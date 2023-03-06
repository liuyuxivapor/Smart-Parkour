#include "logic.h"

uint16_t logic_random_num(uint16_t max_num, uint16_t min_num)
{
    uint16_t a = 1103515245;  // LCG算法参数a
    uint16_t c = 12345;       // LCG算法参数c
    uint16_t m = 2147483648;  // LCG算法参数m
    uint16_t x = 1;           // 初始随机数值为1
    uint16_t rand_num=0;
    uint16_t range=max_num-min_num;
    for (int16_t i = 0; i < 10; i++) {
        x = (a * x + c) % m;  // 生成新的随机数
        rand_num = x % range + 1;  // 将生成的随机数映射到最大值和最小值之间
        rand_num = rand_num + min_num;
    }
    return rand_num;
}
/*利用LCG算法生成伪随机数，返回随机数值，数值在指定最大值和最小值之间*/

void logic_rise_up(uint16_t speed, struct Logic_player_bird_position *bird_position)
{
    //uint16_t pos=bird_position->position;
    for(uint16_t i=0; i<=3; i++)
    {
        if(bird_position->edge_y[i]+speed > LCD_Y)
        {
            bird_position->edge_y[i]=bird_position->edge_y[i];
        }
        else 
        {
            bird_position->edge_y[i]=bird_position->edge_y[i]+speed;
        }    
    }
}
/*以speed像素每秒速度上升*/

void logic_descend_down(uint16_t speed, struct Logic_player_bird_position *bird_position)
{
    for(uint16_t i=0; i<=3; i++)
    {
        if(bird_position->edge_y[i]>speed)
        {
            bird_position->edge_y[i]=bird_position->edge_y[i]-speed;
        }
        else
        {
            bird_position->edge_y[i]=bird_position->edge_y[i];
        }
    }
}
/*以speed像素每秒速度下降*/

uint16_t logic_collide(struct Logic_player_bird_position *bird_position, struct Logic_ocstacle_position *oc_pos,struct Logic_game_event *logic)
{
    struct Logic_player_bird_position bird = *bird_position;
    struct Logic_ocstacle_position ocs = *oc_pos;
    for(uint16_t i=0; i<=1; i++)
    {
        if(bird.edge_x[1]<ocs.oc_edge_position || bird.edge_x[0]>(ocs.oc_edge_position+ocs.ocstacle_width))
        {
            return 0;
        }
        else if(ocs.ocstacle_type==0)//下方的障碍物
        {
            if(bird.edge_y[3]>ocs.ocstacle_height)
            {
                return 0;
            }
            else if(bird.edge_y[3]<=ocs.ocstacle_height)
            {
                return 1;
            }
        }
        else if(ocs.ocstacle_type==1)//上方的障碍物
        {
            if(bird.edge_y[0]<ocs.ocstacle_height)
            {
                return 0;
            }
            else if(bird.edge_y[0]>=ocs.ocstacle_height)
            {
                return 1;
            }
        }
    }
}
/*判断是否碰撞，碰撞返回1，未碰撞返回0*/

