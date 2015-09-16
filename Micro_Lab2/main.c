#include "stm32f4xx_rcc.h"
#include "diod.h"
#include "math.h"
 
uint16_t delay_c = 0; 

const float START_TIME = 250;



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
	float pause = START_TIME;
	GPIO_InitTypeDef button;

	int isButtonDown = 0;
	int doFaster = 1;
	float disableFaster = 0;
	float enableFaster = 0;

	int enable = 0;
	
	SysTick_Config(SystemCoreClock/1000);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	
	rip.GPIO_Mode = GPIO_Mode_OUT;
	rip.GPIO_OType = GPIO_OType_PP;
	rip.GPIO_Pin = GPIO_Pin_All;
	rip.GPIO_PuPd = GPIO_PuPd_NOPULL;
	rip.GPIO_Speed = GPIO_Low_Speed;
	
	GPIO_Init(GPIOD, &rip);
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//Pin 0
	button.GPIO_Pin = GPIO_Pin_0;
	//Mode output
	button.GPIO_Mode = GPIO_Mode_IN;
	//Output type push-pull
	button.GPIO_OType = GPIO_OType_PP;
	//With pull down resistor
	button.GPIO_PuPd = GPIO_PuPd_DOWN;
	//50MHz pin speed
	button.GPIO_Speed = GPIO_Speed_50MHz;
 
	//Initialize pin on GPIOA port
	GPIO_Init(GPIOA, &button);
	
	
	
	
	
	
	
	while(1)
	{
		disableFaster = START_TIME / pause;
		if (disableFaster >= 5) {
			doFaster = 0;
		}
		
		enableFaster = fabs(START_TIME - pause);
		if (enableFaster <= 0.001 || enableFaster >= START_TIME) {
			doFaster = 1;
		}

		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			isButtonDown = 1;
		} else {
			if (isButtonDown) {
				isButtonDown = 0;
				if (doFaster) {
					pause = pause - START_TIME*0.1;
				} else {
					pause = pause + START_TIME*0.1;
				}
			}
		}
		
	

		enableDiod(RED_LED);
		delay_ms(pause);
		disableDiod(RED_LED);
		delay_ms(pause);

		
	}
	
}







