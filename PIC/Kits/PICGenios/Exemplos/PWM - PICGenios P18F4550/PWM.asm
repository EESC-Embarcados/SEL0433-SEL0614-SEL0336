
_Move_Delay:

;PWM.c,40 :: 		void Move_Delay() {
;PWM.c,41 :: 		Delay_ms(400);
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
;PWM.c,42 :: 		}
L_end_Move_Delay:
	RETURN      0
; end of _Move_Delay

_PWM_Init:

;PWM.c,49 :: 		void PWM_Init() {
;PWM.c,50 :: 		TRISC2_bit = 0;      // Configura o pino RC2 (CCP1) como sa?da.
	BCF         TRISC2_bit+0, BitPos(TRISC2_bit+0) 
;PWM.c,53 :: 		PR2 = 255;           // Define o valor m?ximo do contador do Timer2 (per?odo).
	MOVLW       255
	MOVWF       PR2+0 
;PWM.c,57 :: 		T2CON = 0b00000101;  // Liga o Timer2 com um prescaler de 4 (TMR2ON=1, T2CKPS=1).
	MOVLW       5
	MOVWF       T2CON+0 
;PWM.c,61 :: 		CCP1CON = 0b00001100;  // Ativa o modo PWM para o CCP1.
	MOVLW       12
	MOVWF       CCP1CON+0 
;PWM.c,62 :: 		}
L_end_PWM_Init:
	RETURN      0
; end of _PWM_Init

_PWM_Set_Duty:

;PWM.c,66 :: 		void PWM_Set_Duty(unsigned int duty) {
;PWM.c,68 :: 		CCPR1L = duty >> 2;
	MOVF        FARG_PWM_Set_Duty_duty+0, 0 
	MOVWF       R0 
	MOVF        FARG_PWM_Set_Duty_duty+1, 0 
	MOVWF       R1 
	RRCF        R1, 1 
	RRCF        R0, 1 
	BCF         R1, 7 
	RRCF        R1, 1 
	RRCF        R0, 1 
	BCF         R1, 7 
	MOVF        R0, 0 
	MOVWF       CCPR1L+0 
;PWM.c,71 :: 		CCP1CON = (CCP1CON & 0b11001111) | ((duty & 0b11) << 4);
	MOVLW       207
	ANDWF       CCP1CON+0, 0 
	MOVWF       R3 
	MOVLW       3
	ANDWF       FARG_PWM_Set_Duty_duty+0, 0 
	MOVWF       R2 
	MOVF        R2, 0 
	MOVWF       R0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	MOVF        R0, 0 
	IORWF       R3, 0 
	MOVWF       CCP1CON+0 
;PWM.c,72 :: 		}
L_end_PWM_Set_Duty:
	RETURN      0
; end of _PWM_Set_Duty

_main:

