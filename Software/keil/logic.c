#include "logic.h"

uint16_t logic_random_num(uint16_t max_num, uint16_t min_num, uint64_t *seed_x)
{
    uint64_t a = 1103515245;  // LCG算法参数a
    uint64_t c = 12345;       // LCG算法参数c
    uint64_t m = 2147483648;  // LCG算法参数m
    uint64_t rand_num = 0;
    uint64_t range=max_num-min_num;
    *seed_x = (a * *seed_x + c) % m;  // 生成新的随机数
    rand_num = *seed_x % range + 1 + min_num;  // 将生成的随机数映射到最大值和最小值之间
    rand_num = (uint16_t)rand_num;
    return rand_num;
}
/*利用LCG算法生成伪随机数，返回随机数值，数值在指定最大值和最小值之间*/

void logic_rise_up(uint16_t speed, struct Logic_player_bird_position *bird_position)
{
    //uint16_t pos=bird_position->position;
    if(bird_position->edge_y[0]+speed > LCD_Y)
    {
        bird_position->edge_y[0]=LCD_Y;
        bird_position->edge_y[1]=bird_position->edge_y[0];
        bird_position->edge_y[2]=LCD_Y-bird_clo_height;
        bird_position->edge_y[3]=bird_position->edge_y[2];
        bird_position->clo_edge_y[0]=bird_position->edge_y[0]-((bird_vis_height-bird_clo_height)/2);
        bird_position->clo_edge_y[1]=bird_position->clo_edge_y[0];
        bird_position->clo_edge_y[2]=bird_position->clo_edge_y[0]-bird_clo_height;
        bird_position->clo_edge_y[3]=bird_position->clo_edge_y[2];
    }
    else 
    {
        for(uint16_t i=0; i<4; i++)
        {
            bird_position->edge_y[i]=bird_position->edge_y[i]+speed;
            bird_position->clo_edge_y[i]=bird_position->clo_edge_y[i]+speed;
        }
    }    
}
/*以speed像素每秒速度上升*/

void logic_descend_down(uint16_t speed, struct Logic_player_bird_position *bird_position)
{
    if(bird_position->edge_y[3]>speed)
    {
        for(uint16_t i=0; i<4 i++)
        {
            bird_position->edge_y[i]=bird_position->edge_y[i]-speed;
            bird_position->clo_edge_y[i]=bird_position->clo_edge_y[i]-speed;
        }
        
    }
    else
    {
        bird_position->edge_y[3]=0;
        bird_position->edge_y[2]=0;
        bird_position->edge_y[1]=bird_vis_height;
        bird_position->edge_y[0]=bird_vis_height;
        bird_position->clo_edge_y[3]=(bird_vis_height-bird_clo_height)/2;
        bird_position->clo_edge_y[2]=bird_position->clo_edge_y[3];
        bird_position->clo_edge_y[1]=bird_position->clo_edge_y[3]+bird_clo_height;
        bird_position->clo_edge_y[0]=bird_position->clo_edge_y[1];
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
        else
        {
            if(ocs.ocstacle_type==0)
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
}
/*判断是否碰撞，碰撞返回1，未碰撞返回0*/

// uint16_t logic_fly_right_speed(uint16_t position)
// {
// }