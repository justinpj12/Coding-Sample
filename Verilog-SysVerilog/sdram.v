//Simple sdram Module
//Programmer: Justin Jackson
`timescale 1ns / 1ps
module sdram #(
		parameter width = 8, 
		parameter depth = 256,
		parameter addr_width = $clog2(depth))( 
		
	inout [width - 1 : 0] data,
	input wire[addr_width - 1 : 0] addr,
	input wire cmd, seq, clk, reset, sd_wait, ras, cas
    );
	 localparam  	IDLE = 2'd0,
						WAIT = 2'd1,
						RAS = 2'd2,
						CAS = 2'd3;
						
	reg [1:0] state, next_state, state_counter;					
	reg [width - 1 : 0] value[0 : depth - 1];
	reg  [width - 1 : 0] input_data;
	wire [width - 1 : 0] value_loop[0 : depth - 1];
	integer total_count;
	
	genvar d;
	generate  for ( d = 0; d < depth ; d = d + 1 ) begin: fill_loop2
			assign value_loop[d] = d;
			end	 
	endgenerate	
	//cmd == 1: read , cmd == 0: write

	assign data = (cmd && (total_count == 3) && (state != IDLE)) ? value[addr] : 'dz;
	
	always @(posedge clk)
		if(reset)
			state <= IDLE;
		else
			state <= next_state;
	
	always@*
		case (state)
			IDLE: begin
				total_count = 0;
				if (seq) begin 
					next_state <= WAIT; 
					state_counter <= 0; 
					end
				else next_state <= IDLE;
				end
			WAIT: begin
				if (sd_wait & seq)
					state_counter = state_counter + 1;
				if (state_counter == 2) begin
					next_state <= RAS;
					total_count = total_count + 1;
					state_counter <= 0;
					end
				end
			RAS: begin
				if(ras & seq)
					state_counter = state_counter + 1;
				if (state_counter == 2) begin
					next_state <= CAS;
					total_count = total_count + 1;
					state_counter <= 0;
					end
				end
			CAS: begin
				if(cas & seq)
					state_counter = state_counter + 1;
				if (state_counter == 1)
					if (~cmd) value[addr] <= data;
				else if (state_counter == 2) begin
					next_state <= IDLE;
					total_count = total_count + 1;
					state_counter <= 0;
					end
				end
		endcase
		
endmodule