;PWM.c,75 :: 		void main() {
;PWM.c,76 :: 		unsigned int duty_value = 0;
	CLRF        main_duty_value_L0+0 
	CLRF        main_duty_value_L0+1 
	CLRF        main_speed_level_L0+0 
	CLRF        main_speed_level_L0+1 
;PWM.c,84 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;PWM.c,85 :: 		CMCON = 0x07;
	MOVLW       7
	MOVWF       CMCON+0 
;PWM.c,86 :: 		TRISB = 0xFF; // Configura PORTB como entrada para ler os bot?es
	MOVLW       255
	MOVWF       TRISB+0 
;PWM.c,89 :: 		Lcd_Init();
	CALL        _Lcd_Init+0, 0
;PWM.c,90 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;PWM.c,91 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;PWM.c,93 :: 		PWM_Init();
	CALL        _PWM_Init+0, 0
;PWM.c,95 :: 		while(1) {
L_main1:
;PWM.c,99 :: 		if (RB1_bit == 0) {
	BTFSC       RB1_bit+0, BitPos(RB1_bit+0) 
	GOTO        L_main3
;PWM.c,100 :: 		Delay_ms(50); // Debounce para o bot?o
	MOVLW       130
	MOVWF       R12, 0
	MOVLW       221
	MOVWF       R13, 0
L_main4:
	DECFSZ      R13, 1, 1
	BRA         L_main4
	DECFSZ      R12, 1, 1
	BRA         L_main4
	NOP
	NOP
;PWM.c,101 :: 		if (RB1_bit == 0) { // Confirma o clique
	BTFSC       RB1_bit+0, BitPos(RB1_bit+0) 
	GOTO        L_main5
;PWM.c,102 :: 		speed_level++;
	INFSNZ      main_speed_level_L0+0, 1 
	INCF        main_speed_level_L0+1, 1 
;PWM.c,103 :: 		if (speed_level > 4) {
	MOVLW       128
	MOVWF       R0 
	MOVLW       128
	XORWF       main_speed_level_L0+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main26
	MOVF        main_speed_level_L0+0, 0 
	SUBLW       4
L__main26:
	BTFSC       STATUS+0, 0 
	GOTO        L_main6
;PWM.c,104 :: 		speed_level = 0; // Volta para o in?cio
	CLRF        main_speed_level_L0+0 
	CLRF        main_speed_level_L0+1 
;PWM.c,105 :: 		}
L_main6:
;PWM.c,106 :: 		while(RB1_bit == 0); // Espera o bot?o ser solto
L_main7:
	BTFSC       RB1_bit+0, BitPos(RB1_bit+0) 
	GOTO        L_main8
	GOTO        L_main7
L_main8:
;PWM.c,107 :: 		}
L_main5:
;PWM.c,108 :: 		}
L_main3:
;PWM.c,111 :: 		if (RB2_bit == 0) {
	BTFSC       RB2_bit+0, BitPos(RB2_bit+0) 
	GOTO        L_main9
;PWM.c,112 :: 		Delay_ms(50); // Debounce
	MOVLW       130
	MOVWF       R12, 0
	MOVLW       221
	MOVWF       R13, 0
L_main10:
	DECFSZ      R13, 1, 1
	BRA         L_main10
	DECFSZ      R12, 1, 1
	BRA         L_main10
	NOP
	NOP
;PWM.c,113 :: 		if (RB2_bit == 0) { // Confirma o clique
	BTFSC       RB2_bit+0, BitPos(RB2_bit+0) 
	GOTO        L_main11
;PWM.c,114 :: 		speed_level--;
	MOVLW       1
	SUBWF       main_speed_level_L0+0, 1 
	MOVLW       0
	SUBWFB      main_speed_level_L0+1, 1 
;PWM.c,115 :: 		if (speed_level < 0) {
	MOVLW       128
	XORWF       main_speed_level_L0+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main27
	MOVLW       0
	SUBWF       main_speed_level_L0+0, 0 
L__main27:
	BTFSC       STATUS+0, 0 
	GOTO        L_main12
;PWM.c,116 :: 		speed_level = 4; // Volta para o m?ximo
	MOVLW       4
	MOVWF       main_speed_level_L0+0 
	MOVLW       0
	MOVWF       main_speed_level_L0+1 
;PWM.c,117 :: 		}
L_main12:
;PWM.c,118 :: 		while(RB2_bit == 0); // Espera o bot?o ser solto
L_main13:
	BTFSC       RB2_bit+0, BitPos(RB2_bit+0) 
	GOTO        L_main14
	GOTO        L_main13
L_main14:
;PWM.c,119 :: 		}
L_main11:
;PWM.c,120 :: 		}
L_main9:
;PWM.c,123 :: 		switch (speed_level) {
	GOTO        L_main15
;PWM.c,124 :: 		case 0:
L_main17:
;PWM.c,125 :: 		duty_value = 0;
	CLRF        main_duty_value_L0+0 
	CLRF        main_duty_value_L0+1 
;PWM.c,126 :: 		duty_text = "0%  ";
	MOVLW       ?lstr1_PWM+0
	MOVWF       main_duty_text_L0+0 
	MOVLW       hi_addr(?lstr1_PWM+0)
	MOVWF       main_duty_text_L0+1 
;PWM.c,127 :: 		break;
	GOTO        L_main16
;PWM.c,128 :: 		case 1:
L_main18:
;PWM.c,129 :: 		duty_value = 256; // ~25%
	MOVLW       0
	MOVWF       main_duty_value_L0+0 
	MOVLW       1
	MOVWF       main_duty_value_L0+1 
;PWM.c,130 :: 		duty_text = "25% ";
	MOVLW       ?lstr2_PWM+0
	MOVWF       main_duty_text_L0+0 
	MOVLW       hi_addr(?lstr2_PWM+0)
	MOVWF       main_duty_text_L0+1 
;PWM.c,131 :: 		break;
	GOTO        L_main16
;PWM.c,132 :: 		case 2:
L_main19:
;PWM.c,133 :: 		duty_value = 512; // ~50%
	MOVLW       0
	MOVWF       main_duty_value_L0+0 
	MOVLW       2
	MOVWF       main_duty_value_L0+1 
;PWM.c,134 :: 		duty_text = "50% ";
	MOVLW       ?lstr3_PWM+0
	MOVWF       main_duty_text_L0+0 
	MOVLW       hi_addr(?lstr3_PWM+0)
	MOVWF       main_duty_text_L0+1 
;PWM.c,135 :: 		break;
	GOTO        L_main16
;PWM.c,136 :: 		case 3:
L_main20:
;PWM.c,137 :: 		duty_value = 767; // ~75%
	MOVLW       255
	MOVWF       main_duty_value_L0+0 
	MOVLW       2
	MOVWF       main_duty_value_L0+1 
;PWM.c,138 :: 		duty_text = "75% ";
	MOVLW       ?lstr4_PWM+0
	MOVWF       main_duty_text_L0+0 
	MOVLW       hi_addr(?lstr4_PWM+0)
	MOVWF       main_duty_text_L0+1 
;PWM.c,139 :: 		break;
	GOTO        L_main16
;PWM.c,140 :: 		case 4:
L_main21:
;PWM.c,141 :: 		duty_value = 1023; // 100%
	MOVLW       255
	MOVWF       main_duty_value_L0+0 
	MOVLW       3
	MOVWF       main_duty_value_L0+1 
;PWM.c,142 :: 		duty_text = "100%";
	MOVLW       ?lstr5_PWM+0
	MOVWF       main_duty_text_L0+0 
	MOVLW       hi_addr(?lstr5_PWM+0)
	MOVWF       main_duty_text_L0+1 
;PWM.c,143 :: 		break;
	GOTO        L_main16
;PWM.c,144 :: 		}
L_main15:
	MOVLW       0
	XORWF       main_speed_level_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main28
	MOVLW       0
	XORWF       main_speed_level_L0+0, 0 
L__main28:
	BTFSC       STATUS+0, 2 
	GOTO        L_main17
	MOVLW       0
	XORWF       main_speed_level_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main29
	MOVLW       1
	XORWF       main_speed_level_L0+0, 0 
L__main29:
	BTFSC       STATUS+0, 2 
	GOTO        L_main18
	MOVLW       0
	XORWF       main_speed_level_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main30
	MOVLW       2
	XORWF       main_speed_level_L0+0, 0 
L__main30:
	BTFSC       STATUS+0, 2 
	GOTO        L_main19
	MOVLW       0
	XORWF       main_speed_level_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main31
	MOVLW       3
	XORWF       main_speed_level_L0+0, 0 
L__main31:
	BTFSC       STATUS+0, 2 
	GOTO        L_main20
	MOVLW       0
	XORWF       main_speed_level_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main32
	MOVLW       4
	XORWF       main_speed_level_L0+0, 0 
L__main32:
	BTFSC       STATUS+0, 2 
	GOTO        L_main21
L_main16:
;PWM.c,146 :: 		PWM_Set_Duty(duty_value); // Aplica o novo duty cycle
	MOVF        main_duty_value_L0+0, 0 
	MOVWF       FARG_PWM_Set_Duty_duty+0 
	MOVF        main_duty_value_L0+1, 0 
	MOVWF       FARG_PWM_Set_Duty_duty+1 
	CALL        _PWM_Set_Duty+0, 0
;PWM.c,149 :: 		Lcd_Out(1, 1, "Duty Cycle:");
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr6_PWM+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr6_PWM+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;PWM.c,150 :: 		Lcd_Out(1, 13, duty_text);
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       13
	MOVWF       FARG_Lcd_Out_column+0 
	MOVF        main_duty_text_L0+0, 0 
	MOVWF       FARG_Lcd_Out_text+0 
	MOVF        main_duty_text_L0+1, 0 
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;PWM.c,151 :: 		Lcd_Out(2, 1, "RPM: ");
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr7_PWM+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr7_PWM+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;PWM.c,152 :: 		Lcd_Out(2, 6, "0"); // RPM ainda n?o implementado
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       6
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr8_PWM+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr8_PWM+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;PWM.c,155 :: 		}
	GOTO        L_main1
;PWM.c,156 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
