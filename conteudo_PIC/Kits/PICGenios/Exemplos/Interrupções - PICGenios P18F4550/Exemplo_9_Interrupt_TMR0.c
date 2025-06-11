/*
 * SEL0433/SEL0336/SEL0614 - Aplic. de Microprocessadores
 * ===============================================================================
 * Exemplo de Interrup��o com Timer0 - Adaptado para PICGenios
 *
 * Descri��o:
 * Este programa configura o Timer0 para gerar uma interrup��o a cada 200ms.
 * A rotina de tratamento de interrup��o (ISR) � respons�vel por piscar (toggle)
 * o LED D2, conectado ao pino RD2.
 * O programa principal (main) n�o faz nada, demonstrando que a a��o ocorre
 * de forma ass�ncrona, "em segundo plano".
 *
 * Plataforma: PIC18F4550 na placa PICGenios (PICSimLab)
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configura��o para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

// --- Prot�tipos das Fun��es de Configura��o ---
void ConfigMCU();
void ConfigTIMER();
void ConfigInterrupt();

// --- Rotina de Tratamento de Interrup��o (ISR) ---
// Esta fun��o � chamada AUTOMATICAMENTE pelo hardware quando a interrup��o ocorre.
// iv 0x0008: Endere�o do vetor de interrup��o de alta prioridade.
// ics ICS_AUTO: O compilador salva e restaura o contexto automaticamente.
void Interrupt() iv 0x0008 ics ICS_AUTO {

    // 1. Verifica se a interrup��o foi causada pelo Timer0
    if (TMR0IF_bit == 1) {
        // 2. A��o a ser executada (tratamento do evento)
        LATD2_bit = ~LATD2_bit; // Inverte o estado do LED D2

        // 3. Recarrega o Timer0 para a pr�xima contagem de 200ms
        TMR0H = 0xCF;
        TMR0L = 0x2C;

        // 4. Limpa a flag da interrup��o (passo OBRIGAT�RIO)
        TMR0IF_bit = 0; // Prepara para a pr�xima interrup��o
    }
}

// --- Fun��o para configurar os pinos do MCU ---
void ConfigMCU() {
    ADCON1 = 0x0F; // Pinos como digitais
    TRISD = 0;     // PORTD (LEDs) como sa�da
    LATD = 0;      // Todos os LEDs come�am desligados
}

// --- Fun��o para configurar o Timer0 para estourar em 200ms ---
void ConfigTIMER() {
    // C�lculo: (8MHz/4) = 2MHz -> T_ciclo = 0.5us
    // Prescaler 1:32. N_pulsos = 200.000us / (0.5us * 32) = 12500
    // Valor a carregar = 65536 - 12500 = 53036 (ou 0xCF2C em hexadecimal)
    T0CON = 0b00000100; // Timer0 OFF, 16-bit, clock interno, prescaler 1:32
    TMR0H = 0xCF;       // Carrega a parte alta do valor
    TMR0L = 0x2C;       // Carrega a parte baixa
    TMR0ON_bit = 1;     // Liga o Timer0 ap�s a configura��o
}

// --- Fun��o para configurar o sistema de interrup��es ---
void ConfigInterrupt() {
    RCON.IPEN = 0;      // Desabilita os n�veis de prioridade (modo compatibilidade)
    GIE_bit = 1;        // Habilita a "chave geral" das interrup��es
    TMR0IE_bit = 1;     // Habilita a interrup��o espec�fica do Timer0
    TMR0IF_bit = 0;     // Garante que a flag comece zerada
}

// --- Fun��o Principal ---
void main() {
    ConfigMCU();
    ConfigTIMER();
    ConfigInterrupt();

    // O loop principal fica vazio.
    // O microcontrolador executar� este la�o infinito, mas ser�
    // "interrompido" a cada 200ms para executar a rotina de interrup��o.
    while(1) {
    }
}