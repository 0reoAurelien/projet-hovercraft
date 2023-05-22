#include <stm32l4xx.h>

#include "hovercraft_test1.h"

// Définir les broches correspondantes aux LED
#define LED_PWR 9  //à vérifier quand même, tout ça
#define LED_USR 11


// Définir la broche correspondante au bouton
#define BTN_SEL GPIO_PIN_X

// Initialisation des LED
GPIO_InitTypeDef GPIO_InitStruct = {0};
GPIO_InitStruct.Pin = LED_PWR | LED_USR;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// Initialisation du bouton
GPIO_InitStruct.Pin = BTN_SEL;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_PULLUP;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


void waitN(int n){
	while (n!=0){
		n--;
	}
}

// Fonction pour allumer une LED spécifique
void turnOnLED(GPIO_TypeDef* GPIOx, uint16_t pin){
    HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_SET);
}

// Fonction pour éteindre une LED spécifique
void turnOffLED(GPIO_TypeDef* GPIOx, uint16_t pin){
    HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_RESET);
}

// Fonction pour contrôler les LED en fonction du chiffre
void DisplayMode(int number){
    // Éteind la LED
    turnOffLED(GPIOA, LED_USR);


    // Allumer les LED en fonction du chiffre
    switch (number) {
        case 0: //1 clignotement pour le mode 1
            turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
            break;
        case 1: //2 clignotements pour le mode 2
            turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
			waitN(5000000);
			turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
            break;
        case 2: //3 clignotements pour le mode 3
            turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
			waitN(5000000);
			turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
			waitN(5000000);
			turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
            break;
        case 3: //4 clignotements pour le mode 4
            turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
			waitN(5000000);
			turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
			waitN(5000000);
			turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
			waitN(5000000);
			turnOnLED(GPIOA, LED_USR);
			waitN(10000000);
			turnOffLED(GPIOA, LED_PWR);
            break;
        default:
            // Valeur invalide, éteindre toutes les LED
            turnOffLED(GPIOA, LEDPIN1);
            turnOffLED(GPIOA, LEDPIN2);
            break;
    }
}


//attente et détection d'appui court ou long
int PressDetect(int sel){
	int chrono = 0;
	int btn_sel = 0;
	int remind = 500000000;
	while(1){
		while(remind!=0){
			btn_sel = HAL_GPIO_ReadPin(GPIOB, BTN_SEL);
			if (btn_sel){
				while ((btn_sel)&&(chrono<500000000)){  //un appui trop long ne sera pas contabilisé
					chrono++;
					btn_sel = HAL_GPIO_ReadPin(GPIOB, BTN_SEL);
				}
			}
			remind--;
			if ((chrono>40000000)&&(chrono<499999999)){
				return 1;
			}
			if ((chrono>50000)&&(chrono<40000000)){ //minimum 50000 période pour se prémunir des faux contacts
				return 0;
			}
			//si les conditions ne sont pas vérifiées, aucun appui n'est détecté
		}
		int remind = 500000000;
		dispMode(sel);
	}
}

// sélection avec les boutons du mode souhaité 
int selectMode(){
	int sel = 0;
	int btn_sel = 0;
	int chrono = 0;
	DisplayMode(sel);
	while(1){
		btn_sel = pressDetect(sel); 
		if (btn_sel) {
			DisplayMode(sel);
			return sel;
		}
		else {
			sel = (sel + 1) % 4;
			DisplayMode(sel);
		}
	}
}


void leTest(void){
	mode = 0;
	while(1) {
		mode = selectMode()
		switch(mode){   //on exécute la bonne fonction selon le mode choisi
			case 0:
				turnOnLED(GPIOA, LED_PWR);
				waitN(10000000);
				//Forward();
				turnOffLED(GPIOA, LED_PWR);
				break;
			case 1:
				turnOnLED(GPIOA, LED_PWR);
				waitN(10000000);
				//ForwardFront();
				turnOffLED(GPIOA, LED_PWR);
				break;
			case 2:
				turnOnLED(GPIOA, LED_PWR);
				waitN(10000000);
				//Forward10();
				turnOffLED(GPIOA, LED_PWR);
				break;
			case 3:
				turnOnLED(GPIOA, LED_PWR);
				waitN(10000000);
				//ForwardFast();
				turnOffLED(GPIOA, LED_PWR);
				break;
		}
		mode = 0;
		// digitalWrite LOW sur toutes les LEDs USR ;
	}
}
