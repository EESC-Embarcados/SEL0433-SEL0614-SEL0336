
_main:

;Exemplo_10_ADC.c,39 :: 		void main() {
;Exemplo_10_ADC.c,44 :: 		TRISA.RA5=1;  // pino AN4 como entrada (canal analógico escolhido neste ex.)
	BSF         TRISA+0, 5 
;Exemplo_10_ADC.c,54 :: 		ADCON0 = 0B00010001;  // AN4 -> AD ligado, leitura deslig., canal AN0
	MOVLW       17
	MOVWF       ADCON0+0 
;Exemplo_10_ADC.c,55 :: 		ADCON1 = 0B00000000; // tensões de ref. internas = VDD e Vss
	CLRF        ADCON1+0 
;Exemplo_10_ADC.c,57 :: 		ADCON2 = 0B10101010; // Justificativa para direita, FOSC/32 (tempo entre 2 e 25 us)
	MOVLW       170
	MOVWF       ADCON2+0 
;Exemplo_10_ADC.c,61 :: 		Lcd_Init();                        //Inicializa display no modo 4 bits
	CALL        _Lcd_Init+0, 0
;Exemplo_10_ADC.c,62 :: 		Lcd_Cmd(_LCD_CLEAR);               //Apaga display
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Exemplo_10_ADC.c,63 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);          //Desliga cursor
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Exemplo_10_ADC.c,64 :: 		Lcd_Out(1,1,"ADC: ");              // escrita: Linha x Coluna
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr1_Exemplo_10_ADC+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr1_Exemplo_10_ADC+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Exemplo_10_ADC.c,66 :: 		while(1)
L_main0:
;Exemplo_10_ADC.c,68 :: 		ADCON0.GO_DONE = 1;           //liga a leitura e inicia a conversão do ADC
	BSF         ADCON0+0, 1 
;Exemplo_10_ADC.c,69 :: 		while(ADCON0.GO_DONE == 1);   //Aguardar o término da conversão - após a
L_main2:
	BTFSS       ADCON0+0, 1 
	GOTO        L_main3
	GOTO        L_main2
L_main3:
;Exemplo_10_ADC.c,75 :: 		Leitura_ADC = ((ADRESH << 8)| ADRESL);
	MOVF        ADRESH+0, 0 
	MOVWF       FARG_WordToStr_input+1 
	CLRF        FARG_WordToStr_input+0 
	MOVF        ADRESL+0, 0 
	IORWF       FARG_WordToStr_input+0, 1 
	MOVLW       0
	IORWF       FARG_WordToStr_input+1, 1 
;Exemplo_10_ADC.c,102 :: 		WordToStr(Leitura_ADC, Texto);  // conversão
	MOVLW       main_Texto_L0+0
	MOVWF       FARG_WordToStr_output+0 
	MOVLW       hi_addr(main_Texto_L0+0)
	MOVWF       FARG_WordToStr_output+1 
	CALL        _WordToStr+0, 0
;Exemplo_10_ADC.c,103 :: 		LCD_Out(1,5, Texto); // coloca o texto em determinada linha e posição 1, 5
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       5
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       main_Texto_L0+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(main_Texto_L0+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Exemplo_10_ADC.c,104 :: 		Delay_ms(20);       // delay para dar tempo para o LCD atualizar
	MOVLW       52
	MOVWF       R12, 0
	MOVLW       241
	MOVWF       R13, 0
L_main4:
	DECFSZ      R13, 1, 1
	BRA         L_main4
	DECFSZ      R12, 1, 1
	BRA         L_main4
	NOP
	NOP
;Exemplo_10_ADC.c,106 :: 		}
	GOTO        L_main0
;Exemplo_10_ADC.c,108 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
