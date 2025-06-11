
_main:

;LED_Tecla_2.c,21 :: 		void main() {
;LED_Tecla_2.c,24 :: 		unsigned char FlagAux = 0;
	CLRF        main_FlagAux_L0+0 
;LED_Tecla_2.c,29 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;LED_Tecla_2.c,32 :: 		TRISB0_bit = 1;      // Configura o pino RB0 como entrada.
	BSF         TRISB0_bit+0, BitPos(TRISB0_bit+0) 
;LED_Tecla_2.c,35 :: 		TRISD0_bit = 0;      // Configura o pino RD0 como saída.
	BCF         TRISD0_bit+0, BitPos(TRISD0_bit+0) 
;LED_Tecla_2.c,36 :: 		LATD0_bit = 0;       // Garante que o LED comece desligado.
	BCF         LATD0_bit+0, BitPos(LATD0_bit+0) 
;LED_Tecla_2.c,39 :: 		while(1) { // Loop infinito
L_main0:
;LED_Tecla_2.c,43 :: 		if(PORTB.RB0 == 0 && FlagAux == 0) {
	BTFSC       PORTB+0, 0 
	GOTO        L_main4
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main4
L__main11:
;LED_Tecla_2.c,44 :: 		LATD0_bit = ~LATD0_bit; // Inverte o estado do LED (toggle)
	BTG         LATD0_bit+0, BitPos(LATD0_bit+0) 
;LED_Tecla_2.c,45 :: 		FlagAux = 1;            // "Levanta" a flag, indicando que a ação já ocorreu.
	MOVLW       1
	MOVWF       main_FlagAux_L0+0 
;LED_Tecla_2.c,48 :: 		Delay_ms(40);           // Atraso para filtrar a trepidação do botão.
	MOVLW       104
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_main5:
	DECFSZ      R13, 1, 1
	BRA         L_main5
	DECFSZ      R12, 1, 1
	BRA         L_main5
	NOP
;LED_Tecla_2.c,49 :: 		}
L_main4:
;LED_Tecla_2.c,54 :: 		if(PORTB.RB0 == 1 && FlagAux == 1) {
	BTFSS       PORTB+0, 0 
	GOTO        L_main8
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main8
L__main10:
;LED_Tecla_2.c,55 :: 		FlagAux = 0;            // "Abaixa" a flag, deixando o sistema pronto
	CLRF        main_FlagAux_L0+0 
;LED_Tecla_2.c,57 :: 		Delay_ms(40);           // Atraso opcional para filtrar o bouncing da soltura.
	MOVLW       104
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_main9:
	DECFSZ      R13, 1, 1
	BRA         L_main9
	DECFSZ      R12, 1, 1
	BRA         L_main9
	NOP
;LED_Tecla_2.c,58 :: 		}
L_main8:
;LED_Tecla_2.c,59 :: 		} // Fim do while
	GOTO        L_main0
;LED_Tecla_2.c,60 :: 		} // Fim do main
L_end_main:
	GOTO        $+0
; end of _main
