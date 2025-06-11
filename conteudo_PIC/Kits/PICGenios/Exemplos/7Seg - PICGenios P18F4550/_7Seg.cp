#line 1 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/7Seg - PICGenios P18F4550/_7Seg.c"
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON
#line 19 "C:/Users/pedro/USP/PIC/PICSimLab/PICGenios/Exemplos/7Seg - PICGenios P18F4550/_7Seg.c"
signed char ucContador = -1;


void Incremento(unsigned char Contador) {
 switch (Contador) {

 case 0: { LATD = 0b00111111; break; }
 case 1: { LATD = 0b00000110; break; }
 case 2: { LATD = 0b01011011; break; }
 default:{ LATD = 0; ucContador = -1; break; }
 }
}

void main() {

 unsigned char FlagAux = 0;


 ADCON1 = 0x0F;



 TRISB0_bit = 1;



 TRISD = 0;
 LATD = 0;



 TRISA2_bit = 0;
 TRISA3_bit = 0;
 TRISA4_bit = 0;
 TRISA5_bit = 0;

 LATA2_bit = 0;
 LATA3_bit = 0;
 LATA4_bit = 0;
 LATA5_bit = 1;


 while(1) {

 if (PORTB.RB0 == 0 && FlagAux == 0) {



 Incremento(++ucContador);

 FlagAux = 1;
 Delay_ms(40);
 }


 if (PORTB.RB0 == 1 && FlagAux == 1) {


 FlagAux = 0;
 Delay_ms(40);
 }
 }
}
