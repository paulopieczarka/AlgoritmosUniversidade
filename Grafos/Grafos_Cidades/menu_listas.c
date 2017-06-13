#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

void menuGeraBranco(Grafo *g);
void menuGeraRandom(Grafo *g);
void menuInsereAresta(Grafo *g);
void menuRemoveVertice(Grafo *g);
void menuRemoveAresta(Grafo *g);

void menu(Grafo *g)
{
    system("clear");
    imprimeGrafo(g);

    printf(" [1] GERA BRANCO.\t[2] GERA RANDOM.\n");
    printf(" [3] INSERE VERTICE.\t[4] INSERE ARESTA.\n");
    printf(" [5] REMOVE VERTICE.\t[6] REMOVE ARESTA.\n");
    printf(" [7] REMOVE MIN.\t[8] REMOVE MAX.\t[9] MOSTRA ADJS.\n\n");
    printf(" [0] TALVEZ FINALIZE O PROCESSO.\n\n");

    int cmd = 10;
    printf(" Happy cmd: ");
    scanf("%d", &cmd);

    if(cmd == 1){
        menuGeraBranco(g);
    }
    else if(cmd == 2){
        geraGrafoRand(g, 5, 10);
    }
    else if(cmd == 3){
        insereVertice(g);
    }
    else if(cmd == 4){
        menuInsereAresta(g);
    }
    else if(cmd == 5){
        menuRemoveVertice(g);
    }
    else if(cmd == 6){
        menuRemoveAresta(g);
    }
    else if(cmd == 7){
        retiraMin(g);
    }
    else if(cmd == 8){
        retiraMax(g);
    }

    if(cmd != 0){
        menu(g);
    }

    printf("\n ... I already miss YOU!\n\n");
}

void menuGeraBranco(Grafo *g)
{
    int n = 0;
    printf(" Numero vertices: ");
    scanf("%d", &n);

    geraGrafoVazio(g, n);
}

void menuInsereAresta(Grafo *g)
{
    int v1, v2, p;
    printf(" v1: "); scanf("%d", &v1);
    printf(" v2: "); scanf("%d", &v2);
    printf(" peso: "); scanf("%d", &p);

    insereAresta(v1, v2, p, g);
}

void menuRemoveVertice(Grafo *g)
{
    int v = 0;
    printf(" Remover qual vertice? ");
    scanf("%d", &v);

    removeVertice(v, g);
}

void menuRemoveAresta(Grafo *g)
{
    int v1, v2;
    printf(" v1: "); scanf("%d", &v1);
    printf(" v2: "); scanf("%d", &v2);

    retiraAresta(v1, v2, g);
}

void startListaMenu()
{
    Grafo g;
    menu(&g);
}