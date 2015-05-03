module tb_top;
// Testbench Global assets (parameters, clock etc.)
	bit clk;
	wire d, q;
// Interface instantiation
	dff_if dffif();
// Program block instantiation
	test programblock();
// DUT instantiation
	my_dff and_i(d,q);
	
endmodule;