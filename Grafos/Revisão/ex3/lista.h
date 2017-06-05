
typedef struct
{
	char *nome;
	int idade;
	int genero;
} Pessoa;

typedef struct Node Node;

struct Node
{
	Pessoa value;
	struct Node *next;
};

Node list_new(Pessoa *p)
{
	Node *node;
	node->value = *p;
	node->next = NULL;

	return *node;
}

void list_push(Node *n, Pessoa *p)
{
	Node *node;
	node->value = *p;
	node->next = n;
}