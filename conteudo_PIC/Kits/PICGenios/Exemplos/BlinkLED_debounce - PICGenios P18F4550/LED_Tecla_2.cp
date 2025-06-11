#line 1 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_2_Tecla_LED/LED_Tecla_2.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 21 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_2_Tecla_LED/LED_Tecla_2.c"
void main() {


 unsigned char FlagAux = 0;




 ADCON1 = 0x0F;


 TRISB0_bit = 1;


 TRISD0_bit = 0;
 LATD0_bit = 0;


 while(1) {



 if(PORTB.RB0 == 0 && FlagAux == 0) {
 LATD0_bit = ~LATD0_bit;
 FlagAux = 1;


 Delay_ms(40);
 }




 if(PORTB.RB0 == 1 && FlagAux == 1) {
 FlagAux = 0;

 Delay_ms(40);
 }
 }
}
