/*
 * SEL0433/SEL0336/SEL0614 - Aplic. de Microprocessadores
 * ===============================================================================
 * Exemplo de Interrupção com Timer0 - Adaptado para PICGenios
 *
 * Descrição:
 * Este programa configura o Timer0 para gerar uma interrupção a cada 200ms.
 * A rotina de tratamento de interrupção (ISR) é responsável por piscar (toggle)
 * o LED D2, conectado ao pino RD2.
 * O programa principal (main) não faz nada, demonstrando que a ação ocorre
 * de forma assíncrona, "em segundo plano".
 *
 * Plataforma: PIC18F4550 na placa PICGenios (PICSimLab)
 * MCU: PIC18F4550 - Cristal de 8 MHz
*/

// --- Bits de Configuração para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

// --- Protótipos das Funções de Configuração ---
void ConfigMCU();
void ConfigTIMER();
void ConfigInterrupt();

// --- Rotina de Tratamento de Interrupção (ISR) ---
// Esta função é chamada AUTOMATICAMENTE pelo hardware quando a interrupção ocorre.
// iv 0x0008: Endereço do vetor de interrupção de alta prioridade.
// ics ICS_AUTO: O compilador salva e restaura o contexto automaticamente.
void Interrupt() iv 0x0008 ics ICS_AUTO {

    // 1. Verifica se a interrupção foi causada pelo Timer0
    if (TMR0IF_bit == 1) {
        // 2. Ação a ser executada (tratamento do evento)
        LATD2_bit = ~LATD2_bit; // Inverte o estado do LED D2

        // 3. Recarrega o Timer0 para a próxima contagem de 200ms
        TMR0H = 0xCF;
        TMR0L = 0x2C;

        // 4. Limpa a flag da interrupção (passo OBRIGATÓRIO)
        TMR0IF_bit = 0; // Prepara para a próxima interrupção
    }
}

// --- Função para configurar os pinos do MCU ---
void ConfigMCU() {
    ADCON1 = 0x0F; // Pinos como digitais
    TRISD = 0;     // PORTD (LEDs) como saída
    LATD = 0;      // Todos os LEDs começam desligados
}

// --- Função para configurar o Timer0 para estourar em 200ms ---
void ConfigTIMER() {
    // Cálculo: (8MHz/4) = 2MHz -> T_ciclo = 0.5us
    // Prescaler 1:32. N_pulsos = 200.000us / (0.5us * 32) = 12500
    // Valor a carregar = 65536 - 12500 = 53036 (ou 0xCF2C em hexadecimal)
    T0CON = 0b00000100; // Timer0 OFF, 16-bit, clock interno, prescaler 1:32
    TMR0H = 0xCF;       // Carrega a parte alta do valor
    TMR0L = 0x2C;       // Carrega a parte baixa
    TMR0ON_bit = 1;     // Liga o Timer0 após a configuração
}

// --- Função para configurar o sistema de interrupções ---
void ConfigInterrupt() {
    RCON.IPEN = 0;      // Desabilita os níveis de prioridade (modo compatibilidade)
    GIE_bit = 1;        // Habilita a "chave geral" das interrupções
    TMR0IE_bit = 1;     // Habilita a interrupção específica do Timer0
    TMR0IF_bit = 0;     // Garante que a flag comece zerada
}

// --- Função Principal ---
void main() {
    ConfigMCU();
    ConfigTIMER();
    ConfigInterrupt();

    // O loop principal fica vazio.
    // O microcontrolador executará este laço infinito, mas será
    // "interrompido" a cada 200ms para executar a rotina de interrupção.
    while(1) {
    }
}