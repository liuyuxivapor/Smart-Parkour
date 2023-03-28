#ifndef _UI_H
#define _UI_H
#include<stdint.h>
#include<stdio.h>
#include"code_def.h"
uint16_t ui_welcome(uint32_t start);
//显示起始页面,按键后返回0值代表游戏开始
uint16_t ui_pause(uint32_t end, uint32_t con);
//显示暂停页面，按键end后返回0，按键con后返回1
uint16_t ui_end(uint32_t end,uint32_t restart,uint16_t score);
//显示结束页面，按键end后返回0，按键restart后返回1，score为传入的分数统计值
#endif
