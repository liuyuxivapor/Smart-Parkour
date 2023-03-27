module AHBlite_Buzzer(
    input  wire          HCLK,    
    input  wire          HRESETn, 
    input  wire          HSEL,    
    input  wire   [31:0] HADDR,   
    input  wire    [1:0] HTRANS,  
    input  wire    [2:0] HSIZE,   
    input  wire    [3:0] HPROT,   
    input  wire          HWRITE,  
    input  wire   [31:0] HWDATA,  
    input  wire          HREADY,  
    output wire          HREADYOUT, 
    output wire   [31:0] HRDATA,  
    output wire          HRESP,
    // input  wire			 System_clk,	//50MHz
    output wire			 beep			
);

assign HRESP = 1'b0;
assign HREADYOUT = 1'b1;

reg		en;				//蜂鸣器使能位
wire 	addr_finish;	//播放结束位

wire write_en;
assign write_en = HSEL & HTRANS[1] & HWRITE & HREADY;

reg wr_en_reg;
always@(posedge HCLK or negedge HRESETn) begin
  if(~HRESETn) wr_en_reg <= 1'b0;
  else if(write_en) wr_en_reg <= 1'b1;
  else wr_en_reg <= 1'b0;
end

always@(posedge HCLK or negedge HRESETn or posedge addr_finish)
    if(~HRESETn)
		en <= 1'b0;
	else if(addr_finish == 1'b1)
		en <= 1'b0;
    else if(wr_en_reg && HREADY)
        en <= HWDATA[0];		
	

assign HRDATA = {31'b0,en};


  BZ_music BZ
  (
    // .clk(System_clk),
    .clk(HCLK),
    .rstn(HRESETn),
    .en(en),
    .addr_finish(addr_finish),
    .beep(beep)
  );


endmodule


