#line 1 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_10_ADC_LCD/Exemplo_10_ADC.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 29 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_10_ADC_LCD/Exemplo_10_ADC.c"
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


void main() {
 unsigned int Leitura_ADC;
 char Texto[7];




 ADCON1 = 0x0E;


 TRISA0_bit = 1;



 ADCON2 = 0b10101010;


 ADCON0 = 0b00000001;

 Delay_ms(2);



 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 1, "Leitura AN0:");


 while(1) {

 ADCON0.GO_DONE = 1;


 while(ADCON0.GO_DONE == 1);


 Leitura_ADC = (ADRESH << 8) | ADRESL;


 WordToStr(Leitura_ADC, Texto);


 Lcd_Out(2, 5, "      ");
 Lcd_Out(2, 5, Texto);

 Delay_ms(100);
 }
}
