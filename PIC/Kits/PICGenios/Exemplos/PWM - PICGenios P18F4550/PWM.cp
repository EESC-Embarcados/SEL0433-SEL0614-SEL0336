#line 1 "D:/mikroc/mikroC PRO for PIC/Examples/Development Systems/EasyPIC v8/PWM/PWM.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, BOR = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 18 "D:/mikroc/mikroC PRO for PIC/Examples/Development Systems/EasyPIC v8/PWM/PWM.c"
sbit LCD_RS at LATE2_bit;
sbit LCD_EN at LATE1_bit;
sbit LCD_D4 at LATD4_bit;
sbit LCD_D5 at LATD5_bit;
sbit LCD_D6 at LATD6_bit;
sbit LCD_D7 at LATD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


char txt1[] = "PICSimLab";
char txt2[] = "PICGenios";
char txt3[] = "LCD Funcionando!";
char txt4[] = "Pinos Corretos";

char i;

void Move_Delay() {
 Delay_ms(400);
}






void PWM_Init() {
 TRISC2_bit = 0;


 PR2 = 255;



 T2CON = 0b00000101;



 CCP1CON = 0b00001100;
}



void PWM_Set_Duty(unsigned int duty) {

 CCPR1L = duty >> 2;


 CCP1CON = (CCP1CON & 0b11001111) | ((duty & 0b11) << 4);
}


void main() {
 unsigned int duty_value = 0;
 char *duty_text;


 int speed_level = 0;



 ADCON1 = 0x0F;
 CMCON = 0x07;
 TRISB = 0xFF;


 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 PWM_Init();

 while(1) {



 if (RB1_bit == 0) {
 Delay_ms(50);
 if (RB1_bit == 0) {
 speed_level++;
 if (speed_level > 4) {
 speed_level = 0;
 }
 while(RB1_bit == 0);
 }
 }


 if (RB2_bit == 0) {
 Delay_ms(50);
 if (RB2_bit == 0) {
 speed_level--;
 if (speed_level < 0) {
 speed_level = 4;
 }
 while(RB2_bit == 0);
 }
 }


 switch (speed_level) {
 case 0:
 duty_value = 0;
 duty_text = "0%  ";
 break;
 case 1:
 duty_value = 256;
 duty_text = "25% ";
 break;
 case 2:
 duty_value = 512;
 duty_text = "50% ";
 break;
 case 3:
 duty_value = 767;
 duty_text = "75% ";
 break;
 case 4:
 duty_value = 1023;
 duty_text = "100%";
 break;
 }

 PWM_Set_Duty(duty_value);


 Lcd_Out(1, 1, "Duty Cycle:");
 Lcd_Out(1, 13, duty_text);
 Lcd_Out(2, 1, "RPM: ");
 Lcd_Out(2, 6, "0");


 }
}
