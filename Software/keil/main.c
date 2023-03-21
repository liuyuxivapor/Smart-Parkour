#include <stdint.h>
#include <stdio.h>
#include "cartoon.h"


extern uint32_t key0_flag, key1_flag, key2_flag, key3_flag;
/*key0上升 key1下降 key2向左 key3向右*/

int main(void)
{
	SYSInit();
	LCD->LCD_RST = 0;
	delay(2500000); // delay 100ms
	LCD->LCD_RST = 1;
	LCD_Init(1);
	struct Cartoon_pictures main_picture;
	struct Logic_game_event main_game_event;
	main_game_event.Collide_return = 0;
	main_game_event.Pause = 1;
	main_game_event.End = 1;
	main_game_event.Score = 0;
	main_picture.bird_position.edge_x[0] = 300;
	main_picture.bird_position.edge_x[1] = 300 + bird_vis_width;
	main_picture.bird_position.edge_x[2] = 300 + bird_vis_width;
	main_picture.bird_position.edge_x[3] = 300;
	main_picture.bird_position.edge_y[0] = 240;
	main_picture.bird_position.edge_y[1] = 240;
	main_picture.bird_position.edge_y[2] = 240 - bird_vis_height;
	main_picture.bird_position.edge_y[3] = 240 - bird_vis_height;
	main_picture.bird_position.clo_edge_x[0] = 305;
	main_picture.bird_position.clo_edge_x[1] = 305 + bird_clo_width;
	main_picture.bird_position.clo_edge_x[2] = 305 + bird_clo_width;
	main_picture.bird_position.clo_edge_x[3] = 305;
	main_picture.bird_position.clo_edge_y[0] = 235;
	main_picture.bird_position.clo_edge_y[1] = 235;
	main_picture.bird_position.clo_edge_y[2] = 235 - bird_clo_height;
	main_picture.bird_position.clo_edge_y[3] = 235 - bird_clo_height;
	main_picture.head->next = NULL;
	uint16_t seed = 1;//随机生成数的种子
	//cartoon_bird_init(main_picture.bird_view);
	//初始化bird,地图和事件列表
	while (main_game_event.End)
	{
		while (main_game_event.Pause)
		{
			uint16_t oc_id = 0;
			main_picture.head->oc_edge_position = logic_random_num(1200, 1000, &seed);
		}
	}




	return 0;

}
