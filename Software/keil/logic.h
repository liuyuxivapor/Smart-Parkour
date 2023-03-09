#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdint.h>
#include <stdio.h>
#include "code_def.h"
#define LCD_Y 480           //屏幕纵向像素高度
#define LCD_X 800           //屏幕横向像素宽度
#define Draw_X 1200         //横向渲染范围
#define Draw_start 200      //屏幕左侧在渲染范围中的偏移
#define bird_vis_width 50   //鸟的绘制宽度
#define bird_vis_height 50  //鸟的绘制高度
#define bird_clo_width 40   //鸟的碰撞宽度
#define bird_clo_height 40  //鸟的碰撞高度
#define ocstacle_width 80   //所有障碍物的宽度

/*本文件定义游戏运行逻辑*/

struct Logic_game_event{
    uint16_t Collide_return;//判断是否碰撞返回值,为1时碰撞，为0时未碰撞
    uint16_t Pause;//暂停，为0时暂停，为1时游戏继续进行
    uint16_t End;//游戏结束，为0时结束，为1时游戏继续进行
    uint16_t Score;//得分
};//游戏相关事件，单局游戏中结构体只建立一次

struct Logic_player_bird_position{
    //uint16_t position;
    uint16_t edge_x[4];    //视觉边界
    uint16_t edge_y[4];    //视觉边界
    uint16_t clo_edge_x[4];//碰撞边界
    uint16_t clo_edge_y[4];//碰撞边界
};//玩家所控制的鸟的视觉边界和碰撞体积,从左上角开始顺时针为0，1，2，3

struct Logic_ocstacle_position{
    uint16_t ocstacle_id;
    uint16_t ocstacle_type;  //0为下方障碍，1为上方障碍
    uint16_t ocstacle_height;  //绝对高度，即障碍物边界在屏幕上的纵坐标
    //uint16_t ocstacle_width;
    uint16_t oc_edge_position;//左侧边界横坐标
    struct Logic_ocstacle_position *next;
};//链表,记录每个条的ID、横坐标和高度,ID每局游戏前置零,最后碰撞的条的ID即为得分

uint16_t logic_random_num(uint16_t max_num, uint16_t min_num, uint64_t *seed_x);
/*利用LCG算法生成伪随机数，返回随机数值*/

void logic_rise_up(uint16_t speed, struct Logic_player_bird_position *bird_position);
/*以speed像素每秒速度上升*/

void logic_descend_down(uint16_t speed, struct Logic_player_bird_position *bird_position);
/*以speed像素每秒速度下降*/

//void logic_fly_right(uint16_t speed, struct Logic_player_bird_position *bird_position);
///*以speed像素每秒速度向右移动*/
//
//void logic_fly_left(uint16_t speed, struct Logic_player_bird_position* bird_position);
///*以speed像素每秒速度向左移动*/

uint16_t logic_collide(struct Logic_player_bird_position *bird_position, struct Logic_ocstacle_position *oc_pos, struct Logic_game_event *logic);
/*判断是否碰撞，碰撞返回1，未碰撞返回0*/

//uint16_t logic_fly_speed(uint16_t position);
///*根据坐标计算向左或向右飞行速度*/

#endif