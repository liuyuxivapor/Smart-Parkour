#ifndef _UI_H
#define _UI_H
#include<stdint.h>
#include<stdio.h>
#include"code_def.h"
uint16_t ui_welcome(uint32_t start);
//��ʾ��ʼҳ��,�����󷵻�0ֵ������Ϸ��ʼ
uint16_t ui_pause(uint32_t end, uint32_t con);
//��ʾ��ͣҳ�棬����end�󷵻�0������con�󷵻�1
uint16_t ui_end(uint32_t end,uint32_t restart,uint16_t score);
//��ʾ����ҳ�棬����end�󷵻�0������restart�󷵻�1��scoreΪ����ķ���ͳ��ֵ
#endif
