//Ce fichier inclut les fonctions qui structurent le programme,
//ainsi que les fonctions d'affichage des LEDs et d'utilisation
//des boutons.


#include <stm32l4xx.h>

#include "functions.h"

// Définir les broches correspondantes aux LED
#define LED_PWR GPIO_PIN_11
#define LED_USR GPIO_PIN_12


// Définir la broche correspondante au bouton
#define BTN_SEL GPIO_PIN_6


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
void displayMode(int number){
    // Éteind la LED
    turnOffLED(GPIOA, LED_USR);
    int N = 30000;

    // Allumer les LED en fonction du chiffre
    switch (number) {
        case 0: //1 clignotement pour le mode 1
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
            break;
        case 1: //2 clignotements pour le mode 2
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
            break;
        case 2: //3 clignotements pour le mode 3
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
            break;
        case 3: //4 clignotements pour le mode 4
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
			turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
        	turnOnLED(GPIOA, LED_USR);
        	waitN(N);
        	turnOffLED(GPIOA, LED_USR);
			waitN(N);
            break;
        default:
            // Valeur invalide, éteindre toutes les LED
            turnOffLED(GPIOA, LED_USR);
            break;
    }
}


//attente et détection d'appui court ou long
int pressDetect(int sel){
	int chrono = 0;
	int btn_sel = 0;
	int remind = 5000000;
	while(1){
		while(remind!=0){
			btn_sel = HAL_GPIO_ReadPin(GPIOB, BTN_SEL);
			if (btn_sel){
				while ((btn_sel)&&(chrono<3000000)){  //un appui trop long ne sera pas contabilisé
					chrono++;
					btn_sel = HAL_GPIO_ReadPin(GPIOB, BTN_SEL);
				}
			}
			remind--;
			if ((chrono>400000)&&(chrono<2999999)){
				return 1;
			}
			if ((chrono>5000)&&(chrono<399999)){ //minimum 50000 période pour se prémunir des faux contacts
				return 0;
			}
			//si les conditions ne sont pas vérifiées, aucun appui n'est détecté
		}
		remind = 5000000;
		displayMode(sel);
	}
}

// sélection avec les boutons du mode souhaité 
int selectMode(){
	int sel = 0;
	int btn_sel = 0;
	displayMode(sel);
	while(1){
		btn_sel = pressDetect(sel); 
		if (btn_sel) {
			displayMode(sel);
			return sel;
		}
		else {
			sel = (sel + 1) % 4;
			displayMode(sel);
		}
	}
}


void leTest(void){
	int mode = 0;
	while(1) {
		mode = selectMode();
		switch(mode){   //on exécute la bonne fonction selon le mode choisi
			case 0:
				turnOnLED(GPIOA, LED_PWR);
				waitN(50000);
				//Forward();
				turnOffLED(GPIOA, LED_PWR);
				break;
			case 1:
				turnOnLED(GPIOA, LED_PWR);
				waitN(50000);
				//ForwardFront();
				turnOffLED(GPIOA, LED_PWR);
				break;
			case 2:
				turnOnLED(GPIOA, LED_PWR);
				waitN(50000);
				//Forward10();
				turnOffLED(GPIOA, LED_PWR);
				break;
			case 3:
				turnOnLED(GPIOA, LED_PWR);
				waitN(50000);
				//ForwardFast();
				turnOffLED(GPIOA, LED_PWR);
				break;
		}
		mode = 0;
		
		// indication avec les LEDs que le déplacement est terminé
		for (int i=0; i<3; i++){
			turnOnLED(GPIOA, LED_USR);
			turnOnLED(GPIOA, LED_PWR);
			waitN(30000);
			turnOffLED(GPIOA, LED_USR);
			turnOffLED(GPIOA, LED_PWR);
			waitN(30000);
		}
	}
}
