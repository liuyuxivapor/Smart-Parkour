/*
 * @Author: Xuejian Sun 
 * @Date: 2023-02-27 17:56:13 
 * @Last Modified by: Xuejian Sun
 * @Last Modified time: 2023-02-27 18:20:39
 */

module GPIO (
  input   wire        outEn,
  input   wire  [7:0] oData,
  input   wire  [7:0] iData,
  input   wire        clk,
  input   wire        RSTn,

  inout   wire  [7:0] ioPin
);

  reg [7:0] tmp;

  always @(posedge clk or negedge RSTn) begin
    if (~RSTn) tmp <= 8'h0;
    else tmp <= ioPin;
  end

  assign tmp = iData;
  assign ioPin = outEn ? oData : 8'bzzzzzzzz;
  
endmodule