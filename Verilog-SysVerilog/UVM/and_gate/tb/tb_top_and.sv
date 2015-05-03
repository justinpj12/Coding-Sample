module tb_top;
// Testbench Global assets (parameters, clock etc.)
	bit clk;
	bit a;
	bit c;
// Interface instantiation
	and_if andif();
// Program block instantiation
	test programblock();
// DUT instantiation
	my_and and_i(a,c);
	
	integer i;
	initial 
		begin 
			a=0;

			clk=0;
			
			

			#5
				a=1;

				
			#5
				a=1;

				
			#5
				a=0;

				

		end 
endmodule;