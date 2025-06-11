/*
 * SEL0433/SEL0336 Aplic. de Microprocessadores
 * ===============================================================================
 * Exemplo 2 Adaptado: Toggle de LED com Bot�o e Tratamento de Debounce
 *
 * Plataforma: PIC18F4550 na placa PICGenios (simulador PICSimLab)
 *
 * Descri��o:
 * Este c�digo resolve o problema do "Exemplo 1". A cada clique no bot�o B0 (RB0),
 * o estado do LED D0 (RD0) � invertido apenas uma vez. A l�gica usa uma vari�vel
 * "flag" para detectar a borda de subida e descida do pulso do bot�o, ignorando
 * a trepida��o mec�nica (bouncing) e o estado de bot�o pressionado.
 *
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configura��o para PIC18F4550 ---
// Essencial para o funcionamento correto no simulador.
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

void main() {
    // Vari�vel auxiliar (flag) para permitir o acionamento do LED apenas uma
    // vez por clique, tratando o efeito de bouncing.
    unsigned char FlagAux = 0;

    // --- Configura��o dos Pinos para PIC18F4550 ---
    // Configura os pinos das portas A, B, etc. como digitais.
    // O #pragma PBADEN=OFF j� cuida do PORTB, mas ADCON1 � uma boa pr�tica geral.
    ADCON1 = 0x0F;

    // --- Configura��o da Entrada (Bot�o B0) ---
    TRISB0_bit = 1;      // Configura o pino RB0 como entrada.

    // --- Configura��o da Sa�da (LED D0) ---
    TRISD0_bit = 0;      // Configura o pino RD0 como sa�da.
    LATD0_bit = 0;       // Garante que o LED comece desligado.

    // --- Loop Principal ---
    while(1) { // Loop infinito
        // 1. Condi��o de ACIONAMENTO:
        //    Verifica se o bot�o FOI PRESSIONADO (n�vel 0) E
        //    se a a��o ainda N�O FOI TRATADA (FlagAux == 0).
        if(PORTB.RB0 == 0 && FlagAux == 0) {
            LATD0_bit = ~LATD0_bit; // Inverte o estado do LED (toggle)
            FlagAux = 1;            // "Levanta" a flag, indicando que a a��o j� ocorreu.
                                    // Isso impede que o LED fique piscando enquanto o
                                    // bot�o estiver pressionado.
            Delay_ms(40);           // Atraso para filtrar a trepida��o do bot�o.
        }

        // 2. Condi��o de REARME:
        //    Verifica se o bot�o FOI SOLTO (n�vel 1) E
        //    se o sistema est� esperando a libera��o (FlagAux == 1).
        if(PORTB.RB0 == 1 && FlagAux == 1) {
            FlagAux = 0;            // "Abaixa" a flag, deixando o sistema pronto
                                    // para detectar o pr�ximo clique.
            Delay_ms(40);           // Atraso opcional para filtrar o bouncing da soltura.
        }
    } // Fim do while
} // Fim do main