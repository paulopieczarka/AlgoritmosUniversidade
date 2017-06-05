#include <stdio.h>
#include <stdlib.h>

void vizinhos(int size, int[][size], int, int);

int main()
{
	srand(21);
	system("clear");

	int size = 0;
	printf(" Digite o tamanho da matriz:  ");
	scanf("%d", &size);
	printf("\n");

	int i, j, mat[size][size];
	for(i=0; i < size; i++)
	{
		for(j=0; j < size; j++)
		{
			mat[i][j] = rand()%2;
			printf(" %d ", mat[i][j]);
		}

		printf("\n");
	}

	int x = 0, y = 0;
	printf("\n Vizinhos de?  ");
	scanf("%d %d", &x, &y);

	vizinhos(size, *(&mat), x, y);

	printf("\n\n");
	printf(" Hello, World!\n\n");
	return 0;
}

void vizinhos(int size, int arr[][size], int x, int y)
{
	printf("\n Buscando em %d, %d.\n\n Adjacentes verdadeiros: ", x, y);

	int i, j;
	for(i=-1; i <= 1; i++)
	{
		for(j=-1; j <= 1; j++)
		{
			int _i = x+i;
			int _j = y+j;

			if(_i < 0 || _i >= size || _j < 0 || _j >= size){
				continue;
			}

			if(arr[_i][_j] != 1 || (x == _i && y == _j)){
				continue;
			}

			printf("[%d,%d] ", _i, _j);
		}
	}

	printf("\n\n OK!\n");
}