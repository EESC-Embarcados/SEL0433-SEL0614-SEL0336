/*
 * SEL0433/SEL0614/SEL0336 - Aplic. de Microprocessadores
 * Leitura de Tens�o com Conversor AD - Canal AN0
 *
 * Descri��o:
 * Este programa l� a tens�o do pino RA0 (canal AN0). No contexto da placa
 * PICGenios, este � o pino conectado ao potenci�metro (Trimpot).
 * O valor lido (0-1023) � exibido no display LCD.
 *
 * Device:  PIC18F4550 - Clock = 8 MHz
 *
 * ==============================================================================
 * COMO TESTAR NO PICSIMLAB:
 * ==============================================================================
 * 1. Compile e carregue o arquivo .hex na placa PICGenios.
 * 2. Para simular a entrada anal�gica, localize o POTENCI�METRO (Trimpot) na
 * placa virtual, geralmente marcado como P1-AN0.
 * 3. Clique com o mouse sobre o cursor do potenci�metro e arraste-o para
 * a esquerda ou direita para alterar a tens�o de entrada.
 * 4. Ao fazer isso, voc� ver� o valor num�rico no display LCD mudar em
 * tempo real, variando de 0 a 1023.
 * ==============================================================================
*/

// --- Bits de Configura��o para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

// Config. de pinos do LCD para a placa PICGenios
sbit LCD_RS at LATE2_bit;
sbit LCD_EN at LATE1_bit;
sbit LCD_D4 at LATD4_bit;
sbit LCD_D5 at LATD5_bit;
sbit LCD_D6 at LATD6_bit;
sbit LCD_D7 at LATD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

// --- In�cio do Programa ---
void main() {
    unsigned int Leitura_ADC;
    char Texto[7];

    // --- Configura��o dos Pinos ---
    // Esta configura��o � crucial e deve vir PRIMEIRO
    // ADCON1 = 0b00001110 (0x0E): Configura Vref e DEIXA APENAS AN0 COMO ANAL�GICO.
    ADCON1 = 0x0E;

    // Configura o pino RA0 (AN0) como entrada.
    TRISA0_bit = 1;

    // --- Configura��o do M�dulo ADC ---
    // Configura formato e tempos do ADC
    ADCON2 = 0b10101010;

    // Seleciona canal AN0 e liga o m�dulo ADC
    ADCON0 = 0b00000001;

    Delay_ms(2); // Delay para estabiliza��o

    // --- Configura��o do LCD ---
    // Bibliotecas Lcd e Conversions devem estar habilitadas no Library Manager
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1, 1, "Leitura AN0:");

    // --- Loop Principal ---
    while(1) {
        // Inicia a convers�o A/D
        ADCON0.GO_DONE = 1;

        // Aguarda em loop at� a convers�o terminar.
        while(ADCON0.GO_DONE == 1);

        // Combina os registradores em uma �nica vari�vel.
        Leitura_ADC = (ADRESH << 8) | ADRESL;

        // Converte o valor num�rico em texto.
        WordToStr(Leitura_ADC, Texto);

        // Exibe o texto no LCD.
        Lcd_Out(2, 5, "      "); // Limpa a �rea do n�mero anterior
        Lcd_Out(2, 5, Texto);

        Delay_ms(100);
    }
}