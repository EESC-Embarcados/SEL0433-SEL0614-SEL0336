/* SEL0433/SEL0336 Aplic. de Microprocessadores
 ===============================================================================
 Introdu��o � Programa��o em C para Microcontroladores PIC18F usando o kit
 EasyPic v7 Mikroe.

Exemplo 3: Incrementar LEDs/Display 7 seg. ao pressionar um bot�o

- RB0 = Bot�o (PORTB)
- Display de 7 segmentos (PORTD)

- Seletor dos displays:
  PORTA - pinos RA0 (DISP0), RA1 (DISP1), RA2 (DISP2), RA3 (DISP3)

 MCU: PIC18F45K22 - alimenta��o de 3.3V - Cristal de 8 MHz

Problema do Exemplo 1: N�o possui controle sobre a a��o i.e., ao manter a
tecla pressionada, o LED fica piscando (mudando continuamente o estado)  - falta
tratamento do efeito bouncig (trepida��o mec�nica do bot�o ao press. e soltar)


Efeito bouncing -  Quando pressionamos o bot�o, for�amos o contato entre dois
condutores, imprimindo for�a no bot�o que � (energia) transferida para os contatos,
que, por sua vez, levam tempo para se estabilizarem em uma posi��o de "repouso"
(contato pleno). Enquanto esse repouso n�o � atingido, ocorrem microoscila��es
entre as posi��es aberto e fechado, com dura��o de milissegundos. O tratamento
(debouncing) pode ser feito com rotinas de delay da ordem de dezenas de ms, o que
� suficiente para ignorar a oscila��o do bot�o (bouncing) e relativamente curto
para atrasar a l�gica do programa (acender o LED ao press. o bot�o). Ao soltar o
bot�o, tamb�m existe um efeito similar, em raz�o da estabiliza��o dos contatos,
que estavam sob press�o, a voltar no estado de repouso aberto (sem contato).

Liga��es no kit EasyPIC:
   /* Habilitar a chave 4 do DIP Swit 3  (manter desligado todos os outros)
      Habilitar o display de 7 seg. DISP0 no DIP Swit 4 (pino RA0)
      Em PORTB habilitar Pull-UP apenas na chave RB0 (Pull-Up  externo)
      No circuito "Button Press Level" colocar J17 no "Com" (aterrado)
      Na alimenta��o, via USB, manter 3.3 V (padr�o do PIC18F45K22)

// No Software: em <Project> - Edit Project - desabilitar PORT A/D (disable)
================================================================================
 */

// Considera��es iniciais
signed char ucContador = -1;        // var global  para incremento
// outra op��o:
//unsigned char ucContador = 0;     // caso inciar em zero, mudar os �ndices do
// No bloco switch abaixo, seria: case 1;case 2;case 3; e default ucContador = 0

void Incremento(unsigned char Contador)   // Bloco de incremento
{
     switch (Contador)
    /* {
            case 0:{ PORTD.RD0=1; break;}   // acende LED 0 (PORTD)
            case 1:{ PORTD.RD1=1; break;}   // acende LED 1
            case 2:{ PORTD.RD2=1; break;}   // acende LED 2
            default:{ PORTD =0; ucContador = -1; break;} // zera todo o PORTD e
            //reincia o contador
     }  */

  // display de 7 segmentos + DP (ponto decimal) = 8 bits - 8 pinos do PORTD
  // LATD = 0b11111111 ; - todos os LEDs do display acesos!
  // Outros valores:
     {
            case 0:{ LATD = 0b00111111; break;}   // 0
            case 1:{ LATD = 0b00000110; break;}   // 1
            case 2:{ LATD = 0b01011011; break;}   // 2
            default:{ PORTD =0; ucContador = -1; break;} // zera todo o PORTD e
            //reincia o contador
     }

}




void main() {
// inser��o de uma vari�vel auxiliar (local ou global) para resolver o problema
//do exemplo 1!
// Uma vari�vel pode ser criada dentro ou fora do "main". Uma vari�vel local,...
//entretanto, deve estar dentro de uma fun��o.

unsigned char FlagAux = 0; // vari�vel aux. do tipo char que ir� permitir
   // encontrar o estando anterior da tecla para acionar ou n�o o LED (selo).
   // Essa vari�vel � importante para fazer com que o LED seja acionado somente
//quando ocorra uma mudan�a real, evitando acionar mais de uma vez se o estado
//ainda estiver no mesmo n�vel que provocou o acionamento.


 // Diretivas de pr�-configura��o - depende de qual PIC esta usando
 // no caso do 18F45k22, todos os pinos I/O vem pr�-config. como anal�gicos.
 // Portanto:
#ifdef P18F45K22
       ANSELB = 0;  // registrador do PIC18F45K22 - configura todos os pinos...
       //...de PORTB como digital  (lembrando que o 45K22 possui uma chave...
       //individual para cada um dos bits, separados por PORTs
       ANSELD=0; // idem - pinos do PORTD como digital
#else
    ADCON1 |= 0XF;   // outros MCUs da s�rie PIC18F (ex. PIC18F4520 e derivados)
    // possuem ADCON1, e a configura��o seria dessa forma, que j� configura
    // todos como digital
#endif

// Programa

    // Tecla  - configura��o da entrada
    TRISB.RB0 = 1;  // configura pino RB0 como entrada
    PORTB.RB0=1; //seria opcional pois internamente, ao colcoar TRISX.RX0 =1,...
    /* MCU j� coloca n�vel 1 nesta porta X (O MCU possui resistores Pull-up e
    pull-down externos -ver circuitos do kit EasyPIC).Por�m, existe uma excess�o
    que � o PORTB: ao colocar TRISB.RB0 = 1; os resistores PUll-Up desligam-se
    automaticamente */

    // LED  - sa�da: configura��o do estado inicial
    // todo PORTD como sa�da e igual a zero
    TRISD=0;
    PORTD = 0;

    //TRISD.RD0=0; // output - configura o pino como sa�da (=0) (consome corrente)
    //PORTD.RD0 = 0; // LED OFF


    // condi��es e loop para piscar o LED:
while(1) // True
{
    if(PORTB.RB0 ==0 && FlagAux==0)   // AND l�gico (express�o)
    // SE tecla � pressiona: true; e Flag = 0 (valor incial j� � 0): true.
    // Resultado: condi��o verdadeira e o bloco segue sendo executado
    {
       Incremento(++ucContador);      // recebe o Incremento do contador
       // Outra op��o: Incremento(ucContador++) //caso usar "unsiged char
       // ucContador = 0"

       FlagAux=1;        //  A condi��o acima n�o ser� mais verdadeira
       Delay_ms(40);     // tratar efeito bouncing

     }

    // Condi��o oposta para repetir o loop = tecla � liberada
     if(PORTB.RB0 ==1 && FlagAux==1)// Se a tecla n�o estiver press. e flag = 1
        {
          FlagAux=0;     // condi��o para voltar ao bloco IF anterior
          Delay_ms(40);    // tratar efeito bouncing
        }

} //while

} // main