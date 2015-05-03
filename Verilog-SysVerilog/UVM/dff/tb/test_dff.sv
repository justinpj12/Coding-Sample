program automatic test (dff_if.in, dff_if.out);
// Environment instantiation
	Environment env;
	initial
		begin
			env = new(dff_if.in, dff_if.out);
			env.run(10);
			$finish;
		end
endprogram //: test