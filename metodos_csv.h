#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "exibicao.h"

// Nome: Cleverson Pereira da Silva | TIA: 32198531
// Nome: Gustavo Teixeira dos Santos | TIA: 32197020

typedef struct { // Define Struct para armazenar os passos realizados pelo
                 // usuário

  char direcao;
  int valor;

} passos;

// FUNÇÃO PARA CHECAR SE A MATRIZ ESTÁ ORDENADA DE FORMA ITERATIVA
// Essa função trabalha seguindo algumas regras:
// 1 - Se o valor for checado for 0, então ele obrigatoriamente precisa estar na
// última posição da matriz 2 - Se o j (índice da coluna) for 0 e não estiver na
// primeira linha, ele checa o valor atual com a última coluna da linha anterior
// (Sua posição anterior na ordenação) 3 - Se o j (índice da coluna) for maior
// que 0 e não for a última coluna da linha da matriz, checa a posição atual com
// a próxima 4 - Se os laços finalizarem e a função ainda não tiver retornado
// false, então a matriz está ordenada



// FUNÇÃO PARA VERIFICAR SE A MATRIZ ESTÁ ORDENADA DE FORMA RECURSIVA
// Essa função recebe um vetor com todos os valores da matriz para fazer a
// checagem de forma recursiva Essa função segue algumas regras: 1 - Se a
// posição atual do vetor for maior que a anterior, ativa a recursividade
// passando tamanho = tamanho - 1. Caso contrário retorna false 2 - Se a função
// recursiva conseguir chegar no primeiro índice da matriz (Último valor da
// checagem), então a função é verdadeira.] OBS: A posição o 0 ja é checada
// antes da chamada da função
bool checaOrdenacao(int *vetor, int tamanhoVetor) {

  if (tamanhoVetor == 1) { // Se a variável tamanhoVetor estiver apontando para
                           // a primeira posição do vetor
return true;           // Retorna true
  } else {                 // Caso contrário
    if (vetor[tamanhoVetor - 1] >=
        vetor[tamanhoVetor -
              2]) { // Checa se a posição atual é >= à posição anterior
      return checaOrdenacao(
          vetor,
          tamanhoVetor - 1); // Caso a condição seja verdadeira, ativa a
                             // recursividade checando as posições anteriores
    } else {                 // Caso contrário
      return false;          // Retorna false
    }
  }
}

// FUNÇÃO PARA PRINTAR O PASSO ATUAL DA MATRIZ PARA O USUÁRIO
// Essa função foi criada pois em diversas áreas do software a matriz é exibida
// ao usuário

void printMatriz(int **matriz, int tamanhoMatriz) {

  for (int i = 0; i < tamanhoMatriz; i++) {
    for (int j = 0; j < tamanhoMatriz; j++) {
      if (matriz[i][j] >= 10)        // Se o valor atual da checagem for >= 10
        printf("%d ", matriz[i][j]); // Exibe somente o valor
      else                           // Caso contrário
        printf( "0%d ", matriz[i][j]); // Exibe um 0 antes do valor para ficar padronizado
    }
    printf("\n");
  }
}

// FUNÇÃO PARA RECEBER OS PASSOS DA MATRIZ E RESOLVE O JOGO
// Essa função procura onde está o 0 e faz as checagens e alterações a partir do
// 'ponto de vista' do mesmo

