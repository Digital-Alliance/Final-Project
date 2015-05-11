 

    ///////////////////////////////////////////////////////
   //   Hardware Implementation of the Nueral Network  //
  //                 Digital Aliance                 //
 //    James Ginley, Kaila Balacio, Lillian Deas   //
///////////////////////////////////////////////////


// Floating Point Adder from 180B
module FP_Add(N1,N2,Result,clk, done, reset);

  input [31:0] N1,N2;
	input clk, reset;
	output reg [31:0] Result;
	output reg done;
	reg state =0;
	integer i=0;
	wire [31:0] answer;
	reg [31:0] prevresult = 0;
	
//adder adds(N1,N2,answer,clk);

	always @(posedge clk, negedge reset)
	begin
	
	if (reset ==0)
	begin
	i=0;
	done = 0;
	state = 1'b0;
	end
	
	else
		case(state)
		1'b0:	begin
				done = 0;
				Result = answer;
				i=i+1;
				if (i ==6)
					state = 1'b1;
				end
				
		1'b1: begin
				done = 1;
				if(reset ==0)
					begin
					done = 0;
					state = 1'b0;
					end
				end
		endcase
end

endmodule

// Mux replacement (Sigmoid)
module sigmoid (x, clk, sig_out);
	input x, clk;
	output integer sig_out;
	
	always @ (posedge clk)
	begin
		sig_out = x > 0 ? 1:0;
	end
endmodule

// Mux replacement
module mux_x (select, in_1, clk, mux_out);
	input select, in_1, clk;
	output integer mux_out;
	
	always @ (posedge clk)
	begin
		mux_out = select > 0 ? in_1:0;
	end
endmodule
		
// How to create the pixel, weight and bais controlers?

module NN (clk);

	input clk;
	wire [0:783] pixel;
	wire [0:399] weight1, weight2, bais1, bais2, select1_out, sig1_out, select2_out, sig2_out; 
	wire [0:9] weight3, finish;
	
	
	  /////////////////
	 // First Stage //
	/////////////////
	
	//Call to the pixel controler
	//Call to weight controler
	mux_x(pixel[x], weight1[x], clk, select1_out);
	//summer 
	//access bais controler
	FP_Add(select1_out[x], bais1[x] ,clk, done, reset);
	// might need to reconstruct a new adder
	sigmoid(adder_out, clk, sig1_out);
	// write to memory
	
	  //////////////////
	 // Second Stage //
	//////////////////
	// acess sigmoid and weight
	mux_x(sig1_out[x], weight2[x], clk, select2_out);
	//summer 
	//access bais controler
	FP_Add(select2_out[x], bais2[x] ,clk, done, reset);
	// might need to reconstruct a new adder
	sigmoid(adder_out, clk, sig2_out);
	// write to memory
	
	  /////////////////
	 // Third Stage //
	/////////////////
	// acess sigmoid and weight
	mux_x(sig2_out[x], weight3[x], clk, finish);
	//summer 
	// write to memory

endmodule
