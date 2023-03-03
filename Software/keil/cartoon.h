#include <stdint.h>
#include <stdio.h>
#include "code_def.h"
/*本文件定义游戏动画*/

uint16_t cartoon_draw_bird(uint16_t size);
//画鸟，输入大小挡位，共三种挡位，绘制成功返回1，否则返回0

uint16_t cartoon_draw_bar(uint16_t type, uint16_t start_point, uint16_t height, uint16_t width);
/*绘制一个普通条，type规定类型（1为上方，0为下方）,start_point规定起始点（最左端最边缘处）,
height规定高度，width规定宽度，生成成功返回1，生成失败返回0*/

void cartoon_move_forward(uint16_t speed);
//场景向左移动,模拟鸟飞行,输入移动数据

uint16_t cartoon_fly_right(uint16_t speed);
//玩家控制鸟向右飞行,越向右飞行越慢（限制玩家飞行范围）

uint16_t cartoon_fly_left(void);
//玩家控制鸟向左飞行,向左飞行匀速

void cartoon_refresh(void);
//刷新显示下一张图片

