#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#define GREEN_LED GPIO_Pin_12
#define ORANGE_LED GPIO_Pin_13
#define RED_LED GPIO_Pin_14
#define BLUE_LED GPIO_Pin_15

void enableDiod(uint16_t diodPin) {
	GPIO_SetBits(GPIOD,  diodPin);
}

void disableDiod(uint16_t diodPin) {
	GPIO_ResetBits(GPIOD, diodPin);
}
