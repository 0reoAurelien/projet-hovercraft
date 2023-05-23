	.type LED_GreenEnable, %function
	.global LED_GreenEnable
LED_GreenEnable:
	PUSH {R4,R5,R6,LR}
	LDR R4,=0x58024540
	LDR R5,[R4]
	MOV R6,#0x2
	ORR R5,R5,R6
	STR R5,[R4]
	POP {R4,R5,R6,PC}
