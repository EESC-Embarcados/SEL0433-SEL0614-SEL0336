 /* SEL0433/SEL0336 Aplic. de Microprocessadores
 ===============================================================================

Exemplo 2: Continuação do Exemplo 1 - Ao pressionar uma tecla, o nível lógico
de um LED deve mudar
- RB0 = TECLA (PORTB)
- RD0 = LED  (PORTD)
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



MCU: PIC18F45K22 - alimentação de 3.3V - Cristal de 8 MHz
// Ligações no kit EasyPIC
   /* Habilitar a chave 4 do DIP Swit 3  (manter desligado todos os outros)
      Em PORTB habilitar RN2 em Pull-UP apenas na chave RB0 (Pull-Up  externo)
      No circuito "Button Press Level" colocar J17 no "Com" (aterrado)
      Na alimentação, via USB, manter 3.3 V (padrão do PIC18F45K22)

//
================================================================================
*/
// Início
void main() {
// Considerações iniciais

// A novidade aqui é a inserção de uma variável auxiliar (local ou global) para 
//resolver o problema do exemplo 1!
// Uma variável pode ser criada dentro ou fora do "main". Uma variável local,...
//entretanto, deve estar dentro de uma função.

unsigned char FlagAux = 0; // variável aux. do tipo char que irá permitir
// encontrar o estado anterior do botão, para acionar ou não o LED (selo).
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
    ADCON1 |= 0XF;  // outros MCUs da série PIC18F (ex. PIC18F4520 e derivados)
    // possuem ADCON1, e a configuração seria dessa forma, que já configura
    // todos como digital
#endif

// Programa

    // Tecla  - configuração da entrada
    trisb.rb0 = 1;  // configura pino RB0 como entrada
    PORTB.RB0=1; //seria opcional pois internamente, ao colcoar TRISX.RX0 =1,...
    /* MCU já coloca nível 1 nesta porta X (O MCU possui resistores Pull-up e
    pull-down externos -ver circuitos do kit EasyPIC).Porém, existe uma excessão
    que é o PORTB: ao colocar TRISB.RB0 = 1; os resistores PUll-Up desligam-se
    automaticamente */

    // LED  - saída: configuração do estado inicial
    TRISD.RD0=0; // output - configura o pino como saída (=0) (consome corrente)
    PORTD.RD0 = 0; // LED OFF
    
    // TRISD = 0; // todos os pinos como saída
    // PORTD =0; //todos os pinos = 0

    // condições e loop para piscar o LED:
while(1) // True
{

   if(PORTB.RB0 ==0 && FlagAux==0)   // AND lógico (expressão)
    // SE tecla é pressiona: true; E Flag = 0 (lembrando que valor incial já é
    //= 0): true. Resultado: condição verdadeira e o bloco segue sendo executado
    {
       LATD.RD0 =~LATD.RD0; // (TOOGGLE) Inverte o nível lógico do LED em LATD
       // "~ "  inversão bit a bit  - SE incialmente RD0 = 0, receberá 1 quando
       // a teclada for pressionada; SE 1, receberá o valor 0
       
       FlagAux=1;        //  A condição acima não será mais verdadeira - (aqui
       // certamente o botão ainda estará pressionado - pois é execução é muito rápida)
       
       Delay_ms(40);     // trata efeito bouncing (repique mecânico do botão,
       //dentro deste intervalo de tempo não será considerado)
       

     } //fim do bloco IF, o qual em caso de falso (a tecla não for pressionada
     //ou continua pressiona (devido a velocidade do MCU - nanosegundos) mas a
     // Flag = 1), será pulado.

    // Condição oposta para repetir o loop = tecla é liberada
     if(PORTB.RB0 ==1 && FlagAux==1)// Se a tecla não estiver press. E flag = 1
       {
          FlagAux=0;     // condição para voltar ao bloco IF anterior
          Delay_ms(40);  // trata efeito bouncing
        }
     
} //while

} // main