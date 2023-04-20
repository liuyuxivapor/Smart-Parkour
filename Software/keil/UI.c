#include "UI.h"
uint16_t ui_welcome(uint32_t start)
{
    uint8_t start_word[5] = "START";
    uint8_t tip_word[28] = "Please Press start to Strat";
    while(1)
    {
        LCD_ShowString(310,320,180,30,24,start_word);
        LCD_ShowString(148,130,504,15,12,tip_word);
        if(start==1)
        {
            return 0;
        }
    }
}
//显示起始页面,按键后返回0值代表游戏开始
uint16_t ui_pause(uint32_t end, uint32_t con)
{
    uint8_t pause_word[5] = "PAUSE";
    uint8_t tip_word[50] = "Please Press end to Exit or Press con to Continue";
    while(1)
    {
        LCD_ShowString(310,320,180,30,24,pause_word);
        LCD_ShowString(184,130,432,40,12,tip_word);
        if(end==1&&con==0)
        {
            return 0;
        }
        else if(con==1&&end==0)
        {
            return 1;
        }
    }
}
//显示暂停页面，按键end后返回0，按键con后返回1
uint16_t ui_end(uint32_t end,uint32_t restart,uint16_t score)
{
    uint8_t end_word[3] = "END";
    uint8_t score_word[6] = "Score:";
    uint8_t tip_word[24] = "Please Press end to Exit";
    while(1)
    {
        LCD_ShowString(346,320,108,30,24,end_word);
        LCD_ShowString(256,200,180,30,24,score_word);
        LCD_ShowNum(436,200,score,3,24);
        LCD_ShowString(184,130,432,15,12,tip_word);
        if(end==1 && restart==0)
        {
            return 0;
        }
        else if (restart==1 && end==0)
        {
            return 1;
        }
    }
}
//显示结束页面，按键end后返回0，score为传入的分数统计值
