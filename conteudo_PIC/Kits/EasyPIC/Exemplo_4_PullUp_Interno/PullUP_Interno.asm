
_main:

;PullUP_Interno.c,30 :: 		void main() {
;PullUP_Interno.c,39 :: 		ANSELB = 0;  // registrador do PIC18F45K22 - configura todos os pinos...
	CLRF        ANSELB+0 
;PullUP_Interno.c,42 :: 		ANSELD=0; // idem - pinos do PORTD como digital
	CLRF        ANSELD+0 
;PullUP_Interno.c,43 :: 		INTCON2.RBPU=0; // Habilita chave global dos resistores pull-up presente
	BCF         INTCON2+0, 7 
;PullUP_Interno.c,45 :: 		WPUB.WPUB0 = 1; // Habilita o resistor pull-up interno no pino RB0
	BSF         WPUB+0, 0 
;PullUP_Interno.c,59 :: 		TRISB.RB0 = 1;  // configura pino RB0 como entrada
	BSF         TRISB+0, 0 
;PullUP_Interno.c,60 :: 		PORTB.RB0=1; // nível 1 (VCC - pull-up)
	BSF         PORTB+0, 0 
;PullUP_Interno.c,66 :: 		TRISD = 0; // todos os pinos como saída
	CLRF        TRISD+0 
;PullUP_Interno.c,67 :: 		PORTD =0; //todos os pinos = 0
	CLRF        PORTD+0 
;PullUP_Interno.c,70 :: 		while(1) // True
L_main0:
;PullUP_Interno.c,72 :: 		if(PORTB.RB0 ==0)   // AND lógico (expressão)
	BTFSC       PORTB+0, 0 
	GOTO        L_main2
;PullUP_Interno.c,76 :: 		PORTD.RD0 =~LATD.RD0; // (TOOGGLE) Inverte o nível lógico do LED em LAT D
	BTFSC       LATD+0, 0 
	GOTO        L__main5
	BSF         PORTD+0, 0 
	GOTO        L__main6
L__main5:
	BCF         PORTD+0, 0 
L__main6:
;PullUP_Interno.c,80 :: 		Delay_ms(300);
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
;PullUP_Interno.c,82 :: 		}
L_main2:
;PullUP_Interno.c,85 :: 		} //while
	GOTO        L_main0
;PullUP_Interno.c,87 :: 		} // main
L_end_main:
	GOTO        $+0
; end of _main
