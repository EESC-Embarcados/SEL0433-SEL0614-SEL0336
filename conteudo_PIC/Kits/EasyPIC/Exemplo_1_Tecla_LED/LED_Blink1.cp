#line 1 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
#line 37 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
void main() {
#line 49 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
 ADCON1 |= 0XF;







 TRISB.RB0 = 1;
 PORTB.RB0=1;
#line 65 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
 TRISD.RD0=0;
 LATD.RD0 = 0;


while(1)
{
 if(PORTB.RB0 ==0)

 {
 LATD.RD0 =~LATD.RD0;


 Delay_ms(300);


 }
#line 90 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_1_Tecla_LED/LED_Blink1.c"
}

}
