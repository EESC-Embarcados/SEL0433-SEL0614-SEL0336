/*
 * Incrementar Display 7 seg. com botão
 * Plataforma: PIC18F4550 na placa PICGenios (PICSimLab)
 *
 * Descrição:
 * Este código incrementa um contador (0, 1, 2, desliga) a cada clique no
 * botão B0 (RB0). O número é exibido no display de 7 segmentos da
 * extrema direita (disp4).
 *
 * A lógica original de debounce com a variável FlagAux foi mantida.
 *
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configuração para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

// Variável global para o contador. Inicia em -1 para o primeiro clique ir para 0.
signed char ucContador = -1;

// Função que define o padrão do 7 segmentos em PORTD conforme o contador
void Incremento(unsigned char Contador) {
     switch (Contador) {
        // Padrões para um display de anodo comum (como o da PICGenios)
        case 0: { LATD = 0b00111111; break; }  // '0'
        case 1: { LATD = 0b00000110; break; }  // '1'
        case 2: { LATD = 0b01011011; break; }  // '2'
        default:{ LATD = 0; ucContador = -1; break; } // Desliga display e reinicia o contador
     }
}

void main() {
    // Variável de controle para debounce (evita múltiplos incrementos)
    unsigned char FlagAux = 0;

    // --- Configuração dos pinos para PIC18F4550 ---
    ADCON1 = 0x0F; // Configura pinos analógicos (AN0-AN12) como I/O Digital
    // CMCON  = 0x07; // Desabilita os comparadores

    // --- Configuração da Entrada (Botão) ---
    TRISB0_bit = 1; // Configura RB0 como entrada para ler o botão B0

    // --- Configuração das Saídas (Displays) ---
    // 1. Configura PORTD como saída para os segmentos do display (A-G, DP)
    TRISD = 0;
    LATD = 0;   // Inicia com todos os segmentos desligados

    // 2. Habilita APENAS UM display (o disp4, da direita)
    // Os displays da PICGenios são anodo comum, habilitados com nível 0.
    TRISA2_bit = 0; // RA2 (disp1) como saída
    TRISA3_bit = 0; // RA3 (disp2) como saída
    TRISA4_bit = 0; // RA4 (disp3) como saída
    TRISA5_bit = 0; // RA5 (disp4) como saída

    LATA2_bit = 0; // Desliga disp1
    LATA3_bit = 0; // Desliga disp2
    LATA4_bit = 0; // Desliga disp3
    LATA5_bit = 1; // LIGA o disp4 (o da direita)

    // --- Loop Principal ---
    while(1) {
        // Bloco executado quando o botão é pressionado (e não estava antes)
        if (PORTB.RB0 == 0 && FlagAux == 0) {
            // Lógica de debounce: só entra aqui na primeira detecção
            // do botão pressionado (nível 0).

            Incremento(++ucContador); // Pré-incrementa o contador e atualiza o display

            FlagAux = 1;      // "Levanta" a flag para indicar que o botão foi tratado
            Delay_ms(40);     // Atraso para ignorar a trepidação mecânica (bouncing)
        }

        // Bloco executado quando o botão é solto
        if (PORTB.RB0 == 1 && FlagAux == 1) {
            // A tecla foi liberada (nível 1), então podemos preparar para o próximo clique.

            FlagAux = 0;      // "Abaixa" a flag, permitindo que um novo clique seja detectado
            Delay_ms(40);     // Atraso para o bouncing da liberação da tecla
        }
    } // Fim do while
} // Fim do main