Les fonctions suivantes réaliseront des appels en bouclent à d'autres fonctions internes qui serviront à lire soit des entrées digitales provenant des boutons,
soit les entrées analogiques provenant des capteurs. Il est donc normal que le prototype des fonctions externes soit souvent (void -> void).


Le programme se structure au sein d'une fonction main comme suit :


int main(void){
	mode = 0;
	while(1) {
		mode = SelectMode()
		switch(mode){   //on exécute la bonne fonction selon le mode choisi
			case 0:
				Forward();
				break;
			case 1:
				ForwardFront();
				break;
			case 2:
				Forward10();
				break;
			case 3:
				ForwardFast();
				break;
		}
		mode = 0;
		// digitalWrite LOW sur toutes les LEDs USR ;
	}
	return 0; //jamais atteint car on ne sort pas du while précédent
}

Nous avons par la suite amélioré ce code pour implémenter des fonctions d'affichage indiquant l'état de fonctionnement des moteurs.

•	SelectMode (void) : choix du mode => bouton poussoir avec 4 modes différents (avancer 5 secondes, avancer droit, avancer de 10m, avancer le plus vite possible)

cette fonction de selection ressemblera à :

selecteur = 0
Tant que (“le bouton “run” n’est pas appuyé) :
	lecture du bouton poussoir
		si “front montant” :   // Il faudra élaborer une fonction pour détecter un front montant du bouton de sélection
		// (pour cela, on peut garder en mémoire l'état actuel du bouton ainsi que son état à l'instant précédent, pour déduire quand le bouton est appuyé)
			selecteur = (selecteur + 1) % 4   // permet de choisir entre les 4 premiers modes
renvoyer selecteur

prototype : ne prend rien (void) en entrée et retourne le selecteur (int) en sortie

int SelectMode() {
	int selecteur = 0;
	int btn_run = 0;
	int btn_sel_current = 0;
	int btn_sel_previous = 0;
	while (btn_run != 1) :
		btn_sel_previous = btn_sel_current;
		btn_sel_current = (*lecture du bouton selecteur*) ; //0 ou 1 en fonction de si le bouton selecteur a été poussé
		if (btn_sel_current & ((btn_sel_prev+1)%2) ) {
// on s’assure que le bouton est appuyé et qu’il ne l’était pas avant
			selecteur = (selecteur + 1) % 4 ;
		btn_run = (*lecture du bouton run*) ;
		}
	}
return selecteur;   // permettra dans le main() de choisir entre les 4 premiers modes
}

Cette version nécessite l'utilisation de deux boutons : un bouton de selection et un bouton run.
Cependant, nous n'avons à disposition qu'un bouton "reset" qui sert à réinitialiser le programme, et un bouton "usr" pour gérer la fonction SelectMode.
Une alternative consiste alors à utiliser un seul bouton pour sélectionner le mode avec des appuis courts, et valider la sélection avec un appui long.


Cette nouvelle version du programme ressemblera à :

#define LEDPIN1 12
#define LEDPIN2 9
#define LEDPIN2 11

void setup() {
	pinMode(LEDPIN1, OUTPUT);
	pinMode(LEDPIN2, OUTPUT);
	pinMode(LEDPIN3, OUTPUT);
}


int SelectMode() {
	digitalwrte(LEDPIN1, LOW);
	digitalwrte(LEDPIN2, LOW);
	digitalwrte(LEDPIN3, LOW);
	int selecteur = 0;
	int btn_sel = 0;
	int chrono = 0;
	while(1){
		btn_sel = (*lecture du bouton selecteur*) ; 
		if (btn_sel) {
			while (btn_sel) {
			// la clock de notre processeur a une fréquence de 80Mhz et chaque passage dans la boucle compte 5 périodes
			// Chaque passage dans cette boucle dure donc 5/(80*10^6Hz) donc 62.5 ns
				chrono++; 
				}
			if (chrono<32000000){
				selecteur = (selecteur + 1) % 4 ;
				DisplayMode(selecteur);
				}
			else {
				return selecteur;
			}
		}
	}
}



