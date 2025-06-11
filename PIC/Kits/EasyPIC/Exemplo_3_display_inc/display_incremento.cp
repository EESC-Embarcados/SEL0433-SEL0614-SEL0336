#line 1 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_3_display_inc/display_incremento.c"
#line 44 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_3_display_inc/display_incremento.c"
signed char ucContador = -1;




void Incremento(unsigned char Contador)
{
 switch (Contador)
#line 63 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_3_display_inc/display_incremento.c"
 {
 case 0:{ LATD = 0b00111111; break;}
 case 1:{ LATD = 0b00000110; break;}
 case 2:{ LATD = 0b01011011; break;}
 default:{ PORTD =0; ucContador = -1; break;}

 }

}




void main() {





unsigned char FlagAux = 0;
#line 98 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_3_display_inc/display_incremento.c"
 ADCON1 |= 0XF;







 TRISB.RB0 = 1;
 PORTB.RB0=1;
#line 115 "G:/Meu Drive/Pasta dinamica/Profissional/Atuação/Docencia/USP/EESC-SEL/SEL0433  0336 0614 Aplicação de Microprocessadores/2 PIC e Linguagem C/Exemplos/Exemplo_3_display_inc/display_incremento.c"
 TRISD=0;
 PORTD = 0;






while(1)
{
 if(PORTB.RB0 ==0 && FlagAux==0)


 {
 Incremento(++ucContador);



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
