
_main:

;LED_Tecla_2.c,36 :: 		void main() {
;LED_Tecla_2.c,44 :: 		unsigned char FlagAux = 0; // variável aux. do tipo char que irá permitir
	CLRF        main_FlagAux_L0+0 
;LED_Tecla_2.c,60 :: 		ADCON1 |= 0XF;  // outros MCUs da série PIC18F (ex. PIC18F4520 e derivados)
	MOVLW       15
	IORWF       ADCON1+0, 1 
;LED_Tecla_2.c,68 :: 		trisb.rb0 = 1;  // configura pino RB0 como entrada
	BSF         TRISB+0, 0 
;LED_Tecla_2.c,69 :: 		PORTB.RB0=1; //seria opcional pois internamente, ao colcoar TRISX.RX0 =1,...
	BSF         PORTB+0, 0 
;LED_Tecla_2.c,76 :: 		TRISD.RD0=0; // output - configura o pino como saída (=0) (consome corrente)
	BCF         TRISD+0, 0 
;LED_Tecla_2.c,77 :: 		PORTD.RD0 = 0; // LED OFF
	BCF         PORTD+0, 0 
;LED_Tecla_2.c,83 :: 		while(1) // True
L_main0:
;LED_Tecla_2.c,86 :: 		if(PORTB.RB0 ==0 && FlagAux==0)   // AND lógico (expressão)
	BTFSC       PORTB+0, 0 
	GOTO        L_main4
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main4
L__main11:
;LED_Tecla_2.c,90 :: 		LATD.RD0 =~LATD.RD0; // (TOOGGLE) Inverte o nível lógico do LED em LATD
	BTG         LATD+0, 0 
;LED_Tecla_2.c,94 :: 		FlagAux=1;        //  A condição acima não será mais verdadeira - (aqui
	MOVLW       1
	MOVWF       main_FlagAux_L0+0 
;LED_Tecla_2.c,97 :: 		Delay_ms(40);     // trata efeito bouncing (repique mecânico do botão,
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
;LED_Tecla_2.c,101 :: 		} //fim do bloco IF, o qual em caso de falso (a tecla não for pressionada
L_main4:
;LED_Tecla_2.c,106 :: 		if(PORTB.RB0 ==1 && FlagAux==1)// Se a tecla não estiver press. E flag = 1
	BTFSS       PORTB+0, 0 
	GOTO        L_main8
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main8
L__main10:
;LED_Tecla_2.c,108 :: 		FlagAux=0;     // condição para voltar ao bloco IF anterior
	CLRF        main_FlagAux_L0+0 
;LED_Tecla_2.c,109 :: 		Delay_ms(40);  // trata efeito bouncing
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
;LED_Tecla_2.c,110 :: 		}
L_main8:
;LED_Tecla_2.c,112 :: 		} //while
	GOTO        L_main0
;LED_Tecla_2.c,114 :: 		} // main
L_end_main:
	GOTO        $+0
; end of _main
