
#include <stm32l4xx.h>


void turnOnLED(GPIO_TypeDef* GPIOx, uint16_t pin);

void turnOffLED(GPIO_TypeDef* GPIOx, uint16_t pin);

void DisplayMode(int number);

int PressDetect(int sel);

int selectMode(void);

//void waitN(int n);
//elle manque de précision, nous utilisons plutôt HAL_Delay()
