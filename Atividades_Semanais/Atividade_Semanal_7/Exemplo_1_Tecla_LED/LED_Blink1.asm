
_main:

;LED_Blink1.c,37 :: 		void main() {
;LED_Blink1.c,49 :: 		ADCON1 |= 0XF;  // outros MCUs da série PIC18F (ex. PIC18F4550 e derivados)
	MOVLW       15
	IORWF       ADCON1+0, 1 
;LED_Blink1.c,57 :: 		TRISB.RB0 = 1;  // configura pino RB0 como entrada no PORTB
	BSF         TRISB+0, 0 
;LED_Blink1.c,58 :: 		PORTB.RB0=1; //seria opcional pois internamente, ao colocar TRISX.RX0 =1,...
	BSF         PORTB+0, 0 
;LED_Blink1.c,65 :: 		TRISD.RD0=0; // output - configura o pino como saída (=0) (consome corrente)
	BCF         TRISD+0, 0 
;LED_Blink1.c,66 :: 		LATD.RD0 = 0; // LED OFF
	BCF         LATD+0, 0 
;LED_Blink1.c,69 :: 		while(1) // True
L_main0:
;LED_Blink1.c,71 :: 		if(PORTB.RB0 ==0)   // Tecla ativada em nível lógico 0 (SE o pino estiver ..
	BTFSC       PORTB+0, 0 
	GOTO        L_main2
;LED_Blink1.c,74 :: 		LATD.RD0 =~LATD.RD0; // Inverte o nível lógico do LED em LATD
	BTG         LATD+0, 0 
;LED_Blink1.c,77 :: 		Delay_ms(300);     // retarda a CPU de forma que ao pressionar a tecla..
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
;LED_Blink1.c,80 :: 		}  //fim do bloco IF, o qual em caso de falso (a tecla não for pressionada)
L_main2:
;LED_Blink1.c,90 :: 		} //while
	GOTO        L_main0
;LED_Blink1.c,92 :: 		} // main
L_end_main:
	GOTO        $+0
; end of _main
