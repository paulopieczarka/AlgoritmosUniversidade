#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo_matriz.c"

/* Cria um grafo vazio de tamanho n. 
   Procedimento gera um grafo contendo n vértices e nenhuma aresta. */
void geraGrafoVazio(Grafo *g, int n);

/* Cria um grafo de n vértices com atestas geradas aleatoriamente, 
   ponderadas ou não, onde pMax é o maior peso de aresta que pode ser 
   gerado aleatoriamente. */
void geraGrafoRand(Grafo *g, int n, int pMax);

/* Insere um novo vértice no grafo. */
void insereVertice(Grafo *g);

/* Insere uma aresta no grafo. O procedimento recebe a aresta (v1,v2) e 
   seu peso para serem inseridos no Grafo. */
void insereAresta(int v1, int v2, int peso, Grafo *g);

/* Retorna o peso da aresta (v1,v2). */
int retornaAresta(int v1, int v2, Grafo *g);

/* Retira a aresta (v1,v2) do grafo retornando seu peso na variável peso. */
void retiraAresta(int v1, int v2, int *peso, Grafo *g);

/* Retira a aresta de menor peso do grafo e retorna seu peso. */
int retiraMin(Grafo *g);

/* Retira a aresta de maior peso no grafo e retorna seu peso. */
int retiraMax(Grafo *g);

/* Imprime o grafo na forma matricial. */
void imprimeGrafo(Grafo *g);

void imprimeAdjacencias(Grafo *g);

/* Limpa todas as arestas do grafo. No caso de implementações alocação 
   dinâmica a memória também é liberada. */
void limpaGrafo(Grafo *g);