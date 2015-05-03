interface and_if #(parameter NUM_OF_INPUTS = 2);
// signals
	wire [NUM_OF_INPUTS-1:0] a;
	wire c;
	
// modports
	modport in(input a, output c);
	modport out(output c, input a);
endinterface : and_if