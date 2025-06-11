/*
 * Exemplo 1 Adaptado: Aciona LED com Botão
 * Plataforma: PIC18F4550 na placa PICGenios (PICSimLab)
 *
 * Descrição:
 * Este código inverte o estado do LED D0 (conectado em RD0) enquanto o
 * botão B0 (conectado em RB0) estiver pressionado.
 *
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configuração para PIC18F4550 (Essencial para o simulador) ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

void main() {
    // --- Configuração dos Pinos ---
    // Configura os pinos de PORTA e PORTB como digitais.
    // O #pragma PBADEN=OFF já ajuda com PORTB, mas ADCON1 é uma boa prática.
    ADCON1 = 0x0F;

    // --- Configuração da Entrada (Botão B0) ---
    TRISB0_bit = 1;      // Configura o pino RB0 como entrada.

    // --- Configuração da Saída (LED D0) ---
    TRISD0_bit = 0;      // Configura o pino RD0 como saída.
    LATD0_bit = 0;       // Garante que o LED comece desligado.


    // --- Loop Principal ---
    while(1) {
        // Se o botão B0 estiver pressionado (nível lógico 0)...
        if(PORTB.RB0 == 0) {
            // Inverte o estado atual do LED D0
            LATD0_bit = ~LATD0_bit;

            // Delay para visualizar a mudança e criar o efeito de piscar
            Delay_ms(300);
        }
    }
}