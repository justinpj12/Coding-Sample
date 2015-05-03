`include "class_and.sv"
program automatic test (and_if and_if0);
// Environment instantiation
	Environment env;
	initial
		begin
			env = new(and_if0.in, and_if0.out);
			env.run(10);
			//$finish;
		end
		
endprogram //: test