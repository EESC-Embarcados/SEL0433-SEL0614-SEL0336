/*
 * SEL0433/SEL0336 Aplic. de Microprocessadores
 * ===============================================================================
 * Exemplo 2 Adaptado: Toggle de LED com Botão e Tratamento de Debounce
 *
 * Plataforma: PIC18F4550 na placa PICGenios (simulador PICSimLab)
 *
 * Descrição:
 * Este código resolve o problema do "Exemplo 1". A cada clique no botão B0 (RB0),
 * o estado do LED D0 (RD0) é invertido apenas uma vez. A lógica usa uma variável
 * "flag" para detectar a borda de subida e descida do pulso do botão, ignorando
 * a trepidação mecânica (bouncing) e o estado de botão pressionado.
 *
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configuração para PIC18F4550 ---
// Essencial para o funcionamento correto no simulador.
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

void main() {
    // Variável auxiliar (flag) para permitir o acionamento do LED apenas uma
    // vez por clique, tratando o efeito de bouncing.
    unsigned char FlagAux = 0;

    // --- Configuração dos Pinos para PIC18F4550 ---
    // Configura os pinos das portas A, B, etc. como digitais.
    // O #pragma PBADEN=OFF já cuida do PORTB, mas ADCON1 é uma boa prática geral.
    ADCON1 = 0x0F;

    // --- Configuração da Entrada (Botão B0) ---
    TRISB0_bit = 1;      // Configura o pino RB0 como entrada.

    // --- Configuração da Saída (LED D0) ---
    TRISD0_bit = 0;      // Configura o pino RD0 como saída.
    LATD0_bit = 0;       // Garante que o LED comece desligado.

    // --- Loop Principal ---
    while(1) { // Loop infinito
        // 1. Condição de ACIONAMENTO:
        //    Verifica se o botão FOI PRESSIONADO (nível 0) E
        //    se a ação ainda NÃO FOI TRATADA (FlagAux == 0).
        if(PORTB.RB0 == 0 && FlagAux == 0) {
            LATD0_bit = ~LATD0_bit; // Inverte o estado do LED (toggle)
            FlagAux = 1;            // "Levanta" a flag, indicando que a ação já ocorreu.
                                    // Isso impede que o LED fique piscando enquanto o
                                    // botão estiver pressionado.
            Delay_ms(40);           // Atraso para filtrar a trepidação do botão.
        }

        // 2. Condição de REARME:
        //    Verifica se o botão FOI SOLTO (nível 1) E
        //    se o sistema está esperando a liberação (FlagAux == 1).
        if(PORTB.RB0 == 1 && FlagAux == 1) {
            FlagAux = 0;            // "Abaixa" a flag, deixando o sistema pronto
                                    // para detectar o próximo clique.
            Delay_ms(40);           // Atraso opcional para filtrar o bouncing da soltura.
        }
    } // Fim do while
} // Fim do main