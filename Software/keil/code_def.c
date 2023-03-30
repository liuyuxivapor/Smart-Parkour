#include "code_def.h"
#include <stdint.h>
#include <string.h>

extern uint32_t key3_flag, key2_flag, key1_flag, key0_flag;
void SYSInit(void)
{
	// IRQ enable
	NVIC_CTRL_ADDR	=	0x3f;

	// Systick initial
	Set_SysTick_CTRL(0);

	GyroInit();
}

void delay_us(int us)
{
	uint32_t temp;
	SysTick->LOAD  = us*25;
	SysTick->VALUE = 0x00;
	SysTick->CTRL  = 0x05; 
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL  = 0x00;
	SysTick->VALUE = 0x00;
}

void delay_ms(int ms)
{
	uint32_t temp;
	SysTick->LOAD  = ms*25000;
	SysTick->VALUE = 0x00; 
	SysTick->CTRL  = 0x05;
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL  = 0x00; 
	SysTick->VALUE = 0x00;
}

uint32_t ReadUARTState()
{
    uint32_t state;
	state = UART -> UARTTX_STATE;
    return(state);
}

char ReadUART()
{
    char data;
	data = UART -> UARTRX_DATA;
    return(data);
}

void WriteUART(char data)
{
    while(ReadUARTState());
	UART -> UARTTX_DATA = data;
}

void UARTString(char *stri)
{
	int i;
	for(i=0;i<strlen(stri);i++)
	{
		WriteUART(stri[i]);
	}
}

void UARTHandle()
{
	int data;
	data = ReadUART();
	UARTString("Cortex-M0 : ");
	WriteUART(data);
	WriteUART('\n');
}
