
_Move_Delay:

;Lcd.c,40 :: 		void Move_Delay() {
;Lcd.c,41 :: 		Delay_ms(400);
	MOVLW       5
	MOVWF       R11, 0
	MOVLW       15
	MOVWF       R12, 0
	MOVLW       241
	MOVWF       R13, 0
L_Move_Delay0:
	DECFSZ      R13, 1, 1
	BRA         L_Move_Delay0
	DECFSZ      R12, 1, 1
	BRA         L_Move_Delay0
	DECFSZ      R11, 1, 1
	BRA         L_Move_Delay0
;Lcd.c,42 :: 		}
L_end_Move_Delay:
	RETURN      0
; end of _Move_Delay

_main:

;Lcd.c,44 :: 		void main(){
;Lcd.c,47 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;Lcd.c,48 :: 		CMCON  = 0x07; // Desabilita comparadores
	MOVLW       7
	MOVWF       CMCON+0 
;Lcd.c,50 :: 		Lcd_Init(); // Inicializa o LCD
	CALL        _Lcd_Init+0, 0
;Lcd.c,52 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Lcd.c,53 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Lcd.c,55 :: 		Lcd_Out(1, 1, txt3);
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _txt3+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_txt3+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Lcd.c,56 :: 		Lcd_Out(2, 1, txt4);
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _txt4+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_txt4+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Lcd.c,57 :: 		Delay_ms(2500);
	MOVLW       26
	MOVWF       R11, 0
	MOVLW       94
	MOVWF       R12, 0
	MOVLW       110
	MOVWF       R13, 0
L_main1:
	DECFSZ      R13, 1, 1
	BRA         L_main1
	DECFSZ      R12, 1, 1
	BRA         L_main1
	DECFSZ      R11, 1, 1
	BRA         L_main1
	NOP
;Lcd.c,59 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Lcd.c,60 :: 		Lcd_Out(1, 4, txt1);
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       4
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _txt1+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_txt1+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Lcd.c,61 :: 		Lcd_Out(2, 4, txt2);
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       4
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _txt2+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_txt2+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Lcd.c,62 :: 		Delay_ms(2500);
	MOVLW       26
	MOVWF       R11, 0
	MOVLW       94
	MOVWF       R12, 0
	MOVLW       110
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
	NOP
;Lcd.c,64 :: 		while(1) {
L_main3:
;Lcd.c,65 :: 		for(i=0; i<7; i++) {
	CLRF        _i+0 
L_main5:
	MOVLW       7
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main6
;Lcd.c,66 :: 		Lcd_Cmd(_LCD_SHIFT_LEFT);
	MOVLW       24
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Lcd.c,67 :: 		Move_Delay();
	CALL        _Move_Delay+0, 0
;Lcd.c,65 :: 		for(i=0; i<7; i++) {
	INCF        _i+0, 1 
;Lcd.c,68 :: 		}
	GOTO        L_main5
L_main6:
;Lcd.c,69 :: 		for(i=0; i<7; i++) {
	CLRF        _i+0 
L_main8:
	MOVLW       7
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main9
;Lcd.c,70 :: 		Lcd_Cmd(_LCD_SHIFT_RIGHT);
	MOVLW       28
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Lcd.c,71 :: 		Move_Delay();
	CALL        _Move_Delay+0, 0
;Lcd.c,69 :: 		for(i=0; i<7; i++) {
	INCF        _i+0, 1 
;Lcd.c,72 :: 		}
	GOTO        L_main8
L_main9:
;Lcd.c,73 :: 		}
	GOTO        L_main3
;Lcd.c,74 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
