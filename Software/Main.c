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
	return 0; //jamais atteint car on ne sort pas du while précédent
}
