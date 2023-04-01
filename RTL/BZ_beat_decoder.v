module BZ_beat_decoder (beat,beat_cnt_parameter);
    input [3:0] beat;
    output reg [27:0] beat_cnt_parameter;
localparam tune_pwm_parameter_4 = 27'h4C4B400; //全音         四拍
localparam tune_pwm_parameter_2 = 27'h2625A00; //二分音符     二拍
localparam tune_pwm_parameter_1 = 27'h1312D00; //四分音符     一拍
localparam tune_pwm_parameter_1_2 = 27'h989680;//八分音符     半拍
localparam tune_pwm_parameter_1_4 = 27'h4C4B40;//十六分音     四分之一拍
localparam tune_pwm_parameter_1_8 = 27'h2625A0;//三十二分音符 八分之一拍

always @(beat) begin
    case (beat)
        4'h1: beat_cnt_parameter = tune_pwm_parameter_4;
        4'h2: beat_cnt_parameter = tune_pwm_parameter_2;
        4'h3: beat_cnt_parameter = tune_pwm_parameter_1;
        4'h4: beat_cnt_parameter = tune_pwm_parameter_1_2;
        4'h5: beat_cnt_parameter = tune_pwm_parameter_1_4;
        4'h6: beat_cnt_parameter = tune_pwm_parameter_1_8;
        default:beat_cnt_parameter = 27'd0; 
    endcase 
end
endmodule