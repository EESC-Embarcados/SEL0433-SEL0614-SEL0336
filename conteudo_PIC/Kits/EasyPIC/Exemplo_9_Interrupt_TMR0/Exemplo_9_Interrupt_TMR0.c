 /* SEL0433/SEL0336/SEL0614 - Aplic. de Microprocessadores
 
 - conceitos sobre interrupções

 - Programando interrupções internas a partir de evento gerado em periféricos
  do microcontrolador (ex: overflow do timer, conversor AD, PWM etc)

- Exemplo: programação da interrupção interna do temporizador TMR0, i.e, quando
 ocorre o overflow de uma contagem de tempo de 200 ms (TMR0IF =1), aciona a
 interrupção, cujo tratamento do evento é o  blink de um LED que irá sinalizar
 o evento ocorrio. Assim, um LED irá piscar a cada overflow do timer.

//*****************************************
1° Configuração da Temporização do timer
2° Configuração da "chave geral" das interrupções
3° Configuração da interrupção particular
4° Escrita dos vetores de interrupção (HIGH OU LOW)
5° Subrotina de interrupção
//******************************************
*/


//Protótipo de Funções
void ConfigMCU();
void ConfigTIMER();
void ConfigInterrupt();


//Rotina Especial de Interrupção gerada pelo Assistante do mikroC
// menu Tools > Interrupt Assistant
void Interrupt_HIGH() iv 0x0008 ics ICS_AUTO {   //Alta prioridade de interrupção

   if(INTCON.TMR0IF == 1)    //Foi o TIMER0 que gerou a interrupção ?
    {
      PORTD.RD2 = ~LATD.RD2; //PISCA O LED no PORTD

      TMR0H = 0XCF;          //Recarregar o TIMER para 200ms
      TMR0L = 0X2C;
      INTCON.TMR0IF = 0;   //Não esquecer de zerar a Flag, pois é responsável por
      //acionar a interrupção
    }

}    // Fim da subrotina de interrupção
// Assim, o tratamento da interrupção é inverter o estado de uma saída digital (LED)
// e recarregar o timer, sempre que o overflow ocorrer!

void ConfigMCU()
{
 ADCON1 |= 0X0F;    // pinos do microcontrolador como digitais

 TRISD = 0;       //Configurar os pinos de controle dos LEDs
 PORTD = 0;      // inicialmente desligado
}

void ConfigTIMER()
{
//*******************TIMER0 PARA 200ms*********************************
//CicloMaquina = Fosc/4 -> 8MHz/4 = 2MHz -> Periodo = 1/F -> 1/2MHz = 0.5us

//Time_overflow = CicloMaq. * Prescaler * (Modo_8_16bits - valor Inicial)
//200.000us    = 0.5us * 32 * (65536 -  X)
//X = 65536 - 12500 = 53036  -> converter valor para HEX: CF2C

//******************************************************************************
  T0CON = 0B00000100;  //TIMER_OFF, MOD_16BITS, TIMER, PRES_1:32
  TMR0H = 0XCF;   // Carga do valor inicial
  TMR0L = 0X2C;

  INTCON.TMR0IF = 0;  //zera a Flag  (vai p/ 1 quando ocorrer o overflow)
  T0CON.TMR0ON = 1;   //Liga o TIMER0
}

void ConfigInterrupt()
{
  INTCON.GIE = 1;   //Chave Geral, Habilita o uso de interrupção
  //INTCON.GIELH = 1;   //Habilita o vetor de alta prioridade
  RCON.IPEN = 0; //0 -> (default) herança da família PIC16F, onde existe apenas
                            //um nível de prioridade de interrupção
                     //IPEN=1 -> dois níveis de prioridade de interrupção (PIC18)


// IF, IP, IE + periférico
//TMR0 + IF = TMR0IF
// TMR0 + IP = TMR0IP
// ' ' = TMR0IE
// Registradores que contem os bits TMR0IF e TMR0IE = INTCON; 
//TMR0IP = INTCON2

 // INTCON.TMR0IF = 0;   //Flag de estouro do TIMER0. Deve iniciar em 0
  //INTCON2.TMR0IP = 1;  //Prioridade de interrupção do TIMER0. Conf. em Alta prioridade
  INTCON.TMR0IE = 1;   //Habilita a interrupção individual do TIMER0
}


void main() {
   ConfigMCU();           //pinos do MCU config. para acionar os LEDS
   ConfigTIMER();         // tempo config. e TIMER ligado
   ConfigInterrupt(); //Configuração global das interrupções


  while(1) {  // Endless loop
 } //while
 } //main