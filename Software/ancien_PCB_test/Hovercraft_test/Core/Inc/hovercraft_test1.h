
void waitN(int n);

void turnOnLED(GPIO_TypeDef* GPIOx, uint16_t pin);

void turnOffLED(GPIO_TypeDef* GPIOx, uint16_t pin);

void DisplayMode(int number);

int PressDetect(int sel);

int selectMode(void);

void leTest(void);