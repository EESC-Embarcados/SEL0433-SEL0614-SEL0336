/*
 * Exemplo de uso do Timer1 no modo Contador com Prescaler para Debounce
 * Adaptado para PIC18F4550 na placa PICGenios (PICSimLab)
 *
 * Descri��o:
 * Este programa configura o Timer1 para contar 10 eventos externos (pulsos)
�* que chegam no pino RC0 (T1CKI).
 *
�* Ap�s o 10� evento, o timer estoura (overflow), e o programa acende
�* o LED D1 (conectado em RD1) por 1 segundo como sinaliza��o.
�*
�* Este � o princ�pio usado para medir o RPM da ventoinha no projeto final:
 * O pino RC0 na placa � reservado para o sensor infravermelho da ventoinha.
 *
 * Corrigido para tratar o "bouncing" do bot�o. O Prescaler do Timer1
 * foi configurado para 1:8, agindo como um filtro de hardware para os
 * m�ltiplos pulsos gerados por um �nico clique. Ainda assim, menos que 10 cliques
 * s�o suficientes para acender o led, mas j� � suficiente para entender a interrup��o.
 *
 * ==============================================================================
 * COMO TESTAR NO PICSIMLAB:
 * ==============================================================================
 * Como a placa PICGenios n�o possui um bot�o f�sico no pino RC0 (entrada do
 * Timer1), � necess�rio adicionar um bot�o virtual para gerar os pulsos de teste.
 *
 * Siga os passos no simulador:
 * Menu -> Modules -> Spare Parts -> Push button -> Properties (bot�o direito) -> Size: 1 -> Out: 15 (RC0)
 *
 * Lembre-se de habilitar a op��o "Pull-up" nas propriedades do bot�o adicionado.
 * ==============================================================================
*/

// --- Bits de Configura��o para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

void main() {

    // --- Configura��o dos Pinos ---
    ADCON1 = 0x0F;
    TRISC0_bit = 1; // RC0 como entrada para o Timer1
    TRISD = 0;      // PORTD (LEDs) como sa�da
    LATD = 0;       // Todos os LEDs come�am desligados

    // --- Configura��o do Timer1 com PRESCALER 1:8 para tratar o bounce ---
    // bit 5-4 T1CKPS = 11: Prescaler 1:8
    T1CON = 0b10110011;

    // Pr�-carrega o timer para contar 10 eventos
    TMR1H = 0xFF;
    TMR1L = 0xF6;
    TMR1IF_bit = 0;

    // --- Loop Principal ---
    while(1) {
        // Verifica se o Timer1 contou 10 eventos (j� filtrados pelo prescaler)
        if (TMR1IF_bit == 1) {
            LATD1_bit = 1;      // Acende o LED D1

            // Recarrega o timer e zera a flag para a pr�xima contagem
            TMR1H = 0xFF;
            TMR1L = 0xF6;
            TMR1IF_bit = 0;

            Delay_ms(1000);     // Mant�m o LED aceso por 1 segundo
        }
        else {
            // Mant�m o LED D1 apagado fora do per�odo de sinaliza��o
            LATD1_bit = 0;
        }
    }
}