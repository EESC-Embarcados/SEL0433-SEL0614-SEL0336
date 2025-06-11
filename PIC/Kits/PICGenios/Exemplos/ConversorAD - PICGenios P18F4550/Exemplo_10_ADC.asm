
_main:

;Exemplo_10_ADC.c,44 :: 		void main() {
;Exemplo_10_ADC.c,51 :: 		ADCON1 = 0x0E;
	MOVLW       14
	MOVWF       ADCON1+0 
;Exemplo_10_ADC.c,54 :: 		TRISA0_bit = 1;
	BSF         TRISA0_bit+0, BitPos(TRISA0_bit+0) 
;Exemplo_10_ADC.c,58 :: 		ADCON2 = 0b10101010;
	MOVLW       170
	MOVWF       ADCON2+0 
;Exemplo_10_ADC.c,61 :: 		ADCON0 = 0b00000001;
	MOVLW       1
	MOVWF       ADCON0+0 
;Exemplo_10_ADC.c,63 :: 		Delay_ms(2); // Delay para estabilização
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 1
	BRA         L_main0
	DECFSZ      R12, 1, 1
	BRA         L_main0
	NOP
;Exemplo_10_ADC.c,67 :: 		Lcd_Init();
	CALL        _Lcd_Init+0, 0
;Exemplo_10_ADC.c,68 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Exemplo_10_ADC.c,69 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Exemplo_10_ADC.c,70 :: 		Lcd_Out(1, 1, "Leitura AN0:");
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr1_Exemplo_10_ADC+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr1_Exemplo_10_ADC+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Exemplo_10_ADC.c,73 :: 		while(1) {
L_main1:
;Exemplo_10_ADC.c,75 :: 		ADCON0.GO_DONE = 1;
	BSF         ADCON0+0, 1 
;Exemplo_10_ADC.c,78 :: 		while(ADCON0.GO_DONE == 1);
L_main3:
	BTFSS       ADCON0+0, 1 
	GOTO        L_main4
	GOTO        L_main3
L_main4:
;Exemplo_10_ADC.c,81 :: 		Leitura_ADC = (ADRESH << 8) | ADRESL;
	MOVF        ADRESH+0, 0 
	MOVWF       FARG_WordToStr_input+1 
	CLRF        FARG_WordToStr_input+0 
	MOVF        ADRESL+0, 0 
	IORWF       FARG_WordToStr_input+0, 1 
	MOVLW       0
	IORWF       FARG_WordToStr_input+1, 1 
;Exemplo_10_ADC.c,84 :: 		WordToStr(Leitura_ADC, Texto);
	MOVLW       main_Texto_L0+0
	MOVWF       FARG_WordToStr_output+0 
	MOVLW       hi_addr(main_Texto_L0+0)
	MOVWF       FARG_WordToStr_output+1 
	CALL        _WordToStr+0, 0
;Exemplo_10_ADC.c,87 :: 		Lcd_Out(2, 5, "      "); // Limpa a área do número anterior
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       5
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr2_Exemplo_10_ADC+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr2_Exemplo_10_ADC+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Exemplo_10_ADC.c,88 :: 		Lcd_Out(2, 5, Texto);
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       5
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       main_Texto_L0+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(main_Texto_L0+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Exemplo_10_ADC.c,90 :: 		Delay_ms(100);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       4
	MOVWF       R12, 0
	MOVLW       186
	MOVWF       R13, 0
L_main5:
	DECFSZ      R13, 1, 1
	BRA         L_main5
	DECFSZ      R12, 1, 1
	BRA         L_main5
	DECFSZ      R11, 1, 1
	BRA         L_main5
	NOP
;Exemplo_10_ADC.c,91 :: 		}
	GOTO        L_main1
;Exemplo_10_ADC.c,92 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
