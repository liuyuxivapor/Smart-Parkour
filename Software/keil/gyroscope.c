#include "gyroscope.h"
#include "code_def.h"
#include <string.h>

struct SAcc stcAcc;
struct SGyro stcGyro;
struct SAngle stcAngle;

void Gyro_Init(void) 
{
  memset(&stcAcc, 0, sizeof(stcAcc));
  memset(&stcGyro, 0, sizeof(stcGyro));
  memset(&stcAngle, 0, sizeof(stcAngle));
  delay_ms(10);
}

void GyroData(void)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	

	ucRxBuffer[ucRxCnt++] = ReadUART();	
	if (ucRxBuffer[0]!=0x55) 
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) return;
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
      default: break;
		}
		ucRxCnt=0;
  }

  delay_ms(10);
}

  // sprintf(str,"Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);

  // sprintf(str,"Gyro:%.3f %.3f %.3f\r\n",(float)stcGyro.w[0]/32768*2000,(float)stcGyro.w[1]/32768*2000,(float)stcGyro.w[2]/32768*2000);

  // sprintf(str,"Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);

