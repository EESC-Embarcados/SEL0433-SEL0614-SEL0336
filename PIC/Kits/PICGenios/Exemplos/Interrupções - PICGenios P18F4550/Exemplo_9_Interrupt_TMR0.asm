
_Interrupt:

;Exemplo_9_Interrupt_TMR0.c,29 :: 		void Interrupt() iv 0x0008 ics ICS_AUTO {
;Exemplo_9_Interrupt_TMR0.c,32 :: 		if (TMR0IF_bit == 1) {
	BTFSS       TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
	GOTO        L_Interrupt0
;Exemplo_9_Interrupt_TMR0.c,34 :: 		LATD2_bit = ~LATD2_bit; // Inverte o estado do LED D2
	BTG         LATD2_bit+0, BitPos(LATD2_bit+0) 
;Exemplo_9_Interrupt_TMR0.c,37 :: 		TMR0H = 0xCF;
	MOVLW       207
	MOVWF       TMR0H+0 
;Exemplo_9_Interrupt_TMR0.c,38 :: 		TMR0L = 0x2C;
	MOVLW       44
	MOVWF       TMR0L+0 
;Exemplo_9_Interrupt_TMR0.c,41 :: 		TMR0IF_bit = 0; // Prepara para a próxima interrupção
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;Exemplo_9_Interrupt_TMR0.c,42 :: 		}
L_Interrupt0:
;Exemplo_9_Interrupt_TMR0.c,43 :: 		}
L_end_Interrupt:
L__Interrupt4:
	RETFIE      1
; end of _Interrupt

_ConfigMCU:

;Exemplo_9_Interrupt_TMR0.c,46 :: 		void ConfigMCU() {
;Exemplo_9_Interrupt_TMR0.c,47 :: 		ADCON1 = 0x0F; // Pinos como digitais
	MOVLW       15
	MOVWF       ADCON1+0 
;Exemplo_9_Interrupt_TMR0.c,48 :: 		TRISD = 0;     // PORTD (LEDs) como saída
	CLRF        TRISD+0 
;Exemplo_9_Interrupt_TMR0.c,49 :: 		LATD = 0;      // Todos os LEDs começam desligados
	CLRF        LATD+0 
;Exemplo_9_Interrupt_TMR0.c,50 :: 		}
L_end_ConfigMCU:
	RETURN      0
; end of _ConfigMCU

_ConfigTIMER:

;Exemplo_9_Interrupt_TMR0.c,53 :: 		void ConfigTIMER() {
;Exemplo_9_Interrupt_TMR0.c,57 :: 		T0CON = 0b00000100; // Timer0 OFF, 16-bit, clock interno, prescaler 1:32
	MOVLW       4
	MOVWF       T0CON+0 
;Exemplo_9_Interrupt_TMR0.c,58 :: 		TMR0H = 0xCF;       // Carrega a parte alta do valor
	MOVLW       207
	MOVWF       TMR0H+0 
;Exemplo_9_Interrupt_TMR0.c,59 :: 		TMR0L = 0x2C;       // Carrega a parte baixa
	MOVLW       44
	MOVWF       TMR0L+0 
;Exemplo_9_Interrupt_TMR0.c,60 :: 		TMR0ON_bit = 1;     // Liga o Timer0 após a configuração
	BSF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;Exemplo_9_Interrupt_TMR0.c,61 :: 		}
L_end_ConfigTIMER:
	RETURN      0
; end of _ConfigTIMER

_ConfigInterrupt:

;Exemplo_9_Interrupt_TMR0.c,64 :: 		void ConfigInterrupt() {
;Exemplo_9_Interrupt_TMR0.c,65 :: 		RCON.IPEN = 0;      // Desabilita os níveis de prioridade (modo compatibilidade)
	BCF         RCON+0, 7 
;Exemplo_9_Interrupt_TMR0.c,66 :: 		GIE_bit = 1;        // Habilita a "chave geral" das interrupções
	BSF         GIE_bit+0, BitPos(GIE_bit+0) 
;Exemplo_9_Interrupt_TMR0.c,67 :: 		TMR0IE_bit = 1;     // Habilita a interrupção específica do Timer0
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;Exemplo_9_Interrupt_TMR0.c,68 :: 		TMR0IF_bit = 0;     // Garante que a flag comece zerada
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;Exemplo_9_Interrupt_TMR0.c,69 :: 		}
L_end_ConfigInterrupt:
	RETURN      0
; end of _ConfigInterrupt

_main:

;Exemplo_9_Interrupt_TMR0.c,72 :: 		void main() {
;Exemplo_9_Interrupt_TMR0.c,73 :: 		ConfigMCU();
	CALL        _ConfigMCU+0, 0
;Exemplo_9_Interrupt_TMR0.c,74 :: 		ConfigTIMER();
	CALL        _ConfigTIMER+0, 0
;Exemplo_9_Interrupt_TMR0.c,75 :: 		ConfigInterrupt();
	CALL        _ConfigInterrupt+0, 0
;Exemplo_9_Interrupt_TMR0.c,80 :: 		while(1) {
L_main1:
;Exemplo_9_Interrupt_TMR0.c,81 :: 		}
	GOTO        L_main1
;Exemplo_9_Interrupt_TMR0.c,82 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
