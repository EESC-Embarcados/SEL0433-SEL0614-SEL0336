#line 1 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_9_Interrupt_TMR0/Exemplo_9_Interrupt_TMR0.c"
#line 24 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_9_Interrupt_TMR0/Exemplo_9_Interrupt_TMR0.c"
void ConfigMCU();
void ConfigTIMER();
void ConfigInterrupt();




void Interrupt_HIGH() iv 0x0008 ics ICS_AUTO {

 if(INTCON.TMR0IF == 1)
 {
 PORTD.RD2 = ~LATD.RD2;

 TMR0H = 0XCF;
 TMR0L = 0X2C;
 INTCON.TMR0IF = 0;

 }

}



void ConfigMCU()
{
 ADCON1 |= 0X0F;

 TRISD = 0;
 PORTD = 0;
}

void ConfigTIMER()
{








 T0CON = 0B00000100;
 TMR0H = 0XCF;
 TMR0L = 0X2C;

 INTCON.TMR0IF = 0;
 T0CON.TMR0ON = 1;
}

void ConfigInterrupt()
{
 INTCON.GIE = 1;

 RCON.IPEN = 0;
#line 91 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_9_Interrupt_TMR0/Exemplo_9_Interrupt_TMR0.c"
 INTCON.TMR0IE = 1;
}


void main() {
 ConfigMCU();
 ConfigTIMER();
 ConfigInterrupt();


 while(1) {
 }
 }
