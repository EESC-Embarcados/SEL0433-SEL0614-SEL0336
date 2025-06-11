/* SEL0433/SEL0336 Aplic. de Microprocessadores
 ===============================================================================
 Introdu��o � Programa��o em C para Microcontroladores PIC18F usando o kit
 EasyPic v7 Mikroe.
 
Exemplo 4: Como habilitar resistores pull-up internos e n�o precisar usar
os externos habilitados pelas chaves RNx

- RB0 = TECLA (PORTB)
- RD0 = LED  (PORTD)

 MCU: PIC18F45K22 - alimenta��o de 3.3V - Cristal de 8 MHz


// Liga��es no kit EasyPIC
   /* Habilitar a chave 4 do DIP Swit 3  (manter desligado todos os outros)
      Desabilitar pull-up externo da chave RN2.RB0 (manter chaves no meio)
      No circuito "Button Press Level" colocar J17 em GND
      Na alimenta��o, via USB, manter 3.3 V (padr�o do PIC18F45K22)

// No Software: em <Project> - Edit Project - desabilitar PORT A/D (disable)

================================================================================
  */
  
  
#define TRUE 1               // outra forma de colocar var 1 no While

// In�cio
void main() {

// Considera��es iniciais

 // diretivas de pr�-configura��o - depende de qual PIC18F esta usando
 // no caso do 45k22, todos os pinos I/O vem pr�-config. como anal�gicos.
 //  os resistores pull-up s�o manpinulados normalmente no PORTB deste modelo
 // Portanto:
#ifdef P18F45K22
       ANSELB = 0;  // registrador do PIC18F45K22 - configura todos os pinos...
       //...de PORTB como digital  (lembrando que o 18F45K22 possui uma chave...
       //individual para cada um dos bits, separados por PORTs
       ANSELD=0; // idem - pinos do PORTD como digital
       INTCON2.RBPU=0; // Habilita chave global dos resistores pull-up presente
                      // no PORTB
       WPUB.WPUB0 = 1; // Habilita o resistor pull-up interno no pino RB0
       
#else
    ADCON1 |= 0X0F;   // outros MCUs da s�rie PIC18F (ex.PIC18F4550 e derivados)
    // possuem ADCON1, e a configura��o seria dessa forma, que j� configura
    // todos como digital
    INTCON2.RBPU=0;   // Habilitando pull-up interno em outro modelo PIC
    // j� que em outras familias n�o exite o WPUB usado acima p/ 45K22. 
    //Neste caso, � usado RBPU
#endif

// Programa

    // Tecla  - configura��o da entrada
    TRISB.RB0 = 1;  // configura pino RB0 como entrada
    PORTB.RB0=1; // n�vel 1 (VCC - pull-up)

    // LED  - sa�da: configura��o do estado inicial
    //TRISD.RD0=0; //output - configura o pino como sa�da (=0)(consome corrente)
    //PORTD.RD0 = 0; // LED OFF

    TRISD = 0; // todos os pinos como sa�da
    PORTD =0; //todos os pinos = 0

    // condi��es e loop para piscar o LED:
while(1) // True
{
    if(PORTB.RB0 ==0)   // AND l�gico (express�o)
    // SE tecla � pressiona: true; e Flag = 0 (valor incial j� � 0): true.
    // Resultado: condi��o verdadeira e o bloco segue sendo executado
    {
       PORTD.RD0 =~LATD.RD0; // (TOOGGLE) Inverte o n�vel l�gico do LED em LAT D
       // "~ "  invers�o bit a bit  - SE incialmente RD0 = 0, receber� 1 quando
       // a teclada for pressionada; SE 1, receber� o valor 0

       Delay_ms(300);

     }


} //while

} // main