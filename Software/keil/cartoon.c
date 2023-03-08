#include "cartoon.h"
#include "logic.h"

uint16_t cartoon_draw_bird(uint16_t size)
{
    
}

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