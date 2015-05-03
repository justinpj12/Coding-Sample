module rom #(
		parameter width = 8,
		parameter depth = 256,
		parameter addr_width = $clog2(depth))(
	
	output reg [width - 1 : 0] data,
	input wire[addr_width - 1 : 0] addr,
	input wire read, clk, reset);

	wire [width - 1 : 0] value[0 : depth - 1];
	genvar d;
		generate  for ( d = 0; d < depth ; d = d + 1 ) begin: fill_loop2
			assign value[d] = d;
			end	 
		endgenerate	
	
	always @(posedge clk) begin
		data <= (read & ~reset) ? value[addr] : { width{ 1'bz } };
	end
endmodule