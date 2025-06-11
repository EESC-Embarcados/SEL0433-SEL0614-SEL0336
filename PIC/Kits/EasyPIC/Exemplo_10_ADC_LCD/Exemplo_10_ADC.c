   // SEL0433/SEL0614/SEL0336 - Aplic. de Microprocessadores
    // Conceitos sobre conversor AD - config. manual dos registradores
    
 // Uso do conversor ADC para realizar uma leitura analógica (sinal de tensão)
  // usando o TRIMPOT "ADC Input" do kit EasyPIC v7

  // será o usado o canal analógico AN4/RA5 - para ler o sinal de tensão analógico
  //o qual irá varir conforme o ajuste do TRIMPOT (simulando uma variação analógica
  // um sensor, por exemplo)

  // Device:  PIC18F4550 - Clock  = 8 MHz
  // Tensão de ref. interna do ADC 0 - 5V
  // Necessário add bibliotecas LCD e conversão de dados em "Libray Manager"

  // Configurações necessárias: Jumper no "trimpot ADC input" AN4 (PORTA5) - 1° trimpot
  // habilitar o display LCD em SW4 - se necessário ajsutar o contraste no trimpot
  // correspondente


// Config. de pinos do LCD  (PORTB) conforme exemplo da biblioteca do compilador

// pinos utilizados para comunicação com o display LCD
sbit LCD_RS at LATB4_bit; // pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit; // pino 5 do PORTB " " ao EN do display
sbit LCD_D4 at LATB0_bit; // pino 0 do PORTB ao D4
sbit LCD_D5 at LATB1_bit;  // " "
sbit LCD_D6 at LATB2_bit;  // " "
sbit LCD_D7 at LATB3_bit;  // " "
// direção do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;  // direção do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;  // " "
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;


 // inicio do programa
void main() {
  unsigned int Leitura_ADC;   // variav. de leitura ADC
  unsigned char Texto[10];//Display LCD - tipo char - int 8 bits (lembrando: Arranjo= tipo nome [n° de elementos])


TRISA.RA5=1;  // pino AN4 como entrada (canal analógico escolhido neste ex.)
//PORTA.RA0 = 1;  // opcional   (pull-up)

// 3 reg. responsáveis pela config. do módulo ADC: ADCON0, ADCON1 e ADCON2
// ver config. dos bits no datasheet  https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/39632e.pdf


//ADCON1 = 0x0F;


ADCON0 = 0B00010001;  // AN4 -> AD ligado, leitura deslig., canal AN0
ADCON1 = 0B00000000; // tensões de ref. internas = VDD e Vss

ADCON2 = 0B10101010; // Justificativa para direita, FOSC/32 (tempo entre 2 e 25 us)
//... e 12 TAD (tempo de conversão de cada bit + 2 TAD)

// Config. do módulo LCD
  Lcd_Init();                        //Inicializa display no modo 4 bits
  Lcd_Cmd(_LCD_CLEAR);               //Apaga display
  Lcd_Cmd(_LCD_CURSOR_OFF);          //Desliga cursor
  Lcd_Out(1,1,"ADC: ");              // escrita: Linha x Coluna

 while(1)
 {
   ADCON0.GO_DONE = 1;           //liga a leitura e inicia a conversão do ADC
     while(ADCON0.GO_DONE == 1);   //Aguardar o término da conversão - após a
     //conversão terminar esse bit será  = 0 e essa condição não é mais
     // verdadeira. Sendo assim, o programa vai para a próxima linha


     //Leitura_ADC = ADRESH + ADRESL;//0 a 1023; em que: '|' = OR bit a bit
    Leitura_ADC = ((ADRESH << 8)| ADRESL);
    /*
     ex.: se ADRESH = 0B00000011;
     ( ADRESH << 8) =>  00000011 00000000   // rotação de 8 bits a esquerda para
     que o valor de ADRESH fique na parte alta
     Lembrando que Leitura ADC é uma variável de 16 bits que receberá a combinação
     de ADRESH (8bits) com ADRESL(8bits) por meio do OR bitwise "|"   entre eles
     
     Lembrando também que somente 10 bits serão usados para leitura do ADC, já que
     sua resolução é 10 bits. A operação acima, portanto, usará 2 bits do ADRESH
     e 8 bits do ADRESL (justificando o valor da coversão a direita)
     
     Portanto, supondo ADRESH = 0B00000011; e ADRESL =  0B10011101 ; é necessário
     a operação acima para formar a palavra de 10 bits "11 + 10011101" = 1110011101

    Dessa forma, o OR bitwise de ADRESH e ADRESL sera:

                      00000011 00000000
                    | 00000000 10011101
    leitura_ADC =  <- 00000011 10011101 (resultado da Op. OR) - 10 bits justificado a direita

    */

      
    // mostrar os valores no display LCD = necessaio habilitar bibliotecas de
    //LCD (as linhas de código foram apresentadas anteriomente)
    // e de conversão dos dados (Leitura_ADC) para texto, apresentadas abaixo
    WordToStr(Leitura_ADC, Texto);  // conversão
    LCD_Out(1,5, Texto); // coloca o texto em determinada linha e posição 1, 5
    Delay_ms(20);       // delay para dar tempo para o LCD atualizar

   }

}