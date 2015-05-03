module ram #(
		parameter width = 8, 
		parameter depth = 256,
		parameter addr_width = $clog2(depth))( 
		
	inout [width - 1 : 0] data,
	input wire[addr_width - 1 : 0] addr,
	input wire read, write, clk, reset	);
	
	reg[width - 1 : 0] value[0 : depth - 1];
	
	assign data = read ? value[addr] : 'dz ;

	always @(posedge clk)begin
		if(reset) value[addr] <= 'd0;
		else if(write) value[addr] <= data;
	end	
	
endmodule