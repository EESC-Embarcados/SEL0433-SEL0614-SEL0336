#include "calculo.h"    // #include "nome.h" - arquivo no diretório do projeto
                       // #include <nome.h> - arquivo no diretório do compilador

// inclui o protótipo da função soma exatamente aqui nesta área do código
// unsigned char soma(char _b, char _c);

// #include <stdio.h>    - standard input-output header - cabeçalho padrão de
// entrada e saída - possui definições de leitura de dados no teclado, exibição
// de informações na tela, constantes, var. e tipos. 
// Funções stdio.h: printf(); scanf(); fprintf(); fscanf();

//------------------------------------------------------------------------------

  /* Uma função que deve ser definida antes da sua chamada no código
   (ordem do compilador é de cima para baixo), definindo os parâmetros e o
   retorno.
   Por essa razão se faz necessário o protótipo da função:
  
   unsigned char soma(char _b, char _c);  // exemplo de protótipo de função
  
   Ao invés de inserir o protótipo neste código, o arquivo .h pode ser incluido
  
  A geração do arquivo objeto depende das folhas associadas ao projeto. Assim,
  neste arquivo é necessário incluir as funções, diretivas e cabeçalhos que
  farão parte deste projeto.
  */
 
 // outro exemplo:
 /*
      unsigned char soma2(unsigned char t1, unsigned int t2)
{
     return(t1+t2);
}
 */
 
 // variável global: fora do main (usada em todas funções)- endereço de memória
 // reservado e não pode ser realocado
 
 
void main() {           // a função main é void (não retorna valor) pois é a...
// é a função principal e não retorna valores para outras funções. Outro exemplo
//: função Delay - não retorna valor, apenas realiza o atraso

// variável local - dentro de uma função e só existe quando for executada, a
// variável será criada em memória, porém, depois o endereço é liberado, após a
// execução deste bloco  - poupa memória

     PORTB = soma(10,20);     // PORTB = 30;
     
    
     // Outro exemplo:
    // unsigned char x1 = 0;        // unsigned 0 a 255
     //x1 = soma2(56,200);   // x1 = 0 (não suporta valor maior do que 255)
     
     // solução: unsinged int x1 =0;
     // protótipo: unsigned int soma2(unsigned char t1, unsigned int t2)
     
     // Se o retorno da função for 12.5f = float x1; float soma2(...);
}