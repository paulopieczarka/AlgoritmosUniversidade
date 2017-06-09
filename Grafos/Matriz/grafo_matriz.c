#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

typedef struct 
{
	int len;
	int arr[MAX][MAX];
} Grafo;

void insereVertice(Grafo *g);
void insereAresta(int v1, int v2, int peso, Grafo *g);
void imprimeGrafo(Grafo *g);

/* Cria um grafo vazio de tamanho n. 
   Procedimento gera um grafo contendo n vértices e nenhuma aresta. */
void geraGrafoVazio(Grafo *g, int n)
{
	g->len = 0;

	int i;
	for(i=0; i < n; i++){
		insereVertice(g);
	}
}

/* Cria um grafo de n vértices com atestas geradas aleatoriamente, 
   ponderadas ou não, onde pMax é o maior peso de aresta que pode ser 
   gerado aleatoriamente. */
void geraGrafoRand(Grafo *g, int n, int pMax)
{
	srand(time(NULL));
	int max = pMax > MAX ? MAX : pMax;

	printf(" Gerando grafo.. [verticies=%d]\n Arestas: ", n);
	geraGrafoVazio(g, n);

	int i, j, peso = 0;
	for(i=0; i < g->len; i++)
	{
		for(j=0; j < g->len; j++)
		{
			if(rand()%2 == 0)
			{
				peso = rand()%pMax + 1;
				printf("(%d,%d,%d) ", i, j, peso);
				insereAresta(i, j, peso, g);
			}
		}
	}

	printf("\n");
}

/* Insere um novo vértice no grafo. */
void insereVertice(Grafo *g)
{
	// TODO: CHECK IF MAX > g->len.
	if(g->len+1 >= MAX)
	{
		printf(" Maximo atingido deve ser menor que %d.\n", MAX);
		return;
	}

	int i;
	int col = g->len;
	g->len++;

	for(i=0; i < g->len; i++)
	{
		// printf(" >> %d -> [%d,%d] [%d,%d]\n", g->len, col, i, i, col);
		g->arr[col][i] = 0;

		if(col != i) {
			g->arr[i][col] = 0;
		}
	}
}

/* Insere uma aresta no grafo. O procedimento recebe a aresta (v1,v2) e 
   seu peso para serem inseridos no Grafo. */
void insereAresta(int v1, int v2, int peso, Grafo *g)
{
	if(v1 < 0 || v2 < 0 || v1 >= g->len || v2 >= g->len)
	{
		printf(" Out of bounds.\n");
		return;
	}

	g->arr[v1][v2] = peso;
}

/* Retorna o peso da aresta (v1,v2). */
int retornaAresta(int v1, int v2, Grafo *g)
{
	if(v1 < 0 || v2 < 0 || v1 >= g->len || v2 >= g->len)
	{
		printf(" Out of bounds.\n");
		return -1;
	}

	return g->arr[v1][v2];
}

/* Retira a aresta (v1,v2) do grafo retornando seu peso na variável peso. */
void retiraAresta(int v1, int v2, int *peso, Grafo *g)
{
	if(v1 < 0 || v2 < 0 || v1 >= g->len || v2 >= g->len)
	{
		printf(" Out of bounds.\n");
		return;
	}

	*peso = g->arr[v1][v2];
	g->arr[v1][v2] = 0;
}

/* Retira a aresta de menor peso do grafo e retorna seu peso. */
int retiraMin(Grafo *g)
{
	int i, j, mi = -1, mj, min = 0;

	for(i=0; i < g->len; i++)
	{
		for(j=0; j < g->len; j++)
		{
			if(g->arr[i][j] != 0)
			{
				if(mi == -1 || min > g->arr[i][j])
				{
					mi = i; mj = j;
					min = g->arr[i][j];
				}
			}
		}
	}

	if(mi == -1)
	{
		printf("\n Nada para retirar.\n");
		return 0;
	}

	int minPeso;
	retiraAresta(mi, mj, &minPeso, g);
	printf("\n Menor at %d, %d.\n", mi, mj);

	return minPeso;
}

/* Retira a aresta de maior peso no grafo e retorna seu peso. */
int retiraMax(Grafo *g)
{
	int i, j, mi = -1, mj, min = 0;

	for(i=0; i < g->len; i++)
	{
		for(j=0; j < g->len; j++)
		{
			if(g->arr[i][j] != 0)
			{
				if(mi == -1 || min < g->arr[i][j])
				{
					mi = i; mj = j;
					min = g->arr[i][j];
				}
			}
		}
	}

	if(mi == -1)
	{
		printf("\n Nada para retirar.\n");
		return 0;
	}

	int minPeso;
	retiraAresta(mi, mj, &minPeso, g);
	printf("\n Maior at %d, %d.\n", mi, mj);

	return minPeso;
}

/* Imprime o grafo na forma matricial. */
void imprimeGrafo(Grafo *g)
{
	printf("\n Grafo com %d vertices:\n\n", g->len);

	int i, j;
	for(i=0; i < g->len; i++)
	{
		// Index coluna.
		if(i == 0)
		{
			for(j=0; j < g->len; j++)
			{
				if(j == 0){
					printf("     ");
				}

				printf("%3d ", j);
			}
			printf("\n\n");
		}

		for(j=0; j < g->len; j++)
		{
			if(j == 0){
				printf("%3d  ", i);
			}

			printf("%3d ", g->arr[i][j]);	
		}

		printf("\n");
	}
}

void imprimeAdjacencias(Grafo *g)
{
	int i, j;
	for(i=0; i < g->len; i++)
	{
		for(j=0; j < g->len; j++)
		{
			if(retornaAresta(i, j, g) == 0)
				continue;

			printf(" [%d]----- %d -----[%d]\n", i, retornaAresta(i, j, g), j);
		}
	}
}

/* Limpa todas as arestas do grafo. No caso de implementações alocação 
   dinâmica a memória também é liberada. */
void limpaGrafo(Grafo *g)
{
	free(g);
}