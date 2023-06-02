#include <functions.h>
#include <stm32l4xx.h>


// Définir les broches correspondantes aux LED
#define LED_PWR GPIO_PIN_11
#define LED_USR GPIO_PIN_12


// Définir la broche correspondante au bouton
#define BTN_SEL GPIO_PIN_6

/*
void waitN(int n){
	while (n!=0){
		n--;
	}
}
*/
//Nous utilisons plutôt HAL_Delay()


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
    int N = 300;

    // Allumer les LED en fonction du chiffre
    switch (number) {
        case 0: //1 clignotement pour le mode 1
        	turnOnLED(GPIOA, LED_USR);
        	HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
            break;
        case 1: //2 clignotements pour le mode 2
        	turnOnLED(GPIOA, LED_USR);
        	HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
            break;
        case 2: //3 clignotements pour le mode 3
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
            break;
        case 3: //4 clignotements pour le mode 4
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
			turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOnLED(GPIOA, LED_USR);
			HAL_Delay(N);
        	turnOffLED(GPIOA, LED_USR);
			HAL_Delay(N);
            break;
        default:
            // Valeur invalide, éteindre toutes les LED
            turnOffLED(GPIOA, LED_USR);
            break;
    }
}


//attente et détection d'appui court ou long
int pressDetect(int sel){
	int chrono = 0; //compteur du nombre de passages dans la boucle cette fonction
	int btn_sel = 0; //variable donnée par lecture du bouton
	int blink = 0; //utile pour l'affichage indiquant un appui trop long du bouton
	while(1){
		btn_sel = 1-HAL_GPIO_ReadPin(GPIOB, BTN_SEL); //car il est configuré en pull-up
		if (btn_sel){
			while (btn_sel){  //un appui trop long ne sera pas contabilisé
				chrono++;
				if (chrono>59){
					while (btn_sel){
						blink=1-blink;
						HAL_GPIO_WritePin(GPIOA, LED_PWR, blink); //fait clignoter la LED_PWR
						btn_sel = 1-HAL_GPIO_ReadPin(GPIOB, BTN_SEL);  //(en configuration pull up)
						HAL_Delay(250);
					}
					turnOffLED(GPIOA, LED_PWR);
				}
				HAL_Delay(50);
				btn_sel = 1-HAL_GPIO_ReadPin(GPIOB, BTN_SEL);  //(en configuration pull up)
			}
		}
		if ((chrono>9)&&(chrono<60)){
			return 1;
		}
		if ((chrono>1)&&(chrono<10)){ //minimum 100 ms période pour se prémunir des faux contacts
			return 0;
		}
		chrono=0;
		//si les conditions ne sont pas vérifiées, aucun appui n'est détecté
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
