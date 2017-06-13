#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "grafo_matriz.h"

#define MAX_NOME 32

typedef struct {
    char sigla;
    char nome[MAX_NOME];
} Cidade;

typedef struct {
    int current;
    Cidade list[];
} CidadeList;

void startCidades();
void inserirCidade(Grafo *g, CidadeList *cl, char nome[MAX_NOME], char sigla);
void printMatriz(Grafo *g, CidadeList *cl);
void inserirInterconexao(Grafo *g, int c1, int c2, int distance);
void geraMapaRandInter(Grafo *g);
void imprimeAdjCidades(Grafo *g, CidadeList *cl);
void menuInserirCidade(Grafo *g, CidadeList *cl);
void menu(Grafo *g, CidadeList *cl);
void menuInserirInterconexao(Grafo *g);

void startCidades()
{
    // Cidades holder.
    Grafo g;
    CidadeList *cityList;
    cityList = (CidadeList*)malloc(sizeof(CidadeList));
    cityList->current = 0;

    menu(&g, cityList);
}

void menu(Grafo *g, CidadeList *cl)
{
    system("clear");
    printMatriz(g, cl);

    printf("\n [1] Randomizar Interconexoes.\n");
    printf(" [2] Inserir cidade.\t[3] Inserir Interconexao.\n");
    printf(" [4] Remover cidade.\t[5] Remover Interconexao.\n");
    printf("\n [0] TALVEZ FINALIZE.\n");

    int cmd;
    printf("\n Happy cmd: "); 
    scanf(" %d", &cmd);

    if(cmd == 1){
        geraMapaRandInter(g);
    }
    else if(cmd == 2){
        menuInserirCidade(g, cl);
    }
    else if(cmd == 3){
        menuInserirInterconexao(g);
    }
    else if(cmd == 4){
        int v = 0;
        printf(" Remover qual cidade? ");
        scanf("%d", &v);

        //TODO: Remove arresta?
    }
    else if(cmd == 5){
        int v1, v2;
        printf(" c1: "); scanf("%d", &v1);
        printf(" c2: "); scanf("%d", &v2);

        retiraAresta(v1, v2, 0, g);
    }

    if(cmd != 0){
        menu(g, cl);
    }
}

/* ---------- FUNCTIONS ----------- */

void inserirCidade(Grafo *g, CidadeList *cl, char nome[MAX_NOME], char sigla)
{
    Cidade *city = (Cidade*)malloc(sizeof(Cidade));

    if(city != NULL)
    {
        city->sigla = sigla;
        strcpy(city->nome, nome);
        printf(" --> Cidade %s adicionada.\n", city->nome);
        cl->list[cl->current] = *city;
        cl->current++;

        insereVertice(g);
    }
}

void menuInserirCidade(Grafo *g, CidadeList *cl)
{
    char nome[MAX_NOME];
    char sigla;

    printf(" > Nome cidade: ");
    scanf("%s", nome);

    printf(" > Sigla cidade (char): ");
    scanf(" %c", &sigla);

    inserirCidade(g, cl, nome, sigla);
}

void inserirInterconexao(Grafo *g, int c1, int c2, int distance)
{
    insereAresta(c1, c2, distance, g);
}

void menuInserirInterconexao(Grafo *g)
{
    int v1, v2, p;
    printf(" > c1: "); scanf("%d", &v1);
    printf(" > c2: "); scanf("%d", &v2);
    printf(" > distancia: "); scanf("%d", &p);

    inserirInterconexao(g, v1, v2, p);
}

/* Gera um mapa aleatório de interconexões. */
void geraMapaRandInter(Grafo *g)
{
    srand(time(NULL));
    int pMax = rand()%999;

    geraGrafoRand(g, g->len, pMax);
}

/* ---------- INTERFACE ----------- */

/* Stupid way to print a matrix. */
void printMatriz(Grafo *g, CidadeList *cl)
{
    printf("\n Adjacencias em km: \n\n");

    int i, j;
    for(i=0; i < g->len; i++)
    {
        if(i == 0)
        {
            printf("    ");
            for(j=0; j < g->len; j++){
                printf("%4c", cl->list[j].sigla);
            }

            printf("\n");
        }

        for(j=0; j < g->len; j++)
        {
            if(j == 0){
                printf("%4c", cl->list[i].sigla);
            }

            printf("%4d", g->arr[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void imprimeAdjCidades(Grafo *g, CidadeList *cl)
{
	int i, j;
	for(i=0; i < g->len; i++)
	{
		for(j=0; j < g->len; j++)
		{
			if(retornaAresta(i, j, g) == 0)
				continue;
            
            Cidade *c1 = &cl->list[i];
            Cidade *c2 = &cl->list[j];

			printf(" [%s]----- %dkm -----[%s]\n", c1->nome, retornaAresta(i, j, g), c2->nome);
		}
	}
}