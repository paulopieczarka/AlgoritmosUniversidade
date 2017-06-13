#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

typedef struct _Node
{
    int value;
    int cost;
    struct _Node *next;
} Node;

typedef struct
{
    int length;
    Node *adj[MAX];
} Grafo;

// Scopes.
int isNodeNull(Node *n);
Node* createNode(int value, int peso);
void retiraAresta(int v1, int v2, Grafo *g);
void insereAresta(int v1, int v2, int peso, Grafo *g);

void geraGrafoVazio(Grafo *g, int n)
{
    if(n >= 50){
        printf("Too much... n should be less than %d.\n", MAX);
        return;
    }

    // Set graph length.
    g->length = n;

    int i;
    for(i=0; i < g->length; i++){
        g->adj[i] = NULL;
    }
}

void geraGrafoRand(Grafo *g, int n, int pMax)
{
    srand(time(NULL));

    int size = rand()%n + 2;
    geraGrafoVazio(g, size);

    int i, p, v1, v2;
    for(i=0; i < 10; i++)
    {
        p = rand()%pMax + 1;
        v1 = rand()%g->length;
        v2 = rand()%g->length;

        insereAresta(v1, v2, p, g);
    }
}

void insereVertice(Grafo *g)
{
    g->adj[g->length] = NULL;
    g->length++;
}

void removeVertice(int v, Grafo *g)
{
    int i;
    for(i=0; i < g->length; i++){
        retiraAresta(i, v, g);
    }

    for(i=v; i < g->length-1; i++){
        g->adj[i] = g->adj[i+1];
    }

    g->length--;
}

void insereAresta(int v1, int v2, int peso, Grafo *g)
{
    if(v1 >= g->length){
        printf("Too much... v1 should be less than %d.\n", g->length);
        return;
    }
    
    if(v2 >= g->length){
        printf("Too much... v2 should be less than %d.\n", g->length);
        return;
    }

    Node *newAdj = createNode(v2, peso);
    
    if(g->adj[v1] == NULL)
    {
        g->adj[v1] = newAdj;
    }
    else
    {
        Node *node = g->adj[v1];
        while(node->next != NULL){
            node = node->next;
        }

        node->next = createNode(v2, peso);
    }
}

void imprimeGrafo(Grafo *g)
{
    int i;
    for(i=0; i < g->length; i++){
        printf(" - [%2d] => ", i);
        if(g->adj[i] != NULL)
        {
            Node *node = g->adj[i];
            while(node != NULL)
            {
                printf("[%d, %d] => ", node->value, node->cost);
                node = node->next;
            }
        }

        printf("NULL\n");
    }

    printf("\n");
}

void retiraAresta(int v1, int v2, Grafo *g)
{
    Node *node = g->adj[v1];
    if(node == NULL){
        return;
    }

    if(node->value == v2){
        g->adj[v1] = node->next;
    }

    while(node->next != NULL)
    {
        if(node->next->value == v2){
            node->next = node->next->next;
            break;
        }

        node = node->next;
    }
}

int retornaAresta(int v1, int v2, Grafo *g)
{
    Node *node = g->adj[v1];
    while(node != NULL)
    {
        if(node->value == v2){
            return node->cost;
        }
    }

    return 0;
}

int retiraMin(Grafo *g)
{
    Node *node;
    int maxValue = -1;
    int maxCost = -1;
    int maxIndex = -1;

    for(int i=0; i < g->length; i++)
    {
        node = g->adj[i];
        if(node == NULL){
            continue;
        }

        if(maxIndex == -1){
            maxValue = node->value;
            maxCost = node->cost;
            maxIndex = i;
        }

        while(node != NULL)
        {
            if(node->cost < maxCost)
            {
                maxCost = node->cost;
                maxIndex = i;    
            }

            node = node->next;
        }
    }

    if(maxIndex == -1){
        return -1;
    }

    retiraAresta(maxIndex, maxValue, g);
    return maxCost;
}

int retiraMax(Grafo *g)
{
    Node *node;
    int maxValue = -1;
    int maxCost = -1;
    int maxIndex = -1;

    for(int i=0; i < g->length; i++)
    {
        node = g->adj[i];
        if(node == NULL){
            continue;
        }

        if(maxIndex == -1){
            maxValue = node->value;
            maxCost = node->cost;
            maxIndex = i;
        }

        while(node != NULL)
        {
            if(node->cost > maxCost)
            {
                maxCost = node->cost;
                maxIndex = i;    
            }

            node = node->next;
        }
    }

    if(maxIndex == -1){
        return -1;
    }

    retiraAresta(maxIndex, maxValue, g);
    return maxCost;
}

Node* createNode(int value, int peso)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->cost = peso;
    newNode->next = NULL;

    return newNode;
}