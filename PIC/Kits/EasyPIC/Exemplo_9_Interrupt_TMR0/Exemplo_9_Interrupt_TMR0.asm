
_Interrupt_HIGH:

;Exemplo_9_Interrupt_TMR0.c,31 :: 		void Interrupt_HIGH() iv 0x0008 ics ICS_AUTO {   //Alta prioridade de interrupção
;Exemplo_9_Interrupt_TMR0.c,33 :: 		if(INTCON.TMR0IF == 1)    //Foi o TIMER0 que gerou a interrupção ?
	BTFSS       INTCON+0, 2 
	GOTO        L_Interrupt_HIGH0
;Exemplo_9_Interrupt_TMR0.c,35 :: 		PORTD.RD2 = ~LATD.RD2; //PISCA O LED no PORTD
	BTFSC       LATD+0, 2 
	GOTO        L__Interrupt_HIGH5
	BSF         PORTD+0, 2 
	GOTO        L__Interrupt_HIGH6
L__Interrupt_HIGH5:
	BCF         PORTD+0, 2 
L__Interrupt_HIGH6:
;Exemplo_9_Interrupt_TMR0.c,37 :: 		TMR0H = 0XCF;          //Recarregar o TIMER para 200ms
	MOVLW       207
	MOVWF       TMR0H+0 
;Exemplo_9_Interrupt_TMR0.c,38 :: 		TMR0L = 0X2C;
	MOVLW       44
	MOVWF       TMR0L+0 
;Exemplo_9_Interrupt_TMR0.c,39 :: 		INTCON.TMR0IF = 0;   //Não esquecer de zerar a Flag, pois é responsável por
	BCF         INTCON+0, 2 
;Exemplo_9_Interrupt_TMR0.c,41 :: 		}
L_Interrupt_HIGH0:
;Exemplo_9_Interrupt_TMR0.c,43 :: 		}    // Fim da subrotina de interrupção
L_end_Interrupt_HIGH:
L__Interrupt_HIGH4:
	RETFIE      1
; end of _Interrupt_HIGH

_ConfigMCU:

;Exemplo_9_Interrupt_TMR0.c,47 :: 		void ConfigMCU()
;Exemplo_9_Interrupt_TMR0.c,49 :: 		ADCON1 |= 0X0F;    // pinos do microcontrolador como digitais
	MOVLW       15
	IORWF       ADCON1+0, 1 
;Exemplo_9_Interrupt_TMR0.c,51 :: 		TRISD = 0;       //Configurar os pinos de controle dos LEDs
	CLRF        TRISD+0 
;Exemplo_9_Interrupt_TMR0.c,52 :: 		PORTD = 0;      // inicialmente desligado
	CLRF        PORTD+0 
;Exemplo_9_Interrupt_TMR0.c,53 :: 		}
L_end_ConfigMCU:
	RETURN      0
; end of _ConfigMCU

_ConfigTIMER:

;Exemplo_9_Interrupt_TMR0.c,55 :: 		void ConfigTIMER()
;Exemplo_9_Interrupt_TMR0.c,65 :: 		T0CON = 0B00000100;  //TIMER_OFF, MOD_16BITS, TIMER, PRES_1:32
	MOVLW       4
	MOVWF       T0CON+0 
;Exemplo_9_Interrupt_TMR0.c,66 :: 		TMR0H = 0XCF;   // Carga do valor inicial
	MOVLW       207
	MOVWF       TMR0H+0 
;Exemplo_9_Interrupt_TMR0.c,67 :: 		TMR0L = 0X2C;
	MOVLW       44
	MOVWF       TMR0L+0 
;Exemplo_9_Interrupt_TMR0.c,69 :: 		INTCON.TMR0IF = 0;  //zera a Flag  (vai p/ 1 quando ocorrer o overflow)
	BCF         INTCON+0, 2 
;Exemplo_9_Interrupt_TMR0.c,70 :: 		T0CON.TMR0ON = 1;   //Liga o TIMER0
	BSF         T0CON+0, 7 
;Exemplo_9_Interrupt_TMR0.c,71 :: 		}
L_end_ConfigTIMER:
	RETURN      0
; end of _ConfigTIMER

_ConfigInterrupt:

;Exemplo_9_Interrupt_TMR0.c,73 :: 		void ConfigInterrupt()
;Exemplo_9_Interrupt_TMR0.c,75 :: 		INTCON.GIE = 1;   //Chave Geral, Habilita o uso de interrupção
	BSF         INTCON+0, 7 
;Exemplo_9_Interrupt_TMR0.c,77 :: 		RCON.IPEN = 0; //0 -> (default) herança da família PIC16F, onde existe apenas
	BCF         RCON+0, 7 
;Exemplo_9_Interrupt_TMR0.c,91 :: 		INTCON.TMR0IE = 1;   //Habilita a interrupção individual do TIMER0
	BSF         INTCON+0, 5 
;Exemplo_9_Interrupt_TMR0.c,92 :: 		}
L_end_ConfigInterrupt:
	RETURN      0
; end of _ConfigInterrupt

_main:

;Exemplo_9_Interrupt_TMR0.c,95 :: 		void main() {
;Exemplo_9_Interrupt_TMR0.c,96 :: 		ConfigMCU();           //pinos do MCU config. para acionar os LEDS
	CALL        _ConfigMCU+0, 0
;Exemplo_9_Interrupt_TMR0.c,97 :: 		ConfigTIMER();         // tempo config. e TIMER ligado
	CALL        _ConfigTIMER+0, 0
;Exemplo_9_Interrupt_TMR0.c,98 :: 		ConfigInterrupt(); //Configuração global das interrupções
	CALL        _ConfigInterrupt+0, 0
;Exemplo_9_Interrupt_TMR0.c,101 :: 		while(1) {  // Endless loop
L_main1:
;Exemplo_9_Interrupt_TMR0.c,102 :: 		} //while
	GOTO        L_main1
;Exemplo_9_Interrupt_TMR0.c,103 :: 		} //main
L_end_main:
	GOTO        $+0
; end of _main
