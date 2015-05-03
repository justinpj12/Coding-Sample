class PacketIn #(parameter DATA_WIDTH =8);
	rand wire [DATA_WIDTH-1:0] data_i;
	
	function new ( wire [DATA_WIDTH-1:0] pIN );
		begin
			this.data_i = pIN;
		end
	endfunction
	
	function void pack ();
		begin
			this.data_i = {this.data_i};
		end
	endfunction
	
	function void unpack (wire [DATA_WIDTH-1:0] pIN );
		begin
			this.data_i = pIN;
		end
	endfunction
	
	function display ();
		begin
			$display("----PacketIN DFF----\t");
			$display("Input: %b \n", data_i);
		end
	endfunction
	
endclass : PacketIn

class PacketOut #(parameter DATA_WIDTH =8);
	rand wire [DATA_WIDTH-1:0] data_o;
	
	function new ( wire [DATA_WIDTH-1:0] pOUT );
		begin
			this.data_o = pOUT;
		end
	endfunction
	
	function void pack ();
		begin
			this.data_o = {this.data_o};
		end
	endfunction
	
	function void unpack (wire [DATA_WIDTH-1:0] pOUT);
		begin
			this.data_o = pOUT;
		end
	endfunction
	
	function display ();
		begin
			$display("----PacketOUT DFF----\t");
			$display("Output: %b \n", data_o);
		end
	endfunction
	
endclass : PacketOut

class Driver;
// PacketIn handle
	PacketIn pIN;
// mailbox handle
	mailbox #(PacketIn) driver_mb;
// virtual interface
	dff_if INif;
	
	function new (mailbox #(PacketIn) driver_mb, dff_if INif);
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
			INif.in.d = pIN;
			driver_mb.put(pIN);
		end
	endtask
endclass : Driver

class Receiver;
// PacketOut handle
	PacketOut pOUT;
// mailbox handle
	mailbox #(PacketOUT) receiver_mb;
// virtual interface
	dff_if OUTif;
	
	function new (mailbox #(PacketOUT) receiver_mb, dff_if OUTif);
		begin
			this.receiver_mb = receiver_mb;
			this.OUTif = OUTif;
		end
	endfunction

	task read ();
		begin
			pOUT = new();
			pOUT.unpack(OUTif.out.q);
			receiver_mb.put(pOUT);
		end
	endtask
	
endclass : Receiver

class Scoreboard;
//PacketIn and PacketOut handles
	PacketOut pOUT;
	PacketIn pIN;
// mailbox instantiations
	mailbox #(PacketOUT) receiver_mb;
	mailbox #(PacketIn) driver_mb;
	
	function new (mailbox #(PacketOUT) receiver_mb,	mailbox #(PacketIn) driver_mb);
		begin
			this.receiver_mb = receiver_mb;
			this.driver_mb = driver_mb;
		end
	endfunction
	
	task start();
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
	mailbox #(PacketOUT) receiver_mb;
	mailbox #(PacketIn) driver_mb;
	
// virtual interfaces
	dff_if	INif;
	dff_if	OUTif;
	
	function new(dff_if INif, dff_if OUTif);
		begin
			this.INif = INif;
			this.OUTif = OUTif;
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
			INif.in.d = 'b0;
			INif.in.clk = 'b0;
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
				for (i = 0; i<NUM_OF_TESTS; i++) begin: runLoop
					driver_.write();
					receiver_.read();
				end
			join
		end
	endtask
endclass : Environment