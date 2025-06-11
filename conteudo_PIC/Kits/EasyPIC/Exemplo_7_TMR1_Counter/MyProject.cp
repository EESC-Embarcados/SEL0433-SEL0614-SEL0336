#line 1 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_7_TMR1_Counter/MyProject.c"
#line 27 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/Aulas/v2/exemplos/Exemplo_7_TMR1_Counter/MyProject.c"
void main() {

ADCON1=0x0F;

TRISC.RC0=1;





PORTC.RC0=1;

TRISD=0;
PORTD=0;

PORTD.RD1=0;

T1CON =0B10000011;


TMR1H=0xFF;
TMR1L=0xF6;

PIR1.TMR1IF=0;


while(1){
 if(TMR1IF_bit){
 PORTD.RD1=1;
 TMR1H=0xFF;
 TMR1L=0xF6;
 PIR1.TMR1IF=0;
 Delay_ms(1000);
 }
 else{
 PORTD.RD1=0;
 }

 }

}
