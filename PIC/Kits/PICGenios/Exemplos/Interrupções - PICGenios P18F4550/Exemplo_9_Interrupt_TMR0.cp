#line 1 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_9_Interrupt_TMR0/Exemplo_9_Interrupt_TMR0.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 21 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/Exemplo_9_Interrupt_TMR0/Exemplo_9_Interrupt_TMR0.c"
void ConfigMCU();
void ConfigTIMER();
void ConfigInterrupt();





void Interrupt() iv 0x0008 ics ICS_AUTO {


 if (TMR0IF_bit == 1) {

 LATD2_bit = ~LATD2_bit;


 TMR0H = 0xCF;
 TMR0L = 0x2C;


 TMR0IF_bit = 0;
 }
}


void ConfigMCU() {
 ADCON1 = 0x0F;
 TRISD = 0;
 LATD = 0;
}


void ConfigTIMER() {



 T0CON = 0b00000100;
 TMR0H = 0xCF;
 TMR0L = 0x2C;
 TMR0ON_bit = 1;
}


void ConfigInterrupt() {
 RCON.IPEN = 0;
 GIE_bit = 1;
 TMR0IE_bit = 1;
 TMR0IF_bit = 0;
}


void main() {
 ConfigMCU();
 ConfigTIMER();
 ConfigInterrupt();




 while(1) {
 }
}
