#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cartoon.h"
#include "UI.h"


extern uint32_t key0_flag, key1_flag, key2_flag, key3_flag;
/*key0���� key1�½� key2���� key3����*/

int main(void)
{
	SYSInit();
	// LCD->LCD_RST = 0;
	// delay_ms(100); // delay 100ms
	// LCD->LCD_RST = 1;
	// LCD_Init(1);
	// struct Cartoon_pictures main_picture;
	// struct Logic_game_event main_game_event;
	while (1)
	{
    LED->LED_MODE = 3;
    Buzzer->EN = 1;
	// 	int start = 1;
	// 	while (start)
	// 	{
	// 		start = ui_welcome(key0_flag);
	// 	}
	// 	main_game_event.Collide_return = 0;
	// 	main_game_event.Pause = 1;
	// 	main_game_event.End = 1;
	// 	main_game_event.Score = 0;
	// 	main_picture.bird_position.edge_x[0] = 300;
	// 	main_picture.bird_position.edge_x[1] = 300 + bird_vis_width;
	// 	main_picture.bird_position.edge_x[2] = 300 + bird_vis_width;
	// 	main_picture.bird_position.edge_x[3] = 300;
	// 	main_picture.bird_position.edge_y[0] = 240;
	// 	main_picture.bird_position.edge_y[1] = 240;
	// 	main_picture.bird_position.edge_y[2] = 240 - bird_vis_height;
	// 	main_picture.bird_position.edge_y[3] = 240 - bird_vis_height;
	// 	main_picture.bird_position.clo_edge_x[0] = 305;
	// 	main_picture.bird_position.clo_edge_x[1] = 305 + bird_clo_width;
	// 	main_picture.bird_position.clo_edge_x[2] = 305 + bird_clo_width;
	// 	main_picture.bird_position.clo_edge_x[3] = 305;
	// 	main_picture.bird_position.clo_edge_y[0] = 235;
	// 	main_picture.bird_position.clo_edge_y[1] = 235;
	// 	main_picture.bird_position.clo_edge_y[2] = 235 - bird_clo_height;
	// 	main_picture.bird_position.clo_edge_y[3] = 235 - bird_clo_height;
	// 	uint64_t seed = 1;//随机数种子
	// 	uint16_t oc_id = 0;
	// 	main_picture.head = (struct Logic_ocstacle_position*)malloc(sizeof(struct Logic_ocstacle_position));
	// 	struct Logic_ocstacle_position* cur = main_picture.head;
	// 	cur->ocstacle_id = oc_id;
	// 	cur->oc_edge_position = logic_random_num(1100, 1000, &seed);
	// 	cur->ocstacle_type = cur->oc_edge_position % 2;
	// 	cur->ocstacle_height = logic_random_num(380, 100, &seed);
	// 	cur->next = NULL;
	// 	//初始化
	// 	//cartoon_bird_init(main_picture.bird_view);
	// 	while (main_game_event.End)
	// 	{
	// 		while (main_game_event.Pause)
	// 		{
	// 			if (cur->oc_edge_position <= 900)//生成一个新的障碍物
	// 			{
	// 				cur->next = (struct Logic_ocstacle_position*)malloc(sizeof(struct Logic_ocstacle_position));
	// 				cur = cur->next;
	// 				cur->next = NULL;
	// 				oc_id++;
	// 				cur->ocstacle_id = oc_id;
	// 				cur->oc_edge_position = logic_random_num(1100, 1000, &seed);
	// 				cur->ocstacle_type = cur->oc_edge_position % 2;
	// 				cur->ocstacle_height = logic_random_num(380, 100, &seed);
	// 			}
	// 			if (key0_flag == 1 && key1_flag == 0)//向上移动
	// 			{
	// 				logic_rise_up(10, &main_picture.bird_position);
	// 			}
	// 			else if (key0_flag == 0 && key1_flag == 1)//向下移动
	// 			{
	// 				logic_descend_down(10, &main_picture.bird_position);
	// 			}
	// 			cartoon_move_forward(20, &main_picture);//场景移动
	// 			if (main_picture.head->oc_edge_position < 110)//释放已经超出左侧绘制范围的障碍物
	// 			{
	// 				main_game_event.Score=main_picture.head->ocstacle_id;
	// 				struct Logic_ocstacle_position* rand = main_picture.head;
	// 				main_picture.head = main_picture.head->next;
	// 				free(rand);
	// 			}
	// 			cartoon_refresh(&main_picture);//显示刚才生成的画面
	// 			if (logic_collide(&main_picture.bird_position, main_picture.head))
	// 			{
	// 				main_game_event.End = 0;
	// 			}
	// 			delay_ms(33);//延迟33毫秒
	// 			if (key0_flag == 1)//KEY0按下时暂停
	// 			{
	// 				main_game_event.Pause = 0;
	// 			}
	// 		}
	// 		int ran_event = ui_pause(key0_flag, key1_flag);
	// 		if (ran_event)
	// 		{
	// 			main_game_event.Pause = 1;
	// 		}
	// 		else
	// 		{
	// 			main_game_event.End = 0;
	// 		}
	// 	}
	// 	int ran_event = ui_end(key0_flag, key1_flag, main_game_event.Score);
	// 	if (ran_event)
	// 	{
	// 		while (main_picture.head != NULL)
	// 		{
	// 			main_picture.head = main_picture.head->next;
	// 			free(main_picture.head);
	// 		}
	// 		continue;
	// 	}
	// 	else
	// 	{
	// 		delay_ms(100);
	// 		break;
	// 	}
	}
	// return 0;

}
