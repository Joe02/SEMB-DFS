void setup() {
  Serial.begin (4800);
}

/************************

   Algoritmo de Busca em profundidade
   ______

  Copyright 2021 Joel Araújo da Silva, Gilberto Magno

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in the
  Software without restriction, including without limitation the rights to use, copy,
  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the
  following conditions:

  The above copyright notice and this permission notice shall be included in all copies
  or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
  AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

//
// Created for a college projetct
// Course: Sistemas Embarcados @ IFCE - Instituto Federal de Educação, Ciência e Tecnologia do Ceará
// Target Platform: Linux
//





//Bibliotecas necessárias para o algoritmo.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Número máximo de Nodes. Também é a referência para a matriz de adjacências utilizada na verificação de relações.
#define N_NODES 46
#define UCHAR_BYTE_SIZE 8

//Número correspondente à label do vértice-objetivo.
#define N_TO_REACH 44

//Vértice.
typedef struct {
  unsigned char label;
  unsigned char visited;
  unsigned char edges[N_NODES / UCHAR_BYTE_SIZE + 1]; // always take more than required
} Vertex;



//----------------------------------Variáveis necessárias para a pilha.

char stack[N_NODES];
char top = -1;
char counter = -1;
unsigned int bestSolution = 9999;
Vertex lstVertices[N_NODES];
unsigned char vertexCount = 0;




//----------------------------------Funções da Pilha.

//Adiciona um item a pilha.
void push(char item) {
  stack[++top] = item;
}

//Remove o último item adicionado a pilha.
int pop() {
  return stack[top--];
}

//Retorna o valor do último vértice adicionado a pilha.
int peek() {
  return stack[top];
}

//Verificação para saber se a pilha está vazia.
bool isStackEmpty() {
  return top == -1;
}




//----------------------------------Adiciona o vértice na lista de vértices.
void addVertex(unsigned char label)
{
  Vertex vertex;
  vertex.label = label;
  vertex.visited = 0;
  for (int i = 0; i < N_NODES / UCHAR_BYTE_SIZE + 1; ++i) {
    vertex.edges[i] = 0;
  }
  lstVertices[vertexCount++] = vertex;
}



//----------------------------------Adiciona uma relação entre 2 vértices
// void addEdge(unsigned int start, unsigned int end)
// {
//     //Como estamos tratando de uma matriz de adjacências, é necessário criar relações bidirecionais para evitar que
//     //um vértice seja acessado e após isso seja impossível de voltar para o anterior.
//     lstVertices[start].edges[end] = 1;
// }

void addEdge(int start, int end) {
  int section = floor(end / UCHAR_BYTE_SIZE);
  lstVertices[start].edges[section] = lstVertices[start].edges[section] | (1 << end % UCHAR_BYTE_SIZE);

  // add the opposite edge here
  section = floor(start / UCHAR_BYTE_SIZE);
  lstVertices[end].edges[section] = lstVertices[end].edges[section] | (1 << start % UCHAR_BYTE_SIZE);
}


//----------------------------------Printa o vértice.
void displayVertex(unsigned char vertexIndex)
{
  Serial.print(lstVertices[vertexIndex].label);
  Serial.print(" ");
}


//----------------------------------Pega os próximos vértices (em ordem crescen de 0 a N) a partir do vértice atual.
int getAdjUnvisitedVertex(unsigned int vertexIndex, char baseCount) {
  int i;

  for (i = 0; i < N_NODES / UCHAR_BYTE_SIZE + 1; i++) {
    int encoded_edges = lstVertices[(int)vertexIndex].edges[i];
    for (int j = 0; j < UCHAR_BYTE_SIZE; ++j)
    {
      int vertexIdx = i * UCHAR_BYTE_SIZE + j;
      if ((encoded_edges & ( 1 << j )) >> j == 1) {
        if (lstVertices[vertexIdx].visited == 0) {

          return (int)vertexIdx;

        }

        if (lstVertices[vertexIdx].label == N_TO_REACH) {
          if (baseCount + 1 < bestSolution) {

            bestSolution = baseCount + 1;

            if (baseCount == 0) {

              displayVertex(0);
            }

            displayVertex(vertexIdx);
          }
        }
      }
    }
  }

  return -1;
}



//----------------------------------Método de pesquisa em profundida.
void depthFirstSearch() {
  unsigned char i;

  //Sempre marca o primeir vértice como visitado.
  lstVertices[0].visited = 1;

  displayVertex(0);

  push(0);

  unsigned char pathName = 1;
  Serial.print("Caminho ");
  Serial.println(pathName);

  //Enquanto existir um elemento na pilha =>
  while (!isStackEmpty()) {

    int unvisitedVertex = getAdjUnvisitedVertex(peek(), top);
    //Caso não existam nós adjacentes não visitados então o algoritmo chama a função pop para retornar para a posição
    //anterior e tentar novos caminhos a partir dela.
    if (unvisitedVertex == -1) {
      pop();
      if (top == 0) {
        pathName++;
        Serial.println("");
        Serial.println("");
        Serial.print("Caminho ");
        Serial.println(pathName);
      }
    } else {
      //Caso contrário seguir com a pesquisa por novos vértices que possuam relações adjancentes com o atual.
      if (lstVertices[unvisitedVertex].label == N_TO_REACH) {

        if (top + 1 < bestSolution) {
          bestSolution = top + 1;
        }
        else if (bestSolution == -1) {
          bestSolution = top + 1;
        }
      }
      if (top == 0) {
        displayVertex(0);
      }
      lstVertices[unvisitedVertex].visited = 1;
      displayVertex(unvisitedVertex);
      push(unvisitedVertex);
    }
  }

  //Reinicia os valores de visita de todos os vértices, para o caso de existirem duas pesquisas numa mesma execução.
  for (i = 0; i < vertexCount; i++) {
    lstVertices[i].visited = 0;
  }
}



//----------------------------------Função Main
//Aqui os vértices serão criados, assim como as relações.

bool runCode = true;
void loop() {
  while (runCode) {
    //---------------------------------- Início dos casos de teste.
    for (unsigned char aux = 0; aux < N_NODES; aux++) {
      addVertex(aux);
    }

    //Cria a relação entre o primeiro e o último vértice.
    addEdge(0, N_TO_REACH); // Creates relation 0 -> N_TO_REACH

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(5, 6);
    addEdge(6, 7);
    addEdge(7, 8);
    addEdge(8, 9);
    addEdge(9, 10);
    addEdge(10, 11);
    addEdge(11, 12);
    addEdge(12, 13);
    addEdge(13, 14);
    addEdge(14, 15);
    addEdge(15, 16);
    addEdge(16, 17);
    addEdge(17, 18);
    addEdge(18, 19);
    addEdge(19, 20);
    addEdge(20, 21);
    addEdge(21, 22);
    addEdge(22, 23);
    addEdge(23, 24);
    addEdge(24, 25);
    addEdge(25, 26);
    addEdge(26, 27);
    addEdge(27, 28);
    addEdge(28, 29);
    addEdge(28, 30);
    addEdge(29, 45);
    addEdge(30, 31);
    addEdge(31, 32);
    addEdge(32, 33);
    addEdge(33, 34);
    addEdge(34, 35);
    addEdge(35, 36);
    addEdge(36, 37);
    addEdge(37, 38);
    addEdge(38, 39);
    addEdge(39, 40);
    addEdge(40, 41);
    addEdge(41, 42);
    addEdge(42, 43);
    addEdge(43, 44);
    addEdge(44, 45);

    // //---------------------------------- Fim dos casos de teste.
    depthFirstSearch();

    //Aqui comparamos o resultado final.
    //Caso a melhor solução seja diferente de -1 (padrão escolhido por propósitos de teste), retorne o custo da resposta.

    if (bestSolution != 9999) {
      Serial.println();
      Serial.print("Custo do melhor caminho partindo de 0 ate ");
      Serial.print(N_TO_REACH);
      Serial.print(" == ");
      Serial.print(bestSolution);
      Serial.println(" unidades");
    } else {
      Serial.println("");
      Serial.println("");
      Serial.println("Esse problema nao tem solucoes :(");
    }
    runCode = false;
  }
}
