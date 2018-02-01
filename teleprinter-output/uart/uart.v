//(MINE without buffer)
/******************************************************************************
 *                                                                             *
 * Copyright 2016 myStorm Copyright and related                                *
 * rights are licensed under the Solderpad Hardware License, Version 0.51      *
 * (the “License”); you may not use this file except in compliance with        *
 * the License. You may obtain a copy of the License at                        *
 * http://solderpad.org/licenses/SHL-0.51. Unless required by applicable       *
 * law or agreed to in writing, software, hardware and materials               *
 * distributed under this License is distributed on an “AS IS” BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or             *
 * implied. See the License for the specific language governing                *
 * permissions and limitations under the License.                              *
 *                                                                             *
 ******************************************************************************/

// Copied over uart from original chiphack
// have had little luck in finding the right ports to use on the blackice board
// as cannot seem to use the one programming.

// Start: 8'hD: 8'b00001101
// End: 8'hA: 8'b00001010
// Test: 8'h57: 8'b01010111

module uart(  input        clk,
              input 	   next_ed,
              input 	   button,
              output [3:0] led,        // PMOD[55:52]
              output reg   UART_TX,    // PMOD[50]
              output 	   UART_GND);  // possibly use i_tx(/rx) from PMOD3/4?

   // Some register and wire declarations
   reg [3:0] 		   transmit_state;
   reg [7:0] 		   transmit_data;
   reg 			   key1_reg;
   reg [4:0] 		   word_state;
   reg [3:0] 		   led_value;
   
   //reg [8:0] 		   buffer;
   integer 		   i;
   
   integer 		   len; //length of input string
   reg [120:0] 		   transmit_string; //input string


   // Reset
   wire 		   reset;
   assign reset = ~button;

   // Tie UART_GND low
   assign UART_GND = 0;

   assign led = led_value;

   always @(posedge clk or posedge reset) begin
      if (reset) begin
 	 // Reset to the "IDLE" state
 	 transmit_state <= 0;
	 word_state <= 1;
	 led_value <= 1;
	 
 	 // The UART line is set to '1' when idle, or reset
 	 UART_TX <= 1;

 	 // Data we'll transmit - start at ASCII '0'
 	 transmit_data <= 8'h30;
      end
      else begin
 	 case (transmit_state)
 	   0:
 	     begin
 		// Idle state
		transmit_string = "Hello, World!";
		len = 13;
		led_value <= 1;
			       		
		if (next_ed == 1) begin
		   transmit_state <= 1;
		end
 	     end
 	   1:
 	     begin
 		// Start bit state, and progress onto the next state
		UART_TX <= 0;
		transmit_state <= 2;
		led_value <= 2;
	     end
 	   2,3,4,5,6,7,8,9:
 	     begin
		led_value <= 4;
		
 		// Data bits
		UART_TX <= transmit_data[transmit_state - 2];
		transmit_state <= transmit_state + 1;
 	     end
 	   10:
 	     begin
 		// Fills in transmit_data with next letter
		led_value <= 15;
		UART_TX <= 1;
		transmit_state <= 0; //wait for next button
		if (word_state == 0) begin
		   transmit_state <= 0;
		   word_state <= len + 2;
 		end
		if (word_state == 1) begin
		   word_state <= len + 2;
		   transmit_state <= 0;
		   transmit_data <= 8'hD; //carrage return
		end
		else begin
		   transmit_state <= 1;
		   
		   if (word_state == 1) begin
		      transmit_data <= 8'hA; //newline
		   end
		   else begin
		      i <= word_state - 3;
		      
		      transmit_data[0] <= transmit_string[i*8];
		      transmit_data[1] <= transmit_string[i*8+1];
		      transmit_data[2] <= transmit_string[i*8+2];
		      transmit_data[3] <= transmit_string[i*8+3];
		      transmit_data[4] <= transmit_string[i*8+4];
		      transmit_data[5] <= transmit_string[i*8+5];
		      transmit_data[6] <= transmit_string[i*8+6];
		      transmit_data[7] <= transmit_string[i*8+7];
		      
		      //transmit_state <= 0;
		   end
		   word_state <= word_state - 1;
		end
             end

 	   default:
 	     transmit_state <= 0;
 	 endcase
      end
   end

endmodule
