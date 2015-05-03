
 `include "../source/my_and.v"

class PacketIn #(parameter NUM_OF_INPUTS = 2);
	rand bit [NUM_OF_INPUTS-1:0] data_i;
	
	function new ( bit pIn );
		begin
			this.data_i = pIn;
		end
	endfunction
	
	function void pack ();
		begin
			this.data_i = {this.data_i};
		end
	endfunction
	
	function void unpack (bit pIn);
		begin
			this.data_i = pIn;
		end
	endfunction
	
	function display ();
		begin
			$display("----PacketIN Add----\t");
			$display("Number of Inputs: %d\t", NUM_OF_INPUTS);
			$display("Inputs: %b \n", data_i);
		end
	endfunction
	
endclass //: PacketIn


class PacketOut;
	rand bit data_o;

	function new ( bit pOut );
		begin
			this.data_o = pOut;
		end
	endfunction
	
	function void pack ();
		begin
			this.data_o = {data_o};
		end
	endfunction
	
	function void unpack (bit pOut);
		begin
			this.data_o = pOut;
		end
	endfunction
	
	function display ();
		begin
			$display("----PacketOUT Add----\t");
			$display("Output: %b \n", data_o);
		end
	endfunction
endclass //: PacketOut

class Driver;
// PacketIn handle
	PacketIn pIN;
// mailbox handle
	mailbox #(PacketIn) driver_mb;
// virtual interface
	virtual and_if INif;
	
	function new (mailbox #(PacketIn) driver_mb, virtual and_if INif);
		begin
			this.driver_mb = driver_mb;
			this.INif = INif;
		end
	endfunction

	task write ();
		begin
			PacketIn pIN = new();
			pIN.randomize();
			pIN.pack();
			INif.in.a = pIN;
			driver_mb.put(pIN);
		end
	endtask
endclass //: Driver

class Receiver;
// PacketOut handle
	PacketOut pOUT;
// mailbox handle
	mailbox #(PacketOut) receiver_mb;
// virtual interface
	virtual and_if OUTif;
	
	function new (mailbox #(PacketOut) receiver_mb, virtual and_if OUTif);
		begin
			this.receiver_mb = receiver_mb;
			this.OUTif = OUTif;
		end
	endfunction

	task read ();
		begin
			pOUT = new();
			pOUT.unpack(OUTif.out.c);
			receiver_mb.put(pOUT);
		end
	endtask
	
endclass //: Receiver

class Scoreboard;
//PacketIn and PacketOut handles
	PacketOut pOUT;
	PacketIn pIN;
// mailbox instantiations
	mailbox #(PacketOut) receiver_mb;
	mailbox #(PacketIn) driver_mb;
	
	function new (mailbox #(PacketOut) receiver_mb,	mailbox #(PacketIn) driver_mb);
		begin
			this.receiver_mb = receiver_mb;
			this.driver_mb = driver_mb;
		end
	endfunction
	
	task start ();
		begin
			pOUT = receiver_mb.get();
			$error("Receiver has the wrong packet!");
			pIN = driver_mb.get();
			$error("Driver has the wrong packet!");
		end
	endtask
	
endclass : Scoreboard

class Environment;

// TestBench components instantiations
	Driver driver_;
	Receiver receiver_;
	Scoreboard scoreboard_;
	mailbox #(PacketOut) receiver_mb;
	mailbox #(PacketIn) driver_mb;
	//my_and and_0(INif, OUTif);
	
// virtual interfaces
	virtual and_if	INif;
	virtual and_if	OUTif;
	
	function new(virtual and_if p,virtual and_if u);
		begin
			this.INif = p;
			this.OUTif = u;
		end
	endfunction
	
	task build ();
		begin
			driver_mb = new();
			receiver_mb = new();
			driver_ = new(driver_mb, INif);
			receiver_ = new(receiver_mb, OUTif);
			scoreboard_ = new(receiver_mb,driver_mb);
		end
	endtask
	
	task reset ();
		begin
			and_.a = 'b0;
			#10;
		end
	endtask
	
	task start ();
		begin
			scoreboard_.start();
		end
	endtask
	
	task run (input integer NUM_OF_TESTS = 10);
		begin
			build();
			reset();
			fork
				start();
				for (integer i = 0; i<NUM_OF_TESTS; i++) begin: runLoop
					driver_.write();
					receiver_.read();
				end
			join
		end
	endtask
endclass //: Environment