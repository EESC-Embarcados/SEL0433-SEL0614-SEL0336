#line 1 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_10_ADC_LCD/Exemplo_10_ADC.c"
#line 23 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_10_ADC_LCD/Exemplo_10_ADC.c"
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;



void main() {
 unsigned int Leitura_ADC;
 unsigned char Texto[10];


TRISA.RA5=1;









ADCON0 = 0B00010001;
ADCON1 = 0B00000000;

ADCON2 = 0B10101010;



 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"ADC: ");

 while(1)
 {
 ADCON0.GO_DONE = 1;
 while(ADCON0.GO_DONE == 1);





 Leitura_ADC = ((ADRESH << 8)| ADRESL);
#line 102 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_10_ADC_LCD/Exemplo_10_ADC.c"
 WordToStr(Leitura_ADC, Texto);
 LCD_Out(1,5, Texto);
 Delay_ms(20);

 }

}
