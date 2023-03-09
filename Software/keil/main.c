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
  
  //初始化bird,地图和事件列表
  while (main_game_event.End)
  {

  }




  return 0;

}
