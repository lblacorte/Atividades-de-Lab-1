#include <stdio.h>     // para ter acesso às funções getchar e putchar
#include <stdbool.h>   // para ter 'true', 'false' e 'bool'

// calcula o valor de um número formado pelos dígitos decimais que encontrar na entrada
// para quando encontrar um caractere que não é um dígito
// retorna o valor calculado em um inteiro, por isso o tipo de retorno é 'int'
int le_int(void)
{
  int v;  // variável onde é colocado o valor que está sendo calculado
  v = 0;  // começa o valor com 0
  int d;  // variável que vai conter cada caractere lido da entrada

  while (true) {  // repete para sempre (ou até que alguma outra coisa acabe com a repetição)
    // cada repetição pega um dígito e anexa ao número que está sendo calculado
    d = getchar();
    if (d < '0') {
      return v;  // caracteres antes do '0' não interessam, retorna o que foi calculado até agora
    }
    if (d > '9') {
      return v;  // caracteres depois do '9' também não interessam
    }
    // se chegar aqui, o caractere em 'd' é um dígito decimal
    // anexa o valor do dígito ao valor que está sendo calculado
    v = v*10 + d-'0';
  } // fim do while, volta pro início

  // não tem como chegar aqui (por que?)
  return v;
}


// imprime o valor do argumento 'x' em dígitos decimais
// o valor de um dígito de 'x' é obtido dividindo x por uma potência de 10 (1, 10, 100 etc) e
// pegando o resto da divisão desse valor por 10.
// essa função não retorna nada, por isso o tipo de retorno é 'void'
void imprime(int x)
{
  // se o número for negativo, imprime um '-' e transforma o número em positivo
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  // faz 'd' ser uma potência de 10 com o mesmo número de dígitos de 'x'
  int d = 1;
  while (d*10 <= x) {
    d = d*10;
  }
  // imprime cada dígito -- 'd' é a potência de 10 do dígito a imprimir
  // imprime com cada potência que for maior ou igual a 1, diminuindo a potência a cada vez
  while (d >= 1) {
    putchar('0'+x/d%10);
    d = d/10;
  }
}


int main()
{
  int x;

  x = le_int();
  imprime(x);
  putchar('\n');
  x = le_int();
  imprime(x);
  putchar('\n');
}