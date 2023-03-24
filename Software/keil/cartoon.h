#ifndef _CARTOON_H
#define _CARTOON_H

#include <stdint.h>
#include <stdio.h>
#include "code_def.h"
#include "logic.h"
#define BIRD_VIEW_Y 50
#define BIRD_VIEW_X 50
#define BIRD_START_X 5//鸟在绘制范围中的偏移
#define BIRD_START_Y 8//鸟在绘制范围中的偏移
/*本文件定义游戏动画*/

uint16_t Cartoon_bird_view[BIRD_VIEW_Y][BIRD_VIEW_X];
//储存鸟图片像素颜色

struct Cartoon_pictures
{
    uint16_t bird_view[BIRD_VIEW_Y][BIRD_VIEW_X];
    struct Logic_player_bird_position bird_position;
    struct Logic_ocstacle_position *head;   
};

uint16_t Cartoon_bird_shift[2];
//图片起始点相对绘制起始点的偏移量 0x 1y

void cartoon_debug_bird_range(struct Logic_player_bird_position player_bird);
//仅调试时使用，用方框标出鸟的图像范围和碰撞范围

void cartoon_bird_init(uint16_t* bird_view[BIRD_VIEW_Y][BIRD_VIEW_X]);
//初始化鸟

uint16_t cartoon_draw_bird(uint16_t* p_bird_view[BIRD_VIEW_Y][BIRD_VIEW_X], uint16_t start_point[2]);
//画鸟,成功返回1，否则返回0，起始点为绘制范围的左上角

uint16_t cartoon_draw_bar(uint16_t type, uint16_t start_point, uint16_t height, uint16_t width);
/*绘制一个普通条，type规定类型（1为上方，0为下方）,start_point规定起始点（最左端最边缘处）,
height规定高度，width规定宽度，生成成功返回1，生成失败返回0*/

void cartoon_move_forward(uint16_t speed,struct Cartoon_pictures *picture);
//场景向左移动,模拟鸟飞行,输入移动数据

//uint16_t cartoon_fly_right(uint16_t speed);
////玩家控制鸟向右飞行,越向右飞行越慢（限制玩家飞行范围）
//
//uint16_t cartoon_fly_left(void);
////玩家控制鸟向左飞行,向左飞行匀速

void cartoon_refresh(struct Cartoon_pictures *picture_next);
//刷新显示下一张图片

#endif