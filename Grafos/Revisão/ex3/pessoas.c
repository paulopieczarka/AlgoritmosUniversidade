#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
	//system("clear");
	printf("Hello, World!\n\n");

	Pessoa *p1 = new_pessoa("Paulo", 22, 0);
	Pessoa *p2 = new_pessoa("Marcos", 16, 0);
	Pessoa *p3 = new_pessoa("Allan", 25, 0);
	Pessoa *p4 = new_pessoa("Maria", 18, 1);
	Pessoa *p5 = new_pessoa("Janaine", 35, 1);
	Pessoa *p6 = new_pessoa("Amanda", 14, 1);

	Node root = list_new(p1);
	list_push(&root, p2);

	return 0;
}

Pessoa new_pessoa(char *nome, int idade, int genero)
{
	Pessoa *p;
	p->nome = nome;
	p->idade = idade;
	p->genero = genero;

	return &p;
}