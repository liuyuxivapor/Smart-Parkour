#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cartoon.h"
#include "UI.h"
#include "gyroscope.h"

extern uint32_t key0_flag, key1_flag, key2_flag, key3_flag;
extern struct SAcc stcAcc;
extern struct SGyro stcGyro;
extern struct SAngle stcAngle;
/*key0���� key1�½� key2���� key3����*/


// sprintf(str,"Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
// sprintf(str,"Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);
// sprintf(str,"Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);


int main(void)
{
	SYSInit();
	LCD->LCD_RST = 0;
	delay_ms(100); // delay 100ms
	LCD->LCD_RST = 1;
	LCD_Init(1);
	
	char test[100];
	while (1)
	{
		int i = 0;
		while (ReadUARTState == 1)
		{
			test[i] = ReadUART();
			if (i < 100 && test[i] != '\0')
			{
				i++;
			}
		}
		test[99] = '\0';
		UARTString(test);
	}
}
