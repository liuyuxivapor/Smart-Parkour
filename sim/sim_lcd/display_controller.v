`timescale 1ns / 1ps

// This module initializes and feeds an ultra cheap ILI9341 display with a resolution of 320x240x16. 
// It uses the 8 bit 8080 interface of the display. As addition, you can configure the landscape or 
// portait mode of the display. It has an 16 bit axi stream slave interface which is used as data 
// source for the display.
module display_controller #(
    parameter CLOCK_DIV = 0, // Divides clk to slowdown the wr cycles. 0 means wr is "clocked" with clk / 2, 1 equals clk / 4, 2 equals clk / 5 ...
    parameter SKIP_INIT = 0, // Skips the initialization sequence and directly starts serializting from the axi stream interface
    
    // Converts an RGB(A) stream to the display format
    // If STREAM_COLORMODE_RGBA == 1, then the expetect format is: | 4 bit R | 4 bit G | 4 bit B | 4 bit A |
    // If STREAM_COLORMODE_RGBA == 0, then the expetect format is: | 5 bit R | 6 bit G | 5 bit B |
    parameter STREAM_COLORMODE_RGBA = 0,

    parameter LANDSCAPE_CONFIG = 0
) (
    input  wire             resetn,
    input  wire             aclk,

    // Data out
    output reg  [7 : 0]     data,
    output wire             rd, 
    output reg              wr,
    output reg              cs,
    output reg              dc,
    output wire             rst,

    // AXI Stream slave interface
    input  wire             s_axis_tvalid,
    output wire             s_axis_tready,
    input  wire             s_axis_tlast,
    input  wire [15 : 0]    s_axis_tdata
);
    localparam INIT_MEM_SIZE = 37;

    localparam COLOR_R_POS = 12;
    localparam COLOR_G_POS = 8;
    localparam COLOR_B_POS = 4;
    localparam COLOR_A_POS = 0;
    localparam COLOR_SUB_PIXEL_WIDTH = 4;

    assign rst = resetn;
    assign rd = 1;
    reg [8 : 0] initMem [0 : INIT_MEM_SIZE - 1]; // dc[8], data[7:0]
    initial 
    begin
        // Initialization sequence for a ILI9341 with 248'h320px
        initMem[  0] = {1'b0, 8'h01};  
        initMem[  1] = {1'b1, 8'h0}; 
        initMem[  2] = {1'b0, 8'h28};  
        initMem[  3] = {1'b1, 8'h0}; 
        initMem[  4] = {1'b0, 8'hC0};  
        initMem[  5] = {1'b1, 8'h23}; 
        initMem[  6] = {1'b0, 8'hC1};  
        initMem[  7] = {1'b1, 8'h10}; 
        initMem[  8] = {1'b0, 8'hC5};  
        initMem[  9] = {1'b1, 8'h2B}; 
        initMem[ 10] = {1'b1, 8'h2B}; 
        initMem[ 11] = {1'b0, 8'hC7};  
        initMem[ 12] = {1'b1, 8'hC0}; 
        initMem[ 13] = {1'b0, 8'h36};  
        if (LANDSCAPE_CONFIG)
        begin
            initMem[ 14] = {1'b1, 8'h20 | 8'h40 | 8'h08}; // MY MX BGR
        end
        else
        begin
            initMem[ 14] = {1'b1, 8'h00 | 8'h40 | 8'h08}; // MY MX BGR
        end
        initMem[ 15] = {1'b0, 8'h3A};  
        initMem[ 16] = {1'b1, 8'h55}; 
        initMem[ 17] = {1'b0, 8'hB1};  
        initMem[ 18] = {1'b1, 8'h00}; 
        initMem[ 19] = {1'b1, 8'h1B}; 
        initMem[ 20] = {1'b0, 8'hB7}; 
        initMem[ 21] = {1'b1, 8'h07}; 
        initMem[ 22] = {1'b0, 8'h11}; 
        initMem[ 23] = {1'b1, 8'h0};
        initMem[ 24] = {1'b0, 8'h29}; 
        initMem[ 25] = {1'b1, 8'h0};
        if (LANDSCAPE_CONFIG)
        begin
            initMem[ 26] = {1'b0, 8'h2A}; // X
            initMem[ 27] = {1'b1, 8'h0}; 
            initMem[ 28] = {1'b1, 8'h0}; 
            initMem[ 29] = {1'b1, 8'h01}; 
            initMem[ 30] = {1'b1, 8'h3F}; 
            initMem[ 31] = {1'b0, 8'h2B}; // Y
            initMem[ 32] = {1'b1, 8'h0}; 
            initMem[ 33] = {1'b1, 8'h0}; 
            initMem[ 34] = {1'b1, 8'h00}; 
            initMem[ 35] = {1'b1, 8'hEF}; 
        end
        else
        begin
            initMem[ 26] = {1'b0, 8'h2A}; // X
            initMem[ 27] = {1'b1, 8'h0}; 
            initMem[ 28] = {1'b1, 8'h0}; 
            initMem[ 29] = {1'b1, 8'h00}; 
            initMem[ 30] = {1'b1, 8'hEF}; 
            initMem[ 31] = {1'b0, 8'h2B}; // Y
            initMem[ 32] = {1'b1, 8'h0}; 
            initMem[ 33] = {1'b1, 8'h0}; 
            initMem[ 34] = {1'b1, 8'h01}; 
            initMem[ 35] = {1'b1, 8'h3F}; 
        end
        initMem[ 36] = {1'b0, 8'h2C};
    end

    reg [$clog2(INIT_MEM_SIZE) - 1 : 0] counter;
    reg [5 : 0]     state;

    reg [15 : 0]    pixel;
    reg             pixelValid;

    reg [5 : 0]     clockDiv;

    assign s_axis_tready = !pixelValid;

    localparam INIT = 0;
    localparam STREAM0 = 1;
    localparam STREAM1 = 2;

    always @(posedge aclk)
    begin
        if (!resetn)
        begin
            data <= 0;
            wr <= 1;
            cs <= 1;
            dc <= 1;
            
            if (SKIP_INIT)
            begin
                pixelValid <= 0;
                state <= STREAM0;
            end
            else 
            begin
                pixelValid <= 1;
                state <= INIT;
            end
        end
        else 
        begin
            cs <= 0;
            if (!pixelValid)
            begin
                if (s_axis_tvalid)
                begin
                    if (STREAM_COLORMODE_RGBA)
                    begin
                        pixel <= {s_axis_tdata[COLOR_R_POS +: COLOR_SUB_PIXEL_WIDTH], 1'b0, 
                                  s_axis_tdata[COLOR_G_POS +: COLOR_SUB_PIXEL_WIDTH], 2'b00, 
                                  s_axis_tdata[COLOR_B_POS +: COLOR_SUB_PIXEL_WIDTH], 1'b0};
                    end
                    else
                    begin
                        pixel <= s_axis_tdata;
                    end
                    pixelValid <= 1;
                end
            end

            if ((clockDiv == CLOCK_DIV) || (CLOCK_DIV == 0))
            begin
                clockDiv <= 0;
                case (state)
                INIT:
                begin
                    if (wr)
                    begin
                        dc <= initMem[counter][8];
                        data <= initMem[counter][0 +: 8];
                        wr <= 0;
                        counter <= counter + 1;
                    end
                    else 
                    begin
                        wr <= 1;
                        if (counter == INIT_MEM_SIZE) 
                        begin
                            pixelValid <= 0;
                            state <= STREAM0;
                        end
                    end
                end
                STREAM0:
                begin
                    if (wr)
                    begin
                        if (pixelValid)
                        begin
                            dc <= 1;
                            wr <= 0;
                            data <= pixel[8 +: 8];
                        end
                    end
                    else 
                    begin
                        wr <= 1;
                        state <= STREAM1;
                    end
                end
                STREAM1:
                begin
                    if (wr)
                    begin
                        wr <= 0;
                        data <= pixel[0 +: 8];
                    end
                    else 
                    begin
                        wr <= 1;
                        pixelValid <= 0;
                        state <= STREAM0;
                    end
                end
                endcase  
            end
            else 
            begin
                clockDiv <= clockDiv + 1;    
            end
        end
    end
endmodule
