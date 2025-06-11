/* SEL0433/SEL0336 Aplic. de Microprocessadores
 ===============================================================================
 Introdução à Programação em C para Microcontroladores PIC18F usando o kit
 EasyPic v7 Mikroe.

Exemplo 3: Incrementar LEDs/Display 7 seg. ao pressionar um botão

- RB0 = Botão (PORTB)
- Display de 7 segmentos (PORTD)

- Seletor dos displays:
  PORTA - pinos RA0 (DISP0), RA1 (DISP1), RA2 (DISP2), RA3 (DISP3)

 MCU: PIC18F45K22 - alimentação de 3.3V - Cristal de 8 MHz

Problema do Exemplo 1: Não possui controle sobre a ação i.e., ao manter a
tecla pressionada, o LED fica piscando (mudando continuamente o estado)  - falta
tratamento do efeito bouncig (trepidação mecânica do botão ao press. e soltar)


Efeito bouncing -  Quando pressionamos o botão, forçamos o contato entre dois
condutores, imprimindo força no botão que é (energia) transferida para os contatos,
que, por sua vez, levam tempo para se estabilizarem em uma posição de "repouso"
(contato pleno). Enquanto esse repouso não é atingido, ocorrem microoscilações
entre as posições aberto e fechado, com duração de milissegundos. O tratamento
(debouncing) pode ser feito com rotinas de delay da ordem de dezenas de ms, o que
é suficiente para ignorar a oscilação do botão (bouncing) e relativamente curto
para atrasar a lógica do programa (acender o LED ao press. o botão). Ao soltar o
botão, também existe um efeito similar, em razão da estabilização dos contatos,
que estavam sob pressão, a voltar no estado de repouso aberto (sem contato).

Ligações no kit EasyPIC:
   /* Habilitar a chave 4 do DIP Swit 3  (manter desligado todos os outros)
      Habilitar o display de 7 seg. DISP0 no DIP Swit 4 (pino RA0)
      Em PORTB habilitar Pull-UP apenas na chave RB0 (Pull-Up  externo)
      No circuito "Button Press Level" colocar J17 no "Com" (aterrado)
      Na alimentação, via USB, manter 3.3 V (padrão do PIC18F45K22)

// No Software: em <Project> - Edit Project - desabilitar PORT A/D (disable)
================================================================================
 */

// Considerações iniciais
signed char ucContador = -1;        // var global  para incremento
// outra opção:
//unsigned char ucContador = 0;     // caso inciar em zero, mudar os índices do
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
// inserção de uma variável auxiliar (local ou global) para resolver o problema
//do exemplo 1!
// Uma variável pode ser criada dentro ou fora do "main". Uma variável local,...
//entretanto, deve estar dentro de uma função.

unsigned char FlagAux = 0; // variável aux. do tipo char que irá permitir
   // encontrar o estando anterior da tecla para acionar ou não o LED (selo).
   // Essa variável é importante para fazer com que o LED seja acionado somente
//quando ocorra uma mudança real, evitando acionar mais de uma vez se o estado
//ainda estiver no mesmo nível que provocou o acionamento.


 // Diretivas de pré-configuração - depende de qual PIC esta usando
 // no caso do 18F45k22, todos os pinos I/O vem pré-config. como analógicos.
 // Portanto:
#ifdef P18F45K22
       ANSELB = 0;  // registrador do PIC18F45K22 - configura todos os pinos...
       //...de PORTB como digital  (lembrando que o 45K22 possui uma chave...
       //individual para cada um dos bits, separados por PORTs
       ANSELD=0; // idem - pinos do PORTD como digital
#else
    ADCON1 |= 0XF;   // outros MCUs da série PIC18F (ex. PIC18F4520 e derivados)
    // possuem ADCON1, e a configuração seria dessa forma, que já configura
    // todos como digital
#endif

// Programa

    // Tecla  - configuração da entrada
    TRISB.RB0 = 1;  // configura pino RB0 como entrada
    PORTB.RB0=1; //seria opcional pois internamente, ao colcoar TRISX.RX0 =1,...
    /* MCU já coloca nível 1 nesta porta X (O MCU possui resistores Pull-up e
    pull-down externos -ver circuitos do kit EasyPIC).Porém, existe uma excessão
    que é o PORTB: ao colocar TRISB.RB0 = 1; os resistores PUll-Up desligam-se
    automaticamente */

    // LED  - saída: configuração do estado inicial
    // todo PORTD como saída e igual a zero
    TRISD=0;
    PORTD = 0;

    //TRISD.RD0=0; // output - configura o pino como saída (=0) (consome corrente)
    //PORTD.RD0 = 0; // LED OFF


    // condições e loop para piscar o LED:
while(1) // True
{
    if(PORTB.RB0 ==0 && FlagAux==0)   // AND lógico (expressão)
    // SE tecla é pressiona: true; e Flag = 0 (valor incial já é 0): true.
    // Resultado: condição verdadeira e o bloco segue sendo executado
    {
       Incremento(++ucContador);      // recebe o Incremento do contador
       // Outra opção: Incremento(ucContador++) //caso usar "unsiged char
       // ucContador = 0"

       FlagAux=1;        //  A condição acima não será mais verdadeira
       Delay_ms(40);     // tratar efeito bouncing

     }

    // Condição oposta para repetir o loop = tecla é liberada
     if(PORTB.RB0 ==1 && FlagAux==1)// Se a tecla não estiver press. e flag = 1
        {
          FlagAux=0;     // condição para voltar ao bloco IF anterior
          Delay_ms(40);    // tratar efeito bouncing
        }

} //while

} // main