/*
 * Project name:
     Lcd_Test_PICGenios_FINAL
 * Description:
     Versão FINAL e CORRIGIDA para a placa PICGenios no simulador PICSimLab.
     O mapeamento dos pinos do LCD foi corrigido de acordo com o hardware da placa.
 * Test configuration:
     MCU:             PIC18F4550
     Dev.Board:       PICGenios (no simulador PICSimLab)
     Oscillator:      HS 8.0000 MHz
     SW:              mikroC PRO for PIC
*/

// --- Bits de Configuração para PIC18F4550 ---
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
char txt3[] = "LCD Agora Vai!";
char txt4[] = "Pinos Corretos";

char i;

void Move_Delay() {
  Delay_ms(400);
}

void main(){
  // Esta linha é CRUCIAL, pois RE1 e RE2 também são pinos analógicos (AN6, AN7).
  // ADCON1 = 0x0F configura todos os pinos de AN0 a AN12 como digitais.
  ADCON1 = 0x0F;
  CMCON  = 0x07; // Desabilita comparadores

  Lcd_Init(); // Inicializa o LCD

  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);

  Lcd_Out(1, 1, txt3);
  Lcd_Out(2, 1, txt4);
  Delay_ms(2500);

  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1, 4, txt1);
  Lcd_Out(2, 4, txt2);
  Delay_ms(2500);

  while(1) {
    for(i=0; i<7; i++) {
      Lcd_Cmd(_LCD_SHIFT_LEFT);
      Move_Delay();
    }
    for(i=0; i<7; i++) {
      Lcd_Cmd(_LCD_SHIFT_RIGHT);
      Move_Delay();
    }
  }
}