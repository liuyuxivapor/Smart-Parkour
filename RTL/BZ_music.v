//顶层文件
module BZ_music(
    input           clk,
    input           rstn,
	input			en,
//    input           en1,
	output			addr_finish,
    output          beep
);

wire beat_finish;
wire addr_en;
wire addr_rstn;
wire tune_pwm_en;
wire tune_pwm_rstn;
wire beat_cnt_en;
wire beat_cnt_rstn;
BZ_music_ctrl bzmusic_ctrl(
    .clk             (clk)
    ,.en             (en)
    ,.rstn           (rstn)
    ,.addr_finish    (addr_finish)
    ,.beat_finish    (beat_finish)
    ,.addr_en        (addr_en)
    ,.addr_rstn      (addr_rstn)
    ,.tune_pwm_en    (tune_pwm_en)
    ,.tune_pwm_rstn  (tune_pwm_rstn)
    ,.beat_cnt_en    (beat_cnt_en)
    ,.beat_cnt_rstn  (beat_cnt_rstn) 
);
wire [8:0] addr;
BZ_addr_cnt addr_cnt(
     .clk          (clk)
    ,.en           (addr_en)
    ,.rstn         (addr_rstn)
    ,.data         (data)
    ,.addr         (addr)
    ,.addr_finish  (addr_finish)
);
wire [11:0] data;
BZ_bram 
#(
     .ADDR_WIDTH(8)
    ,.DATA_WIDTH(12)
) 
BlockROM1
(
     .en(1'b1)
    ,.clk(clk)
    ,.addr_i(addr)
    ,.data_o(data)
);

wire [19:0] tune_pwm_parameter;
BZ_tune_decoder tune_decoder(
     .tune                (data[11:4])
    ,.tune_pwm_parameter  (tune_pwm_parameter)
);
BZ_tune_pwm tune_pwm(     
     .clk            (clk)
    ,.en             (tune_pwm_en)
    ,.rst_n          (tune_pwm_rstn)
    ,.pwm_parameter  (tune_pwm_parameter)
    ,.clk_pwm        (beep)
);
wire  [27:0]  beat_cnt_parameter;
BZ_beat_decoder beat_decoder(
     .beat                (data[3:0])
    ,.beat_cnt_parameter  (beat_cnt_parameter)
);
BZ_beat_cnt beat_cnt(
     .clk                 (clk)
    ,.en                  (beat_cnt_en)
    ,.rstn                (beat_cnt_rstn)
    ,.beat_cnt_parameter  (beat_cnt_parameter)
    ,.beat_finish         (beat_finish)   
);
endmodule