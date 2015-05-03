interface dff_if #(parameter DATA_WIDTH =8)(input clk);
// signals
	wire [DATA_WIDTH-1:0] d, q;
	
// clocking block
	clocking clock1 @(posedge clk);
		default input output;
		input d, clk;
		output q;
	endclocking
	
// modports
	modports in(input d, clk, output q);
	modports out(output q, input d, clk);
endinterface : dff_if