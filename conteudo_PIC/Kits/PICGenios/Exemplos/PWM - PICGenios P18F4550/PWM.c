/*
 * Project name:
     Lcd_PWM_PICGenios
 * Description:
     Vers?o FINAL e CORRIGIDA para a placa PICGenios no simulador PICSimLab.
     O mapeamento dos pinos do LCD foi corrigido de acordo com o hardware da placa.
 * Test configuration:
     MCU:             PIC18F4550
     Dev.Board:       PICGenios (no simulador PICSimLab)
     Oscillator:      HS 8.0000 MHz
     SW:              mikroC PRO for PIC
*/

// --- Bits de Configura??o para PIC18F4550 ---
#pragma config FOSC = HS, WDT = OFF, PWRT = ON, BOR = ON, LVP = OFF, PBADEN = OFF, MCLRE = ON

// --- Mapeamento CORRETO dos pinos do LCD para a placa PICGenios ---
sbit LCD_RS at LATE2_bit; // Pino RS conectado em RE2
sbit LCD_EN at LATE1_bit; // Pino EN conectado em RE1
sbit LCD_D4 at LATD4_bit; // Pino D4 conectado em RD4
sbit LCD_D5 at LATD5_bit; // Pino D5 conectado em RD5
sbit LCD_D6 at LATD6_bit; // Pino D6 conectado em RD6
sbit LCD_D7 at LATD7_bit; // Pino D7 conectado em RD7

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// --- Fim do mapeamento ---

char txt1[] = "PICSimLab";
char txt2[] = "PICGenios";
char txt3[] = "LCD Funcionando!";
char txt4[] = "Pinos Corretos";

char i;

void Move_Delay() {
  Delay_ms(400);
}

// --- Fun??es para o Controle PWM ---

// Esta fun??o inicializa o M?dulo CCP1 para operar em modo PWM
// usando o Timer2. A frequ?ncia do PWM ser? de aproximadamente 4.88kHz
// com um cristal de 8MHz.
void PWM_Init() {
  TRISC2_bit = 0;      // Configura o pino RC2 (CCP1) como sa?da.

  // 1. Configurar o Per?odo do PWM (Frequ?ncia) com o Timer2
  PR2 = 255;           // Define o valor m?ximo do contador do Timer2 (per?odo).
                       // Isso nos dar? a resolu??o m?xima para o duty cycle.

  // 2. Configurar e ligar o Timer2
  T2CON = 0b00000101;  // Liga o Timer2 com um prescaler de 4 (TMR2ON=1, T2CKPS=1).
                       // Prescaler 1:4 ? um bom come?o.

  // 3. Configurar o M?dulo CCP1 para modo PWM
  CCP1CON = 0b00001100;  // Ativa o modo PWM para o CCP1.
}

// Esta fun??o ajusta o duty cycle do PWM.
// O valor de 'duty' pode ir de 0 (0%) a 1023 (100%).
void PWM_Set_Duty(unsigned int duty) {
  // Coloca os 8 bits mais significativos do duty cycle em CCPR1L
  CCPR1L = duty >> 2;

  // Coloca os 2 bits menos significativos nos bits 5 e 4 do CCP1CON
  CCP1CON = (CCP1CON & 0b11001111) | ((duty & 0b11) << 4);
}
// --- Mantenha suas fun??es PWM_Init() e PWM_Set_Duty() como estavam ---

void main() {
    unsigned int duty_value = 0;
    char *duty_text;

    // Vari?vel para controlar o n?vel de velocidade (0 a 4)
    int speed_level = 0;

    // --- Configura??es Iniciais ---
    // A configura??o PBADEN=OFF nos #pragma ? essencial para PORTB funcionar digitalmente
    ADCON1 = 0x0F;
    CMCON = 0x07;
    TRISB = 0xFF; // Configura PORTB como entrada para ler os bot?es

    // Inicialize seu LCD aqui
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    PWM_Init();

    while(1) {
        // --- L?gica de Controle com Bot?es ---

        // Bot?o de AUMENTAR velocidade (RB1)
        if (RB1_bit == 0) {
            Delay_ms(50); // Debounce para o bot?o
            if (RB1_bit == 0) { // Confirma o clique
                speed_level++;
                if (speed_level > 4) {
                    speed_level = 0; // Volta para o in?cio
                }
                while(RB1_bit == 0); // Espera o bot?o ser solto
            }
        }

        // Bot?o de DIMINUIR velocidade (RB2)
        if (RB2_bit == 0) {
            Delay_ms(50); // Debounce
            if (RB2_bit == 0) { // Confirma o clique
                speed_level--;
                if (speed_level < 0) {
                    speed_level = 4; // Volta para o m?ximo
                }
                while(RB2_bit == 0); // Espera o bot?o ser solto
            }
        }

        // --- Converte o n?vel de velocidade para valor de PWM e texto ---
        switch (speed_level) {
            case 0:
                duty_value = 0;
                duty_text = "0%  ";
                break;
            case 1:
                duty_value = 256; // ~25%
                duty_text = "25% ";
                break;
            case 2:
                duty_value = 512; // ~50%
                duty_text = "50% ";
                break;
            case 3:
                duty_value = 767; // ~75%
                duty_text = "75% ";
                break;
            case 4:
                duty_value = 1023; // 100%
                duty_text = "100%";
                break;
        }

        PWM_Set_Duty(duty_value); // Aplica o novo duty cycle

        // --- Atualiza o LCD ---
        Lcd_Out(1, 1, "Duty Cycle:");
        Lcd_Out(1, 13, duty_text);
        Lcd_Out(2, 1, "RPM: ");
        Lcd_Out(2, 6, "0"); // RPM ainda n?o implementado

        // N?o precisa de delay aqui, pois o loop j? ? controlado pelos bot?es
    }
}