





// HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_RESET);

#include "stm32h7xx.h"

void LED_Configure(){
	int* pt_GPIOB_MODER;
	int* pt_GPIOB_OTYPER;
	int* pt_GPIOB_OSPEEDR;
	int* pt_GPIOB_PUPDR;
	int* pt_GPIOB_ODR;
	int* pt_GPIOB_IDR;

	pt_GPIOB_MODER = (int*) 0x58020400;
	pt_GPIOB_OTYPER = (int*) 0x58020404;
	pt_GPIOB_OSPEEDR = (int*) 0x58020408;
	pt_GPIOB_PUPDR = (int*) 0x5802040C;
	pt_GPIOB_IDR = (int*) 0x58020410;
	pt_GPIOB_ODR = (int*) 0x58020414;


	*pt_GPIOB_MODER &=0xFFFFFFFC;
	*pt_GPIOB_OTYPER &=0xFFFFFFFE;
	*pt_GPIOB_OSPEEDR &=0xFFFFFFFC;
	*pt_GPIOB_PUPDR &=0xFFFFFFFC;
	*pt_GPIOB_IDR &=0xFFFFFFFE;
	*pt_GPIOB_ODR &=0xFFFFFFFE;


	*pt_GPIOB_MODER |=0x1;
}



void LED_DisplayGreen(int val){
	if (val & 1){  //condition donnant le LSB de val
		GPIOB->ODR |=0x1;  //active le bit ON0 pour éclairer la LED verte
	}
	else {
		GPIOB->ODR &=0xFFFFFFFE;  //désactive le bit On0 pour éteindre la LED verte
	}
}

void LED_InitYellow(void){
	GPIO_InitTypeDef myGPIO;
	__GPIOE_CLK_ENABLE();
	myGPIO.Speed = GPIO_SPEED_LOW;
	myGPIO.Mode = GPIO_MODE_OUTPUT_PP;
	myGPIO.Pull = GPIO_NOPULL;
	myGPIO.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOE, &myGPIO);
}


void LED_DisplayYellow(int val){
	//HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
	if (val & 1){
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
	}
}

void LED_Init(void){
	LED_GreenEnable();
	LED_Configure();
	LED_InitYellow();
}


void LED_Disp3LED(int pattern) {
	LED_DisplayGreen(pattern & 1); //lecture du LSB de pattern pour commander la LED verte
	LED_DisplayYellow((pattern & 2)/2); //lecture du deuxième LSB pour commander la LED jaune
}

//void LED_Display(int pattern) {}
