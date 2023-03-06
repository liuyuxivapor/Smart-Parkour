/*
 * @Author: Xuejian Sun 
 * @Date: 2023-03-06 10:27:21 
 * @Last Modified by: Xuejian Sun
 * @Last Modified time: 2023-03-06 10:36:39
 */

module AHBlite_Decoder
#(
  /*RAMCODE enable parameter*/
  parameter Port0_en = 1,
  /************************/

  /*RAMDATA enable parameter*/
  parameter Port1_en = 1,
  /************************/

  /*LCD enable parameter*/
  parameter Port2_en = 1,
  /************************/

  /*UART enable parameter*/
  parameter Port3_en = 1,
  /************************/

  /*Camera enable parameter*/
  parameter Port4_en = 1,
  /************************/

  /*UART enable parameter*/
  parameter Port5_en = 1
  /************************/
)(
  input [31:0] HADDR,

  /*RAMCODE OUTPUT SELECTION SIGNAL*/
  output wire P0_HSEL,

  /*RAMDATA OUTPUT SELECTION SIGNAL*/
  output wire P1_HSEL,

  /*LCD OUTPUT SELECTION SIGNAL*/
  output wire P2_HSEL,

  /*GPIO OUTPUT SELECTION SIGNAL*/
  output wire P3_HSEL, 

  /*Camera OUTPUT SELECTION SIGNAL*/
  output wire P4_HSEL,

  /*UART OUTPUT SELECTION SIGNAL*/
  output wire P5_HSEL
);

  //RAMCODE-----------------------------------
  //0x00000000-0x0000ffff
  /*Insert RAMCODE decoder code there*/
  assign P0_HSEL = (HADDR[31:16] == 16'h0000) ? Port0_en : 1'b0; 
  /***********************************/

  //RAMDATA-------------------------------
  //0X20000000-0X2000FFFF
  /*Insert RAMDATA decoder code there*/
  assign P1_HSEL = (HADDR[31:16] == 16'h2000) ? Port1_en : 1'b0; 
  /***********************************/

  //PERIPHRAL-----------------------------

  //0X40050000 LCD
  /*Insert LCD decoder code there*/
  assign P2_HSEL = (HADDR[31:16] == 16'h4005) ? Port2_en : 1'b0; 
  /***********************************/

  //0X40000010 UART RX DATA
  //0X40000014 UART TX STATE
  //0X40000018 UART TX DATA
  /*Insert UART decoder code there*/
  assign P3_HSEL = (HADDR[31:4] == 28'h4000010) ? Port3_en : 1'b0; 
  /***********************************/

  //0X4030000 Camera
  /*Insert Camera decoder code there*/
  assign P4_HSEL = (HADDR[31:20] == 12'h403) ? Port4_en : 1'b0;  
  /***********************************/

  //0X4010000 Buzzer
  /*Insert Buzzer decoder code there*/
  assign P5_HSEL = (HADDR[31:20] == 12'h401) ? Port5_en : 1'b0;  
  /***********************************/

endmodule