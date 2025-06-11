#line 1 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_7_TMR1_Counter/MyProject.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 36 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_7_TMR1_Counter/MyProject.c"
void main() {


 ADCON1 = 0x0F;
 TRISC0_bit = 1;
 TRISD = 0;
 LATD = 0;



 T1CON = 0b10110011;


 TMR1H = 0xFF;
 TMR1L = 0xF6;
 TMR1IF_bit = 0;


 while(1) {

 if (TMR1IF_bit == 1) {
 LATD1_bit = 1;


 TMR1H = 0xFF;
 TMR1L = 0xF6;
 TMR1IF_bit = 0;

 Delay_ms(1000);
 }
 else {

 LATD1_bit = 0;
 }
 }
}
