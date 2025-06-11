#line 1 "D:/mikroc/mikroC PRO for PIC/Examples/Development Systems/EasyPIC v8/Lcd/Lcd.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, BOR = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 18 "D:/mikroc/mikroC PRO for PIC/Examples/Development Systems/EasyPIC v8/Lcd/Lcd.c"
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
char txt3[] = "LCD Agora Vai!";
char txt4[] = "Pinos Corretos";

char i;

void Move_Delay() {
 Delay_ms(400);
}

void main(){


 ADCON1 = 0x0F;
 CMCON = 0x07;

 Lcd_Init();

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 Lcd_Out(1, 1, txt3);
 Lcd_Out(2, 1, txt4);
 Delay_ms(2500);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1, 4, txt1);
 Lcd_Out(2, 4, txt2);
 Delay_ms(2500);

 while(1) {
 for(i=0; i<7; i++) {
 Lcd_Cmd(_LCD_SHIFT_LEFT);
 Move_Delay();
 }
 for(i=0; i<7; i++) {
 Lcd_Cmd(_LCD_SHIFT_RIGHT);
 Move_Delay();
 }
 }
}
