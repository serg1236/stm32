#include "diod.h"

uint16_t delay_c = 0; 


void SysTick_Handler() {
	if (delay_c > 0) {
		delay_c--;
	}
}


void delay_ms(uint16_t delay_t){
	delay_c = delay_t;
	while(delay_c){
	};
}
int main (void){
	GPIO_InitTypeDef rip;
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	rip.GPIO_Mode = GPIO_Mode_OUT;
	rip.GPIO_OType = GPIO_OType_PP;
	rip.GPIO_Pin = GPIO_Pin_All;
	rip.GPIO_PuPd = GPIO_PuPd_NOPULL;
	rip.GPIO_Speed = GPIO_Low_Speed;
	
	GPIO_Init(GPIOD, &rip);

	SysTick_Config(SystemCoreClock/1000);
	while(1)
	{
   	enableDiod(RED_LED);
		delay_ms(500);
		disableDiod(RED_LED);
		enableDiod(BLUE_LED);
		delay_ms(500);
		delay_ms(1000);
		disableDiod(BLUE_LED);
		enableDiod(GREEN_LED);
		enableDiod(ORANGE_LED);
		delay_ms(1000);
		disableDiod(GREEN_LED);
		disableDiod(ORANGE_LED);
	}
	
}




