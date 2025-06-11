#line 1 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_2_Tecla_LED/LED_Tecla_2.c"
#line 36 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_2_Tecla_LED/LED_Tecla_2.c"
void main() {







unsigned char FlagAux = 0;
#line 60 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_2_Tecla_LED/LED_Tecla_2.c"
 ADCON1 |= 0XF;







 trisb.rb0 = 1;
 PORTB.RB0=1;
#line 76 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_2_Tecla_LED/LED_Tecla_2.c"
 TRISD.RD0=0;
 PORTD.RD0 = 0;





while(1)
{

 if(PORTB.RB0 ==0 && FlagAux==0)


 {
 LATD.RD0 =~LATD.RD0;



 FlagAux=1;


 Delay_ms(40);



 }




 if(PORTB.RB0 ==1 && FlagAux==1)
 {
 FlagAux=0;
 Delay_ms(40);
 }

}

}
