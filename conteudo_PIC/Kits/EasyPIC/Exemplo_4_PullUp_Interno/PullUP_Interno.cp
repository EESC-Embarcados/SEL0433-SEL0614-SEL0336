#line 1 "C:/Users/pedro/Desktop/Exemplo_4_PullUp_Interno/PullUP_Interno.c"
#line 30 "C:/Users/pedro/Desktop/Exemplo_4_PullUp_Interno/PullUP_Interno.c"
void main() {








 ANSELB = 0;


 ANSELD=0;
 INTCON2.RBPU=0;

 WPUB.WPUB0 = 1;
#line 59 "C:/Users/pedro/Desktop/Exemplo_4_PullUp_Interno/PullUP_Interno.c"
 TRISB.RB0 = 1;
 PORTB.RB0=1;





 TRISD = 0;
 PORTD =0;


while(1)
{
 if(PORTB.RB0 ==0)


 {
 PORTD.RD0 =~LATD.RD0;



 Delay_ms(300);

 }


}

}