bool resolveMatriz(passos *passos, int **matriz, int tamanhoPassos, int tamanhoMatriz) {
  int linha, coluna, contador, *aux;
  // Bloco de código que encontra a exata posição do 0;

  linha = -1; // Linha e coluna recebem -1. Para checar se a tabela está no 
  // formato certo
  coluna = -1;
  for (int i = 0; i < tamanhoMatriz; i++) {
    for (int j = 0; j < tamanhoMatriz; j++) {
      if (matriz[i][j] == 0) { // Se a posição em específico da matriz for 0
        if (linha == -1 &&
            coluna ==
                -1) { // E ainda não tiver um valor atribuído à linha e coluna
                      // (Ou seja, ainda não foi encontrado nenhum 0)
          // Variáveis linha e coluna recebem a posição exata onde está o 0
          linha = i;
          coluna = j;
        } else {        // Caso contrário
          return false; // Retorna falso
        }
      }
    }
  }

  if (linha == -1 || coluna == -1) { // Se não encontrou um 0 na matriz
    return false;                    // retorna falso
  }

  // Bloco de código dedicado a resolução dos passos inseridos pelo usuário
  for (int i = 0; i < tamanhoPassos; i++) {

    switch (passos[i].direcao) { // Switch case para cada passo inserido

    case 'c': // Caso o passo indique 'para cima'

      if ((linha < tamanhoMatriz - 1) &&
          (matriz[linha + 1][coluna] ==
           passos[i].valor)) { // Se a posição abaixo do 0 for o número do passo
                               // e não estiver na última linha da matriz
        // troca a posição do número com a do 0 e atualiza a posição do mesmo
        matriz[linha + 1][coluna] = 0;
        matriz[linha][coluna] = passos[i].valor;
        linha++;
        printf("\n %dº passo: Colocando o número %d para cima\n", i + 1,
               passos[i].valor);

      } else {        // Caso contrário
        return false; // Retorna false
      }

      break;
    case 'b': // Caso o passo indique 'para baixo'

      if ((linha > 0) && (matriz[linha - 1][coluna] == passos[i].valor)) { 
        // Se a posição acima do 0 for o número do passo // e não estiver na primeira posição da matriz
        // Troca a posição do número com a do 0 e atualiza a posição do mesmo
        matriz[linha - 1][coluna] = 0;
        matriz[linha][coluna] = passos[i].valor;
        linha--;
        printf("\n %dº passo: Colocando o número %d para baixo\n", i + 1, passos[i].valor);
      } else {        // Caso contrário
        return false; // Retorna false
      }

      break;
    case 'd': // Caso o passo indique 'à direita'

      if ((coluna > 0) && (matriz[linha][coluna - 1] == passos[i].valor)) {
        // Se a posição à esquerda do 0 for o número do passo // e não estiver na primeira posição da coluna
        // Troca a posição do número com a do 0 e atualiza a posição do mesmo
        matriz[linha][coluna - 1] = 0;
        matriz[linha][coluna] = passos[i].valor;
        coluna--;
        printf("\n %dº passo: Colocando o número %d para direita\n", i + 1, passos[i].valor);
      } else {        // Caso contrário
        return false; // Retorna false
      }

      break;
    case 'e': // Caso o passo indique 'à esquerda'

      if ((coluna < tamanhoMatriz - 1) &&
        (matriz[linha][coluna + 1] == passos[i].valor)) { 
        // Se a posição à direita do 0 for o número do passo e// não estiver na última posição da coluna
        // Troca a posição do número com a do 0 e atualiza a posição do mesmo
        matriz[linha][coluna + 1] = 0;
        matriz[linha][coluna] = passos[i].valor;
        coluna++;
        printf("\n %dº passo: Colocando o número %d para esquerda\n", i + 1, passos[i].valor);
      } else {        // Caso contrário
        return false; // Retorna false
      }

      break;
    }

    imprime(matriz, tamanhoMatriz, tamanhoMatriz); // Ao final de cada passo, printa o // estado atual da matriz
  }

  // Inicia os passos para chamar as funções iterativas e recursivas
  if (matriz[tamanhoMatriz - 1][tamanhoMatriz - 1] == 0) { // Se a última posição da matriz for 0
    aux = (int*)malloc((tamanhoMatriz * tamanhoMatriz) * sizeof(int)); // Inicia um vetor para receber os valores da // matriz e ser enviado para a função recursiva
    contador = 0;

    for (int i = 0; i < tamanhoMatriz; i++) {
      for (int j = 0; j < tamanhoMatriz; j++) {
        aux[contador] = matriz[i][j]; // Copia o valor em específico da matriz // para a posição em específico do vetor
        contador++; // Atualiza o contador
      }
    }

    if (checaOrdenacao(aux, tamanhoMatriz * tamanhoMatriz - 1) == true) { // Se estiver ordenado
      return true;  // Retorna true
    }else{        // Caso contrário
      return false; // Retorna false
    }
  } else { // Se a última posição da matriz não for 0, nem realiza a checagem e // ja retorna false
    return false; // Retorna false
  }
}