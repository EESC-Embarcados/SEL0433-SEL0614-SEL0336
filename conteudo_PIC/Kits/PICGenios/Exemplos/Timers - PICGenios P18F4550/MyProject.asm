
_main:

;MyProject.c,36 :: 		void main() {
;MyProject.c,39 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;MyProject.c,40 :: 		TRISC0_bit = 1; // RC0 como entrada para o Timer1
	BSF         TRISC0_bit+0, BitPos(TRISC0_bit+0) 
;MyProject.c,41 :: 		TRISD = 0;      // PORTD (LEDs) como saída
	CLRF        TRISD+0 
;MyProject.c,42 :: 		LATD = 0;       // Todos os LEDs começam desligados
	CLRF        LATD+0 
;MyProject.c,46 :: 		T1CON = 0b10110011;
	MOVLW       179
	MOVWF       T1CON+0 
;MyProject.c,49 :: 		TMR1H = 0xFF;
	MOVLW       255
	MOVWF       TMR1H+0 
;MyProject.c,50 :: 		TMR1L = 0xF6;
	MOVLW       246
	MOVWF       TMR1L+0 
;MyProject.c,51 :: 		TMR1IF_bit = 0;
	BCF         TMR1IF_bit+0, BitPos(TMR1IF_bit+0) 
;MyProject.c,54 :: 		while(1) {
L_main0:
;MyProject.c,56 :: 		if (TMR1IF_bit == 1) {
	BTFSS       TMR1IF_bit+0, BitPos(TMR1IF_bit+0) 
	GOTO        L_main2
;MyProject.c,57 :: 		LATD1_bit = 1;      // Acende o LED D1
	BSF         LATD1_bit+0, BitPos(LATD1_bit+0) 
;MyProject.c,60 :: 		TMR1H = 0xFF;
	MOVLW       255
	MOVWF       TMR1H+0 
;MyProject.c,61 :: 		TMR1L = 0xF6;
	MOVLW       246
	MOVWF       TMR1L+0 
;MyProject.c,62 :: 		TMR1IF_bit = 0;
	BCF         TMR1IF_bit+0, BitPos(TMR1IF_bit+0) 
;MyProject.c,64 :: 		Delay_ms(1000);     // Mantém o LED aceso por 1 segundo
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
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
;MyProject.c,65 :: 		}
	GOTO        L_main4
L_main2:
;MyProject.c,68 :: 		LATD1_bit = 0;
	BCF         LATD1_bit+0, BitPos(LATD1_bit+0) 
;MyProject.c,69 :: 		}
L_main4:
;MyProject.c,70 :: 		}
	GOTO        L_main0
;MyProject.c,71 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
