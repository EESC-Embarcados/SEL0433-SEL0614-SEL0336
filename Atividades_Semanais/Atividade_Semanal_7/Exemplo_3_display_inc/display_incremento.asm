
_Incremento:

;display_incremento.c,49 :: 		void Incremento(unsigned char Contador)   // Bloco de incremento
;display_incremento.c,51 :: 		switch (Contador)
	GOTO        L_Incremento0
;display_incremento.c,64 :: 		case 0:{ LATD = 0b00111111; break;}   // 0
L_Incremento2:
	MOVLW       63
	MOVWF       LATD+0 
	GOTO        L_Incremento1
;display_incremento.c,65 :: 		case 1:{ LATD = 0b00000110; break;}   // 1
L_Incremento3:
	MOVLW       6
	MOVWF       LATD+0 
	GOTO        L_Incremento1
;display_incremento.c,66 :: 		case 2:{ LATD = 0b01011011; break;}   // 2
L_Incremento4:
	MOVLW       91
	MOVWF       LATD+0 
	GOTO        L_Incremento1
;display_incremento.c,67 :: 		default:{ PORTD =0; ucContador = -1; break;} // zera todo o PORTD e
L_Incremento5:
	CLRF        PORTD+0 
	MOVLW       255
	MOVWF       _ucContador+0 
	GOTO        L_Incremento1
;display_incremento.c,69 :: 		}
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
;display_incremento.c,71 :: 		}
L_end_Incremento:
	RETURN      0
; end of _Incremento

_main:

;display_incremento.c,76 :: 		void main() {
;display_incremento.c,82 :: 		unsigned char FlagAux = 0; // variável aux. do tipo char que irá permitir
	CLRF        main_FlagAux_L0+0 
;display_incremento.c,98 :: 		ADCON1 |= 0XF;   // outros MCUs da série PIC18F (ex. PIC18F4520 e derivados)
	MOVLW       15
	IORWF       ADCON1+0, 1 
;display_incremento.c,106 :: 		TRISB.RB0 = 1;  // configura pino RB0 como entrada
	BSF         TRISB+0, 0 
;display_incremento.c,107 :: 		PORTB.RB0=1; //seria opcional pois internamente, ao colcoar TRISX.RX0 =1,...
	BSF         PORTB+0, 0 
;display_incremento.c,115 :: 		TRISD=0;
	CLRF        TRISD+0 
;display_incremento.c,116 :: 		PORTD = 0;
	CLRF        PORTD+0 
;display_incremento.c,123 :: 		while(1) // True
L_main6:
;display_incremento.c,125 :: 		if(PORTB.RB0 ==0 && FlagAux==0)   // AND lógico (expressão)
	BTFSC       PORTB+0, 0 
	GOTO        L_main10
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main10
L__main17:
;display_incremento.c,129 :: 		Incremento(++ucContador);      // recebe o Incremento do contador
	INCF        _ucContador+0, 1 
	MOVF        _ucContador+0, 0 
	MOVWF       FARG_Incremento_Contador+0 
	CALL        _Incremento+0, 0
;display_incremento.c,133 :: 		FlagAux=1;        //  A condição acima não será mais verdadeira
	MOVLW       1
	MOVWF       main_FlagAux_L0+0 
;display_incremento.c,134 :: 		Delay_ms(40);     // tratar efeito bouncing
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
;display_incremento.c,136 :: 		}
L_main10:
;display_incremento.c,139 :: 		if(PORTB.RB0 ==1 && FlagAux==1)// Se a tecla não estiver press. e flag = 1
	BTFSS       PORTB+0, 0 
	GOTO        L_main14
	MOVF        main_FlagAux_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main14
L__main16:
;display_incremento.c,141 :: 		FlagAux=0;     // condição para voltar ao bloco IF anterior
	CLRF        main_FlagAux_L0+0 
;display_incremento.c,142 :: 		Delay_ms(40);    // tratar efeito bouncing
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
;display_incremento.c,143 :: 		}
L_main14:
;display_incremento.c,145 :: 		} //while
	GOTO        L_main6
;display_incremento.c,147 :: 		} // main
L_end_main:
	GOTO        $+0
; end of _main
