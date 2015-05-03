module my_dff
#(parameter DATA_WIDTH = 8)
(input wire [DATA_WIDTH-1:0] d,
input wire clk, resetb,
output reg [DATA_WIDTH-1:0] q);

//this is dff DUT
	dff_if INif;
	dff_if OUTif;
	
	INif.in.d = d;
	q = OUTif.out.q;
endmodule