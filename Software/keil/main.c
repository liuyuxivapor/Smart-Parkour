#include <stdint.h>
#include <stdio.h>
#include "code_def.h"

extern uint32_t key0_flag, key1_flag, key2_flag, key3_flag;

int main()
{
  SYSInit();
  LCD->LCD_RST = 0;
  delay(5000000); // delay 100ms
  LCD->LCD_RST = 1;
  LCD_Init(1);
  return 0;
}