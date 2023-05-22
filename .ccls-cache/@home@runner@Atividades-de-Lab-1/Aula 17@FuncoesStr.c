#include <stdio.h>

int meustrlen(char s[])
{
  int i;
  for (i = 0; s[i] != '\0'; i++){
    ;
  }
  return i;
}

void meustrcpy(char s[], char s2[])
{
  for (int i = 0; s2[i] != '\0'; i++){
    s[i] = s2[i];
  }
  i++;
  s[i] = s2[i]
}

void meustrcat(char s[], char s2[])
{
  int tam = meustrlen(s);
  for (int i = 0; s2[i] != '\0'; i++){
    s[i+tam] = s2[i];
  }
}

int main()
{
  char s[30];
  char nome[30];
  printf("Qual seu nome? ");
  scanf("%9s", nome);
  meustrcpy(s, "Seu nome é ");
  meustrcat(s, nome);
  printf("%s, com %d letras\n", s, meustrlen(nome));
}