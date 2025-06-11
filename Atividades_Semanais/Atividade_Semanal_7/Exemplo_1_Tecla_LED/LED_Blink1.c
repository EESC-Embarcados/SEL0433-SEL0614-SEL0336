 /* SEL0433/SEL0336 Aplic. de Microprocessadores
 ===============================================================================
 Introdu��o � Programa��o em C para Microcontroladores PIC18F usando o kit
 EasyPic v7 Mikroe.   
 
 Uso dos registradores TRISX (dire��o - define como entrada (leitura): bit 1; 
 ou sa�da(escrita): bit 0)
 PORTX(leitura de dados de entrada (se TRISX =1))
 e LATX (modifica /escreve dados na sa�da - se TRISX = 0)
 
 Portando: TRISx = 1 define o pino como entrada,ativando o input buffer interno
 do microcontrolador, bloqueando LATx (desconectando) do pino e, portanto, n�o permite
 escrita, somente leitura em PORTx
 
 Por outro lado, TRISx = 0 ativa um buffer tristate que conecta LATx ao pino,
 permitindo opera��o de escrita
===============================================================================
 Conhecendo os PORTs (I/O) do PIC18F - uso de entradas e sa�das

Exemplo 1: Ao pressionar uma tecla/bot�o (entrada), o n�vel l�gico de um LED
deve mudar (sa�da)
 - RB0 = TECLA/bot�o (PORTB)
 - RD0 = LED  (PORTD)

 MCU: PIC18F4550- alimenta��o de 5V - Cristal externo de 8 MHz

Liga��es no kit EasyPIC:
   > Habilitar a chave 4 do DIP Swit 3  (manter desligado todos os outros)
   > Em PORTB habilitar chave RN2 em Pull-UP apenas na chave RB0
   > No circuito "Button Press Level" colocar J17 no "Com" (aterrado)
   > Na alimenta��o, via USB, manter 3.3 V (padr�o do PIC18F45K22)

================================================================================
  */

// In�cio - fun��o principal
void main() {
// Considera��es iniciais

 // Diretivas de pr�-configura��o - depende de qual PIC ser� usado
 // No caso do 18F45k22, todos os pinos I/O vem pr�-config. como anal�gicos.
 // Portanto:
#ifdef P18F45K22
       ANSELB = 0;  // registrador do PIC18F45K22 - configura todos os pinos...
       //...de PORTB como digital  (lembrando que o 18F45K22 possui uma chave...
       //individual para cada um dos bits, separados por PORTs
       ANSELD=0; // idem - pinos do PORTD como digital
#else
    ADCON1 |= 0XF;  // outros MCUs da s�rie PIC18F (ex. PIC18F4550 e derivados)
    // possuem ADCON1, e a configura��o seria dessa forma, que j� configura
    // todos como digital
#endif

// Programa

    // Configura��o da entrada = Tecla
    TRISB.RB0 = 1;  // configura pino RB0 como entrada no PORTB
    PORTB.RB0=1; //seria opcional pois internamente, ao colocar TRISX.RX0 =1,...
    /* MCU j� coloca n�vel 1 nesta porta X (O MCU possui resistores Pull-up e 
    pull-down externos -ver circuitos do kit EasyPIC).Por�m, existe uma excess�o
    que � o PORTB: ao colocar TRISB.RB0 = 1; os resistores PUll-Up desligam-se
    automaticamente */
    
    // Sa�da (LED): configura��o do estado inicial
    TRISD.RD0=0; // output - configura o pino como sa�da (=0) (consome corrente)
    LATD.RD0 = 0; // LED OFF

// condi��es e loop para piscar o LED:
while(1) // True
{
    if(PORTB.RB0 ==0)   // Tecla ativada em n�vel l�gico 0 (SE o pino estiver ..
    // aterrado..)
    {
       LATD.RD0 =~LATD.RD0; // Inverte o n�vel l�gico do LED em LATD
       // "~ "  invers�o bit a bit  - SE incialmente RD0 = 0, receber� 1 quando
       // a teclada for pressionada; SE 1, receber� o valor 0
       Delay_ms(300);     // retarda a CPU de forma que ao pressionar a tecla..
       // a a��o de fato aconte�a (as intru��es s�o executadas em nanosegundos)

     }  //fim do bloco IF, o qual em caso de falso (a tecla n�o for pressionada)
     //...ser� pulado.
     
     /*  Abaixo um exemplo de loop simples, somente para piscar LED independente
     da tecla:
        LATD.RD0= 1;   // acende o LED
        Delay_ms(300);  // delay de 300 ms  aceso
        LATD.RD0=0;    // apaga o LED
        Delay_ms(300);  // delay de 300 ms apagado
        */
} //while

} // main