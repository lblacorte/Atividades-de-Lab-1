#include <stdio.h>
#include <stdbool.h>

//Junção das funções em uma só, testa na própria função:
float calculo(char operacao, float total, float num){ //recebe operação e dois números
  switch(operacao){
    case '+': total += num;
      break;
    case '-': total -= num;
      break;
    case '*': total *= num;
      break;
    case '/': total /= num;
      break;
  }
  return total; //retorna o total
}

int main(){
  float num, numE, total; //numE = o número "esperando"
  char operacao, operacaoE; //operacaoE = operação esperando
  bool ultimaMD = false; //esse booleano foi necessário para o caso de mais de um * ou / em sequência, para saber se já havia ocorrido alguma multiplicação ou divisão (última Múltiplicação/Divisão)
  
  printf("\nDigite a operação desejada: ");
    
  scanf("%f", &num); //retirei o contador e fiz a primeira leitura fora do laço
  total = num; //o primeiro total é o próprio número
  
  while(operacao != '\n'){ //o laço ocorre enquanto o operador não for Enter

    operacao = getchar(); //pega o caractere digitado como operador, getchar consegue pegar o enter

    if(operacao != '\n'){ //pede um número apenas se não for dado enter (fim da linha de cálculo)
      scanf("%f", &num);
    }

//Condição separada para informar erro quando um caractere inválido é digitado, não dá pra fazer na função calculo()
    if(operacao != '+' && operacao != '-' && operacao != '*' && operacao != '/' && operacao != '\n'){
      printf("\nO caractere \"%c\" não representa uma operação válida! Tudo que foi digitado a partir dele foi desconsiderado no cálculo do resultado.\n", operacao);
      operacao = '\n'; //Para que o laço se encerre e não sejam efetuados mais cálculos sobre o total
    }

//Condição em separado para implementar prioridade quando for efetuado * ou / depois de + ou -
    if((operacao == '+' || operacao == '-') && ultimaMD == true && (operacaoE == '+' || operacaoE == '-')){
      total = calculo(operacaoE, numE, total); //Cálculo do número esperando sobre o resultado de * ou /
      operacaoE = '\0'; //Não há mais operações pendentes sobre o resultado de * ou /
      ultimaMD = false; //Não há mais * ou / a ser analisada
    }

//Cálculo de * ou /
    if(operacao == '*' || operacao == '/'){
      total = calculo(operacao, total, num);
      ultimaMD = true; //retorna que já foi realizada uma multiplicação ou divisão, preciso saber se o que vem depois também é * ou / ou se é + ou -, pois caso seja + ou - já pode ser feita a operação anterior pendente de + ou - se houver, se for * ou / preciso fazer todos essas multiplicações e divisões antes de somar ou diminuir (para poder usar apenas duas variáveis).
    }
    else if(operacao == '+' || operacao == '-'){ // caso de + ou -
      if(operacaoE == '+' || operacaoE == '-'){ //caso de haver mais de um + ou - em sequência
        total = calculo(operacaoE, numE, total);
      }
    //preciso saber se há * ou / após, então guardo em outra variável, após retornar no laço é feita a prioridade
      numE = total; //numE passa a ser o total até agora
      total = num; //o total passa a ser o último número recebido
      operacaoE = operacao; //guardo a operação na variável reserva
    }
    //Cálculo final, caso houverem operações de + ou - pendentes
    else if(operacao == '\n' && (operacaoE == '+' || operacaoE == '-')){
      total = calculo(operacaoE, numE, total);
    }
  }
  printf("\nO resultado é: %g\n", total);//apresenta o resultado
}