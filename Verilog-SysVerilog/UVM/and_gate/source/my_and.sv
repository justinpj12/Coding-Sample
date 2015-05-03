 `include "interface_and.sv"
 
module my_and
	
#(parameter NUM_OF_INPUTS = 2)
( input wire [NUM_OF_INPUTS - 1:0] a,
 output wire c);

//this is and DUT 
	and_if #(NUM_OF_INPUTS) and_();
	a = and_.in;
	c = and_.out;
endmodule



