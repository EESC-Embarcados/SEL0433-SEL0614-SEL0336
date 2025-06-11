
_main:

;LED_Blink1.c,15 :: 		void main() {
;LED_Blink1.c,19 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;LED_Blink1.c,22 :: 		TRISB0_bit = 1;      // Configura o pino RB0 como entrada.
	BSF         TRISB0_bit+0, BitPos(TRISB0_bit+0) 
;LED_Blink1.c,25 :: 		TRISD0_bit = 0;      // Configura o pino RD0 como saída.
	BCF         TRISD0_bit+0, BitPos(TRISD0_bit+0) 
;LED_Blink1.c,26 :: 		LATD0_bit = 0;       // Garante que o LED comece desligado.
	BCF         LATD0_bit+0, BitPos(LATD0_bit+0) 
;LED_Blink1.c,28 :: 		LATA5_bit = 1; // DESLIGA o disp4 (o da direita)
	BSF         LATA5_bit+0, BitPos(LATA5_bit+0) 
;LED_Blink1.c,31 :: 		while(1) {
L_main0:
;LED_Blink1.c,33 :: 		if(PORTB.RB0 == 0) {
	BTFSC       PORTB+0, 0 
	GOTO        L_main2
;LED_Blink1.c,35 :: 		LATD0_bit = ~LATD0_bit;
	BTG         LATD0_bit+0, BitPos(LATD0_bit+0) 
;LED_Blink1.c,38 :: 		Delay_ms(300);
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       12
	MOVWF       R12, 0
	MOVLW       51
	MOVWF       R13, 0
L_main3:
	DECFSZ      R13, 1, 1
	BRA         L_main3
	DECFSZ      R12, 1, 1
	BRA         L_main3
	DECFSZ      R11, 1, 1
	BRA         L_main3
	NOP
	NOP
;LED_Blink1.c,39 :: 		}
L_main2:
;LED_Blink1.c,40 :: 		}
	GOTO        L_main0
;LED_Blink1.c,41 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
