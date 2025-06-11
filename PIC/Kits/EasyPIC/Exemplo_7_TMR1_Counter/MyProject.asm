
_main:

;MyProject.c,27 :: 		void main() {
;MyProject.c,29 :: 		ADCON1=0x0F;   // Pinos digitais
	MOVLW       15
	MOVWF       ADCON1+0 
;MyProject.c,31 :: 		TRISC.RC0=1; // RC0 como entrada pois corresponde ao pino T1CK1 que incrementa a
	BSF         TRISC+0, 0 
;MyProject.c,37 :: 		PORTC.RC0=1;  // em pull-up
	BSF         PORTC+0, 0 
;MyProject.c,39 :: 		TRISD=0;   // PORTD como entrada
	CLRF        TRISD+0 
;MyProject.c,40 :: 		PORTD=0;   //inicialmente zero (LED)
	CLRF        PORTD+0 
;MyProject.c,42 :: 		PORTD.RD1=0;
	BCF         PORTD+0, 1 
;MyProject.c,44 :: 		T1CON =0B10000011; // Config. do timer1 no modo contador, 16 bits, ligado
	MOVLW       131
	MOVWF       T1CON+0 
;MyProject.c,47 :: 		TMR1H=0xFF;
	MOVLW       255
	MOVWF       TMR1H+0 
;MyProject.c,48 :: 		TMR1L=0xF6;
	MOVLW       246
	MOVWF       TMR1L+0 
;MyProject.c,50 :: 		PIR1.TMR1IF=0;//Flag do timer 1 em zero (vai para 1 quando ocorre overflow)
	BCF         PIR1+0, 0 
;MyProject.c,53 :: 		while(1){
L_main0:
;MyProject.c,54 :: 		if(TMR1IF_bit){  // monitora a flag - se igual 1
	BTFSS       TMR1IF_bit+0, BitPos(TMR1IF_bit+0) 
	GOTO        L_main2
;MyProject.c,55 :: 		PORTD.RD1=1; //ação quando totalizar 10 eventos
	BSF         PORTD+0, 1 
;MyProject.c,56 :: 		TMR1H=0xFF;   //recarrega o timer para nova contagem
	MOVLW       255
	MOVWF       TMR1H+0 
;MyProject.c,57 :: 		TMR1L=0xF6;
	MOVLW       246
	MOVWF       TMR1L+0 
;MyProject.c,58 :: 		PIR1.TMR1IF=0;   //zera flag para nova contagem
	BCF         PIR1+0, 0 
;MyProject.c,59 :: 		Delay_ms(1000);    // aguarda um tempo com a sinalização acionada
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
;MyProject.c,60 :: 		}
	GOTO        L_main4
L_main2:
;MyProject.c,62 :: 		PORTD.RD1=0; // LED desligado caso contrário
	BCF         PORTD+0, 1 
;MyProject.c,63 :: 		}
L_main4:
;MyProject.c,65 :: 		}
	GOTO        L_main0
;MyProject.c,67 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
