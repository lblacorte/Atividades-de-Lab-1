#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void corl(int r, int g, int b)
{
  printf("\e[38;2;%d;%d;%dm", r, g, b);
}
void corf(int r, int g, int b)
{
  printf("\e[48;2;%d;%d;%dm", r, g, b);
}
void corn(void)
{
  printf("\e[m");
}
void pos(int lin, int col)
{
  printf("\e[%d;%dH", lin, col);
}
void limpa(void)
{
  printf("\e[2J");
}

int main()
{
  srand(time(0));
  limpa();
  pos(1, 10);
  corl(180, 100, 50);
  corf(30, 50, 80);
  printf("Texto em cima");
  corl(120, 0, 250);
  printf("Em outra cor");
  getchar();
  for (int i=0; i<1000; i++) {
    int a = rand()%20;
    int b = rand()%40;
    pos(a, b);
    corf(rand()%50+10*a, rand()%100, rand()%50+5*b);
    putchar(' ');
  }
  corn();
  getchar();
  limpa();
  printf("tchau\n");
}