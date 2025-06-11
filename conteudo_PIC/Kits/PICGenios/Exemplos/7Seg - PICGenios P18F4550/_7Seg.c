/*
 * Incrementar Display 7 seg. com bot�o
 * Plataforma: PIC18F4550 na placa PICGenios (PICSimLab)
 *
 * Descri��o:
 * Este c�digo incrementa um contador (0, 1, 2, desliga) a cada clique no
 * bot�o B0 (RB0). O n�mero � exibido no display de 7 segmentos da
 * extrema direita (disp4).
 *
 * A l�gica original de debounce com a vari�vel FlagAux foi mantida.
 *
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configura��o para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

// Vari�vel global para o contador. Inicia em -1 para o primeiro clique ir para 0.
signed char ucContador = -1;

// Fun��o que define o padr�o do 7 segmentos em PORTD conforme o contador
void Incremento(unsigned char Contador) {
     switch (Contador) {
        // Padr�es para um display de anodo comum (como o da PICGenios)
        case 0: { LATD = 0b00111111; break; }  // '0'
        case 1: { LATD = 0b00000110; break; }  // '1'
        case 2: { LATD = 0b01011011; break; }  // '2'
        default:{ LATD = 0; ucContador = -1; break; } // Desliga display e reinicia o contador
     }
}

void main() {
    // Vari�vel de controle para debounce (evita m�ltiplos incrementos)
    unsigned char FlagAux = 0;

    // --- Configura��o dos pinos para PIC18F4550 ---
    ADCON1 = 0x0F; // Configura pinos anal�gicos (AN0-AN12) como I/O Digital
    // CMCON  = 0x07; // Desabilita os comparadores

    // --- Configura��o da Entrada (Bot�o) ---
    TRISB0_bit = 1; // Configura RB0 como entrada para ler o bot�o B0

    // --- Configura��o das Sa�das (Displays) ---
    // 1. Configura PORTD como sa�da para os segmentos do display (A-G, DP)
    TRISD = 0;
    LATD = 0;   // Inicia com todos os segmentos desligados

    // 2. Habilita APENAS UM display (o disp4, da direita)
    // Os displays da PICGenios s�o anodo comum, habilitados com n�vel 0.
    TRISA2_bit = 0; // RA2 (disp1) como sa�da
    TRISA3_bit = 0; // RA3 (disp2) como sa�da
    TRISA4_bit = 0; // RA4 (disp3) como sa�da
    TRISA5_bit = 0; // RA5 (disp4) como sa�da

    LATA2_bit = 0; // Desliga disp1
    LATA3_bit = 0; // Desliga disp2
    LATA4_bit = 0; // Desliga disp3
    LATA5_bit = 1; // LIGA o disp4 (o da direita)

    // --- Loop Principal ---
    while(1) {
        // Bloco executado quando o bot�o � pressionado (e n�o estava antes)
        if (PORTB.RB0 == 0 && FlagAux == 0) {
            // L�gica de debounce: s� entra aqui na primeira detec��o
            // do bot�o pressionado (n�vel 0).

            Incremento(++ucContador); // Pr�-incrementa o contador e atualiza o display

            FlagAux = 1;      // "Levanta" a flag para indicar que o bot�o foi tratado
            Delay_ms(40);     // Atraso para ignorar a trepida��o mec�nica (bouncing)
        }

        // Bloco executado quando o bot�o � solto
        if (PORTB.RB0 == 1 && FlagAux == 1) {
            // A tecla foi liberada (n�vel 1), ent�o podemos preparar para o pr�ximo clique.

            FlagAux = 0;      // "Abaixa" a flag, permitindo que um novo clique seja detectado
            Delay_ms(40);     // Atraso para o bouncing da libera��o da tecla
        }
    } // Fim do while
} // Fim do main