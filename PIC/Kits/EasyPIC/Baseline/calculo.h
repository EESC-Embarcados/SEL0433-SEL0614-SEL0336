// arquivo cabeçalho .h (header): definições  e protótipo de funções


 // Encapsulamento do arq. header - evita duplicação de variáveis caso este
 // mesmoa arquivo .h for incluido em várias folhas de projeto. Por exemplo, se
 // aqui neste arquivo uma variav. "char a1" for declarada ela será duplicada,
 // no padrão ANSI uma variável global não deve ser duplicada.
 // Para tanto, usa-se a diretiva abaixo #ifndef (só define a função calculo se
 // ainda não foi definida). Caso uma folha já tenha incluido o arquivo .h ela
 // não será redefinida
 
#ifndef __calculo__
#define __calculo__

 unsigned char soma(char _b, char _c);// protótipo da função soma

#endif