Cette fonction SelectMode fait aussi appel à une autre fonction DisplayMode() qui affichera la valeur du sélecteur en binaire grâce aux deux LEDs USR.
Elle ressemblera à :




DisplayMode(int mode) {
	switch(mode){   //on exécute la bonne fonction selon le mode choisi
		case 0:
			digitalwrte(LEDPIN1, LOW);
			digitalwrte(LEDPIN2, LOW);
			// write LOW sur toutes les LEDs;  indique le mode 0
			break;
		case 1:
			digitalwrte(LEDPIN1, HIGH);
			// digitalWrite LOW sur la LED USR 2 ;
			// digitalWrite HIGH sur la LED USR 1 ;   indique le mode 1
			break;
		case 2:
			digitalwrte(LEDPIN1, LOW);
			digitalwrte(LEDPIN2, HIGH);
			// digitalWrite LOW sur la LED USR 1 ;
			// digitalWrite HIGH sur la LED USR 2 ;   indique le mode 2
			break;
		case 3:
			digitalwrte(LEDPIN1, HIGH);
			// digitalWrite HIGH sur toutes les LEDs USR ;   indique le mode 3
			break;
	}
}

•	Forward (void) : avancer 5 secondes => donne la consigne pour faire tourner correctement le moteur 1 et le moteur 2 et faire avancer l'aéroglisseur 5 secondes.
On ne se préoccupe pas de la trajectoire dans cette fonction. On cherche surtout quelle suspension on doit fournir au véhicule pour avancer sans frottement.
Le moteur 2 permettant la suspension du véhicule n'a pas besoin de tourner quand le véhicule est à l'arret (donc quand le moteur 1 est éteint).
Durant la marche du véhicule, le moteur 2 doit avoir une vitesse minimale en permanence pour pouvoir glisser.
Et il doit tourner plus vite lorsque le hovercarft accélère (quand le moteur 2 est allumé), afin que l'avant ne frotte pas trop le sol.
Temps d'attente à programmer par une boucle for, nombre d'itérations à déterminer par pratique si optimisation non indentifiable par le microprocesseur.

prototype : (void -> void)

void Forward() {

•	ForwardFront (void) : avancer droit => Doit respecter les même conditions que le mode précédent avec une contrainte supplémentaire.
Il faut agir sur le servomoteur pour empêcher de dévier de la trajectoire rectiligne.
Pour cela, cette fonction devra lire en boucle le signal de la "centrale inertielle"(gyroscope) pour ensuite donner la consigne au servomoteur de corriger la trajectoire

prototype : (void -> void)

void ForwardFront() {

•	Forward10 (void) : avancer droit sur 10m => En plus des contraintes précédentes,
doit prendre en compte la vitesse (ou l’accélération) de l’hovercraft pour connaître sa position et le faire s'arrêter après 10m

prototype : (void -> void)

void Forward10() {

•	ForwardFast (void) : avancer le plus vite possible => En plus des contraintes précédentes,
doit determiner la vitesse optimale pour parcourir les 10 mètres le plus vite possible et s'arrêter

prototype : (void -> void)

void ForwardFast() {

Les fonctions ici présentes dans le ReadMe sont des ébauches et peuvent comporter des erreurs de syntaxe, ou bien être encore incomplètes. Pour voir le code complet, accédez à notre dossier test-pinout qui contient le code fonctionnel implémenté dans la dernière version de notre PCB. Ce code ne fait pas appel aux fonctions de contrôle des moteurs, car ces derniers ne fonctionnent pas. 
Pour commander les moteurs, nous avons utilisé en parallèle notre carte Nucleo, comme lors de la démonstration durant la présentation orale.
Se référer au document "fonction_hovercraft.odt" pour plus de détails, sur le code. Ce document contient notamment des ébauches de code commenté, et clarifie l'utilisation des fonctions.
