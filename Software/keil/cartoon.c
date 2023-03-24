#include "cartoon.h"

void cartoon_bird_init(uint16_t *bird_view[BIRD_VIEW_Y][BIRD_VIEW_X])
{
    for(uint16_t i=0; i<BIRD_VIEW_Y; i++)
    {
        for(uint16_t j=0; j<BIRD_VIEW_X; j++)
        {
            *(bird_view+i+j) = 0;
        }
    }
    /*-----此处写入鸟的初始化数据-----*/
}
//鸟图像的初始化

uint16_t cartoon_draw_bird(uint16_t *p_bird_view[BIRD_VIEW_Y][BIRD_VIEW_X],uint16_t start_point[2])
{
    uint16_t *bird_view=p_bird_view;
    for(uint16_t i=0; i<BIRD_VIEW_Y; i++)
    {
        for(uint16_t j=0; j<BIRD_VIEW_X; j++)
        {
            if(*(bird_view+(i+1)*j)>13)
            {
                return 0;
            }
            else
            {
                switch (*(bird_view+(i+1)*j))
                {
                    //case 0:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,WHITE);
                        //break;
                    case 1:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,BLACK);
                        break;
                    case 2:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,BLUE);
                        break;
                    case 3:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,BRED);
                        break;
                    case 4:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,GRED);
                        break;
                    case 5:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,GBLUE);
                        break;
                    case 6:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,RED);
                        break;
                    case 7:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,MAGENTA);
                        break;
                    case 8:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,GREEN);
                        break;
                    case 9:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,CYAN);
                        break;
                    case 10:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,YELLOW);
                        break;
                    case 11:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,BROWN);
                        break;
                    case 12:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,BRRED);
                        break;
                    case 13:LCD_Fast_DrawPoint(start_point[0]+j,start_point[1]-i,GRAY);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return 1;
}
//画鸟,成功返回1，否则返回0，起始点为绘制范围的左上角

uint16_t cartoon_draw_bar(uint16_t type, uint16_t start_point, uint16_t height, uint16_t width)
{
    uint16_t start_point_x = start_point;
    uint16_t start_point_y = 0;
    uint16_t end_point_x = start_point_x + width;
    uint16_t end_point_y = height;
    switch(type)
    {
        case 0:start_point_y = 0;
            break;
        case 1:start_point_y = LCD_Y;
            break;
        default:break;
    }
    if (start_point_x < 199 && end_point_x > 199)
    {
        start_point_x = 199;
    }
    else if (start_point_x < 199 && end_point_x < 199)
    {
        return 0;
    }
    if (end_point_x > 999 && start_point_x < 999)
    {
        end_point_x = 999;
    }
    else if (end_point_x > 999 && start_point_x > 999)
    {
        return 0;
    }

    LCD_Color_Fill(start_point_x - 200, start_point_y, end_point_x - 200, end_point_y, &(GREEN));
    return 1;
}
/*绘制一个普通条，type规定类型（1为上方，0为下方）,start_point规定起始点（最左端最边缘处）,
height规定高度，width规定宽度，生成成功返回1，生成失败返回0*/

void cartoon_move_forward(uint16_t speed,struct Cartoon_pictures *picture)
{
    struct Logic_ocstacle_position *p_oc_pos = picture->head;
    do
    {
        if(p_oc_pos->oc_edge_position<speed)
        {
            p_oc_pos->oc_edge_position = 0;
            p_oc_pos = p_oc_pos->next;
        }
        else
        {
            p_oc_pos->oc_edge_position = p_oc_pos->oc_edge_position-speed;
            p_oc_pos = p_oc_pos->next;
        }
        
    }while(p_oc_pos != NULL)
}
//场景（障碍物）向左移动,模拟鸟飞行,输入移动数据

void cartoon_refresh(struct Cartoon_pictures *picture_next)
{
    LCD_Clear(WHITE);
    uint16_t bird_pos_xy[2];
    bird_pos_xy[0] = picture_next->bird_positin.edge_x[0];
    bird_pos_xy[1] = picture_next->bird_positin.edge_y[0];
    cartoon_draw_bird(&(picture_next->bird_view), bird_pos_xy);
    struct Logic_ocstacle_position* oc = picture_next->head;
    do
    {
        cartoon_draw_bar(oc->ocstacle_type, oc->oc_edge_position, oc->ocstacle_height, ocstacle_width );
        oc = oc->next;
    }while(oc != NULL)
}
/*刷新图片*/

void cartoon_debug_bird_range(struct Logic_player_bird_position player_bird)
{
    LCD_DrawLine(player_bird.clo_edge_x[0], player_bird.clo_edge_y[0], player_bird.clo_edge_x[1], player_bird.clo_edge_y[1]);
    LCD_DrawLine(player_bird.clo_edge_x[1], player_bird.clo_edge_y[1], player_bird.clo_edge_x[2], player_bird.clo_edge_y[2]);
    LCD_DrawLine(player_bird.clo_edge_x[2], player_bird.clo_edge_y[2], player_bird.clo_edge_x[3], player_bird.clo_edge_y[3]);
    LCD_DrawLine(player_bird.clo_edge_x[3], player_bird.clo_edge_y[3], player_bird.clo_edge_x[0], player_bird.clo_edge_y[0]);
    LCD_Drawline(player_bird.edge_x[0], player_bird.edge_y[0], player_bird.edge_x[1], player_bird.edge_y[1]);
    LCD_Drawline(player_bird.edge_x[1], player_bird.edge_y[1], player_bird.edge_x[2], player_bird.edge_y[2]);
    LCD_Drawline(player_bird.edge_x[2], player_bird.edge_y[2], player_bird.edge_x[3], player_bird.edge_y[3]);
    LCD_Drawline(player_bird.edge_x[3], player_bird.edge_y[3], player_bird.edge_x[0], player_bird.edge_y[0]);
}