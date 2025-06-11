/*
 * Exemplo 1 Adaptado: Aciona LED com Bot�o
 * Plataforma: PIC18F4550 na placa PICGenios (PICSimLab)
 *
 * Descri��o:
 * Este c�digo inverte o estado do LED D0 (conectado em RD0) enquanto o
 * bot�o B0 (conectado em RB0) estiver pressionado.
 *
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configura��o para PIC18F4550 (Essencial para o simulador) ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

void main() {
    // --- Configura��o dos Pinos ---
    // Configura os pinos de PORTA e PORTB como digitais.
    // O #pragma PBADEN=OFF j� ajuda com PORTB, mas ADCON1 � uma boa pr�tica.
    ADCON1 = 0x0F;

    // --- Configura��o da Entrada (Bot�o B0) ---
    TRISB0_bit = 1;      // Configura o pino RB0 como entrada.

    // --- Configura��o da Sa�da (LED D0) ---
    TRISD0_bit = 0;      // Configura o pino RD0 como sa�da.
    LATD0_bit = 0;       // Garante que o LED comece desligado.


    // --- Loop Principal ---
    while(1) {
        // Se o bot�o B0 estiver pressionado (n�vel l�gico 0)...
        if(PORTB.RB0 == 0) {
            // Inverte o estado atual do LED D0
            LATD0_bit = ~LATD0_bit;

            // Delay para visualizar a mudan�a e criar o efeito de piscar
            Delay_ms(300);
        }
    }
}