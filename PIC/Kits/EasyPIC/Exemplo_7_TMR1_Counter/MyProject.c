 /* Exemplo de uso do Timer1/3 no modo contador
 
 - Monitora o pino T13CkI(RC0) e conta 10 eventos
 - Um bot�o ser� usado como exemplo e ao ser pressionado
 ir� incrementar o contador
 - No 10� incremento ocorrer� o overflow do timer e uma a��o de sinaliza��o
 dever� ser executada
 
 ----------------------------------------------------------------------------
 - Configura��o do timer1:
 >> O TMR1 no modo contador � associado ao pino externo T13CkI (pino RC0) do PIC, 
 pois monitora a mudan�a de borda neste pino para incrementar o registrador de 
 contagem a cada borda de subida ou de descida. Ao contr�rio do modo de contagem
  de tempo,  no qual o registrador de contagem � incrementado a cada pulso do
  clock

 >> usa os registradores T1CON, TMR1H e TMR1L, e a flag TMR1IF que se encontra
 no reg. PIR1 (PIR1.TMR1IF ou TMR1IF_bit), a qual deve ser zerada manualmente
 
 >> Como ser�o 10 eventos, n�o ser� necess�rio usar Preescaler, portanto, ser� 1:1
 >> Logo, dever� ser carregado o valor inicial de 65526 (65536-10) considerando
 o modo 16 bits, no qual o estouro ocorre em 2^16.
 
*/


void main() {

ADCON1=0x0F;   // Pinos digitais

TRISC.RC0=1; // RC0 como entrada pois corresponde ao pino T1CK1 que incrementa a 
//contagem do TMR1
// � um pino fixo - ou seja, deve-se obrigatoriamente usar este pino para contar no
//timer 1 - portanto � nele que deve-se ligar um sensor ou bot�o ou algum outro
//dispositivo que se desejar contar eventos

PORTC.RC0=1;  // em pull-up

TRISD=0;   // PORTD como entrada
PORTD=0;   //inicialmente zero (LED)

PORTD.RD1=0;

T1CON =0B10000011; // Config. do timer1 no modo contador, 16 bits, ligado

// valores iniciais para contar at� 10 eventos > 65526 = FFF6 em hexadecimal
TMR1H=0xFF;
TMR1L=0xF6;

PIR1.TMR1IF=0;//Flag do timer 1 em zero (vai para 1 quando ocorre overflow)


while(1){
         if(TMR1IF_bit){  // monitora a flag - se igual 1
               PORTD.RD1=1; //a��o quando totalizar 10 eventos
               TMR1H=0xFF;   //recarrega o timer para nova contagem
               TMR1L=0xF6;
               PIR1.TMR1IF=0;   //zera flag para nova contagem
               Delay_ms(1000);    // aguarda um tempo com a sinaliza��o acionada
               }
         else{
         PORTD.RD1=0; // LED desligado caso contr�rio
         }
 
 }

}