#include "cartoon.h"

void cartoon_bird_init(uint16_t *bird_view[BIRD_VIEW_Y][BIRD_VIEW_X])
{
    for(uint16_t i=0; i<BIRD_VIEW_Y; i++)
    {
        for(uint16_t j=0; j<BIRD_VIEW_X; j++)
        {
            bird_view[i][j]=0;
        }
    }

}
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
    uint16_t end_point_x = 0;
    uint16_t end_point_y = 0;
    if(type==0)
    {
        start_point_y = 0;
        end_point_x = start_point_x + ocstacle_width;
        end_point_y = height;
    }
    else if(type==1)
    {
        start_point_y = LCD_Y;
        
    }

}