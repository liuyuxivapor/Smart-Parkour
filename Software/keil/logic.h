#include <stdint.h>
#include <stdio.h>
#include "code_def.h"

uint16_t draw_bar(uint16_t type, uint16_t start_point, uint16_t height);
/*绘制一个普通条，type规定类型（1为上方，0为下方）,start_point规定起始点（最左端最边缘处）,
height规定高度，生成成功返回1，生成失败返回0*/

uint16_t random_num(uint16_t max_num, uint16_t min_num);
/*利用LCG算法生成伪随机数，返回随机数值*/

void rise_up(uint16_t speed);
/*以speed像素每秒速度上升*/

void descend_down(uint16_t speed);
/*以speed像素每秒速度下降*/

uint16_t collide(uint16_t position_player, uint16_t position_obstacle);
/*判断是否碰撞，碰撞返回1，未碰撞返回0  test2*/