 /* SEL0433/SEL0336 Aplic. de Microprocessadores
 ===============================================================================
 Introdução à Programação em C para Microcontroladores PIC18F usando o kit
 EasyPic v7 Mikroe.   
 
 Uso dos registradores TRISX (direção - define como entrada (leitura): bit 1; 
 ou saída(escrita): bit 0)
 PORTX(leitura de dados de entrada (se TRISX =1))
 e LATX (modifica /escreve dados na saída - se TRISX = 0)
 
 Portando: TRISx = 1 define o pino como entrada,ativando o input buffer interno
 do microcontrolador, bloqueando LATx (desconectando) do pino e, portanto, não permite
 escrita, somente leitura em PORTx
 
 Por outro lado, TRISx = 0 ativa um buffer tristate que conecta LATx ao pino,
 permitindo operação de escrita
===============================================================================
 Conhecendo os PORTs (I/O) do PIC18F - uso de entradas e saídas

Exemplo 1: Ao pressionar uma tecla/botão (entrada), o nível lógico de um LED
deve mudar (saída)
 - RB0 = TECLA/botão (PORTB)
 - RD0 = LED  (PORTD)

 MCU: PIC18F4550- alimentação de 5V - Cristal externo de 8 MHz

Ligações no kit EasyPIC:
   > Habilitar a chave 4 do DIP Swit 3  (manter desligado todos os outros)
   > Em PORTB habilitar chave RN2 em Pull-UP apenas na chave RB0
   > No circuito "Button Press Level" colocar J17 no "Com" (aterrado)
   > Na alimentação, via USB, manter 3.3 V (padrão do PIC18F45K22)

================================================================================
  */

// Início - função principal
void main() {
// Considerações iniciais

 // Diretivas de pré-configuração - depende de qual PIC será usado
 // No caso do 18F45k22, todos os pinos I/O vem pré-config. como analógicos.
 // Portanto:
#ifdef P18F45K22
       ANSELB = 0;  // registrador do PIC18F45K22 - configura todos os pinos...
       //...de PORTB como digital  (lembrando que o 18F45K22 possui uma chave...
       //individual para cada um dos bits, separados por PORTs
       ANSELD=0; // idem - pinos do PORTD como digital
#else
    ADCON1 |= 0XF;  // outros MCUs da série PIC18F (ex. PIC18F4550 e derivados)
    // possuem ADCON1, e a configuração seria dessa forma, que já configura
    // todos como digital
#endif

// Programa

    // Configuração da entrada = Tecla
    TRISB.RB0 = 1;  // configura pino RB0 como entrada no PORTB
    PORTB.RB0=1; //seria opcional pois internamente, ao colocar TRISX.RX0 =1,...
    /* MCU já coloca nível 1 nesta porta X (O MCU possui resistores Pull-up e 
    pull-down externos -ver circuitos do kit EasyPIC).Porém, existe uma excessão
    que é o PORTB: ao colocar TRISB.RB0 = 1; os resistores PUll-Up desligam-se
    automaticamente */
    
    // Saída (LED): configuração do estado inicial
    TRISD.RD0=0; // output - configura o pino como saída (=0) (consome corrente)
    LATD.RD0 = 0; // LED OFF

// condições e loop para piscar o LED:
while(1) // True
{
    if(PORTB.RB0 ==0)   // Tecla ativada em nível lógico 0 (SE o pino estiver ..
    // aterrado..)
    {
       LATD.RD0 =~LATD.RD0; // Inverte o nível lógico do LED em LATD
       // "~ "  inversão bit a bit  - SE incialmente RD0 = 0, receberá 1 quando
       // a teclada for pressionada; SE 1, receberá o valor 0
       Delay_ms(300);     // retarda a CPU de forma que ao pressionar a tecla..
       // a ação de fato aconteça (as intruções são executadas em nanosegundos)

     }  //fim do bloco IF, o qual em caso de falso (a tecla não for pressionada)
     //...será pulado.
     
     /*  Abaixo um exemplo de loop simples, somente para piscar LED independente
     da tecla:
        LATD.RD0= 1;   // acende o LED
        Delay_ms(300);  // delay de 300 ms  aceso
        LATD.RD0=0;    // apaga o LED
        Delay_ms(300);  // delay de 300 ms apagado
        */
} //while

} // main