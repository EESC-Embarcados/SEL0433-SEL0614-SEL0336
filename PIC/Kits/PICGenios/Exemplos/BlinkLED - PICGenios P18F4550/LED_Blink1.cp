#line 1 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 15 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
void main() {



 ADCON1 = 0x0F;


 TRISB0_bit = 1;


 TRISD0_bit = 0;
 LATD0_bit = 0;

 LATA5_bit = 1;


 while(1) {

 if(PORTB.RB0 == 0) {

 LATD0_bit = ~LATD0_bit;


 Delay_ms(300);
 }
 }
}
