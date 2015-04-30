
///////////////////////////////////////////////////////
//   Hardware Implementation of the Nueral Network  //
//                 Digital Aliance                  //
//    James Ginley, Kaila Balacio, Lillian Deas    //
/////////////////////////////////////////////////////


// 2 to 1 Mux for First Stage
module 2to1Mux ( in_0, in_1, out);
  input [3:0] in_0;
  input       in_1;
  output [3:0] out;
  
  assign out = in_1 ? in_0;
  
endmodule

// Pipelined Multiplier for Second and Third Stages
module 8x8_Mult_Piped (a, b, clk, reset, y);
  input clk, reset;
  input[0:7] a, b;
  output[15:0] y

  reg[7:0] aR[8:0];
  reg[7:0] bR[8:0];
  reg[15:0] yR[8:0];
  
  always @ (posedge clk)
    begin
    
      aR[7] = aR[6];
      bR[7] = bR[6];
      yR[7] = yR[6];
      aR[6] = aR[5];
      bR[6] = bR[5];
      yR[6] = yR[5];
      aR[5] = aR[4];
      bR[5] = bR[4];
      yR[5] = yR[4];
      aR[4] = aR[3];
      bR[4] = bR[3];
      yR[4] = yR[3];
      aR[3] = aR[2];
      bR[3] = bR[2];
      yR[3] = yR[2];
      aR[2] = aR[1];
      bR[2] = bR[1];
      yR[2] = yR[1];
      aR[1] = aR[0];
      bR[1] = bR[0];
      yR[1] = yR[0];

      aR[0] = a;
      bR[0] =b;
      yR[0] = 8x8_Mult_Piped(aR[0], bR[0]);

    end
    
    function [15:0] 8x8_Mult_Piped;
    input [7:0] a,b;
    reg [7:0] a_mag, b_mag;
    reg [14:0] y_mag;
    reg [14:0] y_neg;
    begin
      
      case (a[7])
        0: a_mag = a[6:0];
        1: a_mag = 128 - a[6:0];
      endcase
      
      case(b[7])
        0: b_mag = b[6:0];
        1: b_mag = 128 - b[6:0];
      endcase 
      
      y_mag = a_mag * b_mag;
      
      if ((a[7]^b[7]) & (y_mag != 0))
      begin
        y_neg = 32768 - y_mag[13:0]
        8x8_Mult_Piped = {1'b1, y_neg};
      end
      else 
        8x8_Mult_Piped = y_mag;
      end
      
      endfunction 
      
      assign y = yR[7];
      
      endmodule

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
	
adder adds(N1,N2,answer,clk);

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

/* MAY NOT NEED
//FP Multiplier with no rounding from 180B 
module FP_Mul(N1,N2,Result,clk, done, reset);
	input [31:0] N1,N2;
	input clk, reset;
	output reg[31:0] Result;
	output reg done;
	wire [8:0] E;
	wire [47:0] M;
	wire [47:0] realM1, realM2;
	wire [8:0] realE;
	reg firstone, secondone;
	reg state =0;
	
	//assign Result[31] = N1[31]^N2[31];
	assign E = N1[30:23] + N2[30:23] -127;
	assign M = {1'b1,N1[22:0]} * {1'b1,N2[22:0]};
	assign realM2 = M << 2;
	assign realM1 = M << 1;
	assign realE = E+1;
	
	always @ (M[47], M[46], reset, N1, N2)
	begin
	if (reset == 0)
		done = 0;
	else
		begin
			if(M[47] == 1)
				begin
				//realM1 = M << 1;
				//realE = E+1;
				Result[31] = N1[31]^N2[31];
				Result[30:23] = realE[7:0];
				Result[22:0] = realM1[47:25];
				if(realM1[24] && realM1[23])
				begin
				Result = Result +1;
				end
				done =1;
				end
			else if (M[46] == 1)
				begin
				//realM2 = M << 2;
				Result[31] = N1[31]^N2[31];
				Result[30:23] = E[7:0];
				Result[22:0] = realM2[47:25];
				if(realM2[24] && realM2[23])
				begin
				Result = Result +1;
				end
				done =1;
				end
		end
	end
endmodule
*/
