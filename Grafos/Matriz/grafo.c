#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

void subSystem(Grafo *g);

void gerarGrafoVazio()
{
	system("clear");
	printf("\n [1] Gerar grafo vazio:\n\n");
	printf(" Numero de vertices (max=%d): ", MAX-1);

	int len;
	scanf("%d", &len);

	if(len >= MAX){
		printf(" DEMAIS!!1 Deveria ser < %d.\n", MAX);
	}
	else
	{
		Grafo g;
		geraGrafoVazio(&g, len);
		
		subSystem(&g);
	}
}

void gerarGrafoAleatorio()
{
	system("clear");
	printf("\n [2] Gerar grafo random:\n\n");

	int len, max;

	printf(" Numero de vertices (max=%d): ", MAX-1);
	scanf("%d", &len);

	printf(" Peso max: ");
	scanf("%d", &max);

	if(len >= MAX){
		printf(" DEMAIS!!1 Deveria ser < %d.\n", MAX);
	}
	else
	{
		Grafo g;
		geraGrafoRand(&g, len, max);

		subSystem(&g);
	}
}

void subSystem(Grafo *g)
{
	system("clear");
	imprimeGrafo(g);

	printf("\n");
	printf(" [1] Nova aresta.\n");
	printf(" [2] Novo no.\n");
	printf(" [3] Verificar adjacencia.\n");
	printf(" [4] Listar todas as adjacencias.\n");
	printf(" [5] Retira menor aresta.\n");
	printf(" [6] Retira maior aresta.\n");
	printf(" [7] Imprime grafo.\n");
	printf("\n [0] Sair.\n");
	printf("\n Ir para: ");

	int cmd;
	scanf("%d", &cmd);

	if(cmd == 1)
	{
		int v1, v2, peso;
		printf(" Valor v1: ");
		scanf("%d", &v1);

		printf(" Valor v2: ");
		scanf("%d", &v2);

		printf(" Valor peso: ");
		scanf("%d", &peso);

		insereAresta(v1, v2, peso, g);
	}
	else if(cmd == 2)
	{
		insereVertice(g);
	}
	else if(cmd == 3)
	{
		int v1, v2;
		printf(" Valor v1: ");
		scanf("%d", &v1);

		printf(" Valor v2: ");
		scanf("%d", &v2);

		int arr = retornaAresta(v1, v2, g);
		if(arr < 1){
			printf(" Não possui adjacencia.\n");
		}
		else
		{
			printf(" Possui adjacencia com peso %d.\n", arr);
		}

		getchar(); getchar();
	}
	else if(cmd == 4)
	{
		printf("\n Adjacencias:\n\n");
		imprimeAdjacencias(g);
		getchar(); getchar();
	}
	else if(cmd == 5)
	{
		retiraMin(g);
		getchar(); getchar();
	}
	else if(cmd == 6)
	{
		retiraMax(g);
		getchar(); getchar();
	}
	else if(cmd == 7)
	{
		// Do nothing.
	}
	else if(cmd == 0)
	{
		//limpaGrafo(g);
		printf(" Bye.\n");
	}
	else
	{
		printf(" Opcao invalida.\n");
		getchar(); getchar();
	}

	// Para sair.
	if(cmd != 0){
		subSystem(g);
	}
}