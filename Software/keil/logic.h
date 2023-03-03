#include <stdint.h>
#include <stdio.h>
#include "code_def.h"

/*本文件定义游戏运行逻辑*/

struct Logic_game_event{
    uint16_t Collide_return;//判断是否碰撞返回值
    uint16_t Pause;//暂停，为1时暂停，为0时游戏继续进行
    //uint16_t  Score;//得分
};//游戏相关事件，单局游戏中结构体只建立一次

struct Logic_player_bird_position{
    uint16_t edge_x[4];
    uint16_t edge_y[4];
};//玩家所控制的鸟的碰撞体积,从左上角开始顺时针为0，1，2，3

struct Logic_ocstacle_position{
    uint16_t ocstacle_id;
    uint16_t ocstacle_height;
    uint16_t ocstacle_width;
    uint16_t oc_edge_position;//左侧边界横坐标
    struct Logic_ocstacle_position *next;
};//链表,记录每个条的ID、横坐标和高度,ID每局游戏前置零,最后碰撞的条的ID即为得分

uint16_t logic_random_num(uint16_t max_num, uint16_t min_num);
/*利用LCG算法生成伪随机数，返回随机数值*/

void logic_rise_up(uint16_t speed);
/*以speed像素每秒速度上升*/

void logic_descend_down(uint16_t speed);
/*以speed像素每秒速度下降*/

uint16_t logic_collide(struct Logic_player_bird_position *player_position, uint16_t position_obstacle);
/*判断是否碰撞，碰撞返回1，未碰撞返回0*/

uint16_t logic_fly_right_speed(uint16_t position);
/*根据坐标计算向右飞行速度*/