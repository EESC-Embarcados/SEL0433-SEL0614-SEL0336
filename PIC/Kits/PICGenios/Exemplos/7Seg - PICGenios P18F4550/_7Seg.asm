
_Incremento:

;_7Seg.c,22 :: 		void Incremento(unsigned char Contador) {
;_7Seg.c,23 :: 		switch (Contador) {
	GOTO        L_Incremento0
;_7Seg.c,25 :: 		case 0: { LATD = 0b00111111; break; }  // '0'
L_Incremento2:
	MOVLW       63
	MOVWF       LATD+0 
	GOTO        L_Incremento1
;_7Seg.c,26 :: 		case 1: { LATD = 0b00000110; break; }  // '1'
L_Incremento3:
	MOVLW       6
	MOVWF       LATD+0 
	GOTO        L_Incremento1
;_7Seg.c,27 :: 		case 2: { LATD = 0b01011011; break; }  // '2'
L_Incremento4:
	MOVLW       91
	MOVWF       LATD+0 
	GOTO        L_Incremento1
;_7Seg.c,28 :: 		default:{ LATD = 0; ucContador = -1; break; } // Desliga display e reinicia o contador
L_Incremento5:
	CLRF        LATD+0 
	MOVLW       255
	MOVWF       _ucContador+0 
	GOTO        L_Incremento1
;_7Seg.c,29 :: 		}
L_Incremento0:
	MOVF        FARG_Incremento_Contador+0, 0 
	XORLW       0
	BTFSC       STATUS+0, 2 
	GOTO        L_Incremento2
	MOVF        FARG_Incremento_Contador+0, 0 
	XORLW       1
	BTFSC       STATUS+0, 2 
	GOTO        L_Incremento3
	MOVF        FARG_Incremento_Contador+0, 0 
	XORLW       2
	BTFSC       STATUS+0, 2 
	GOTO        L_Incremento4
	GOTO        L_Incremento5
L_Incremento1:
;_7Seg.c,30 :: 		}
L_end_Incremento:
	RETURN      0
; end of _Incremento

_main:

;_7Seg.c,32 :: 		void main() {
;_7Seg.c,34 :: 		unsigned char FlagAux = 0;
	CLRF        main_FlagAux_L0+0 
;_7Seg.c,37 :: 		ADCON1 = 0x0F; // Configura pinos analógicos (AN0-AN12) como I/O Digital
	MOVLW       15
	MOVWF       ADCON1+0 
;_7Seg.c,41 :: 		TRISB0_bit = 1; // Configura RB0 como entrada para ler o botão B0
	BSF         TRISB0_bit+0, BitPos(TRISB0_bit+0) 
;_7Seg.c,45 :: 		TRISD = 0;
	CLRF        TRISD+0 
;_7Seg.c,46 :: 		LATD = 0;   // Inicia com todos os segmentos desligados
	CLRF        LATD+0 
;_7Seg.c,50 :: 		TRISA2_bit = 0; // RA2 (disp1) como saída
	BCF         TRISA2_bit+0, BitPos(TRISA2_bit+0) 
;_7Seg.c,51 :: 		TRISA3_bit = 0; // RA3 (disp2) como saída
	BCF         TRISA3_bit+0, BitPos(TRISA3_bit+0) 
;_7Seg.c,52 :: 		TRISA4_bit = 0; // RA4 (disp3) como saída
	BCF         TRISA4_bit+0, BitPos(TRISA4_bit+0) 
;_7Seg.c,53 :: 		TRISA5_bit = 0; // RA5 (disp4) como saída
	BCF         TRISA5_bit+0, BitPos(TRISA5_bit+0) 
;_7Seg.c,55 :: 		LATA2_bit = 0; // Desliga disp1
	BCF         LATA2_bit+0, BitPos(LATA2_bit+0) 
;_7Seg.c,56 :: 		LATA3_bit = 0; // Desliga disp2
	BCF         LATA3_bit+0, BitPos(LATA3_bit+0) 
;_7Seg.c,57 :: 		LATA4_bit = 0; // Desliga disp3
	BCF         LATA4_bit+0, BitPos(LATA4_bit+0) 
;_7Seg.c,58 :: 		LATA5_bit = 1; // LIGA o disp4 (o da direita)
	BSF         LATA5_bit+0, BitPos(LATA5_bit+0) 
;_7Seg.c,61 :: 		while(1) {
L_main6:
;_7Seg.c,63 :: 		if (PORTB.RB0 == 0 && FlagAux == 0) {
	BTFSC       PORTB+0, 0 
	GOTO        L_main10
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main10
L__main17:
;_7Seg.c,67 :: 		Incremento(++ucContador); // Pré-incrementa o contador e atualiza o display
	INCF        _ucContador+0, 1 
	MOVF        _ucContador+0, 0 
	MOVWF       FARG_Incremento_Contador+0 
	CALL        _Incremento+0, 0
;_7Seg.c,69 :: 		FlagAux = 1;      // "Levanta" a flag para indicar que o botão foi tratado
	MOVLW       1
	MOVWF       main_FlagAux_L0+0 
;_7Seg.c,70 :: 		Delay_ms(40);     // Atraso para ignorar a trepidação mecânica (bouncing)
	MOVLW       104
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_main11:
	DECFSZ      R13, 1, 1
	BRA         L_main11
	DECFSZ      R12, 1, 1
	BRA         L_main11
	NOP
;_7Seg.c,71 :: 		}
L_main10:
;_7Seg.c,74 :: 		if (PORTB.RB0 == 1 && FlagAux == 1) {
	BTFSS       PORTB+0, 0 
	GOTO        L_main14
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main14
L__main16:
;_7Seg.c,77 :: 		FlagAux = 0;      // "Abaixa" a flag, permitindo que um novo clique seja detectado
	CLRF        main_FlagAux_L0+0 
;_7Seg.c,78 :: 		Delay_ms(40);     // Atraso para o bouncing da liberação da tecla
	MOVLW       104
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_main15:
	DECFSZ      R13, 1, 1
	BRA         L_main15
	DECFSZ      R12, 1, 1
	BRA         L_main15
	NOP
;_7Seg.c,79 :: 		}
L_main14:
;_7Seg.c,80 :: 		} // Fim do while
	GOTO        L_main6
;_7Seg.c,81 :: 		} // Fim do main
L_end_main:
	GOTO        $+0
; end of _main
