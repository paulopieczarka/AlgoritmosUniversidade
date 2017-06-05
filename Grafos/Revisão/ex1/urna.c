#include <stdio.h>
#include <stdlib.h>

int main()
{
	char nomes[5][32] = {"Scorpion", "Raiden", "Subzero", "Goro", "Branco"};
	int candidatos[4] = {24666, 34555, 43444, 19333};

	int i, votos[5];
	for(i=0; i < 5; i++)
		votos[i] = 0;

	int j;
	for(j=0; j < 2; j++)
	{
		int confirma = 0;
		while(confirma != 1)
		{
			system("clear");

			int voto = 0;
			printf("Digite o NUM do seu candidato: ");
			scanf("%i", &voto);

			// Search.
			for(i=0; i <= 5; i++)
			{
				if(i == 5)
				{
					voto = 4;
				}
				else if(voto == candidatos[i])
				{
					voto = i;
					break;
				}
			}

			printf("Confirma? [0]Não [1]Sim   R: ");
			scanf("%d", &confirma);

			// Sum.
			if(confirma == 1){
				votos[voto]++;
			}
		}
	}

	system("clear");
	for(i=0; i < 5; i++)
		printf("- Candidato %s recebeu %d votos.\n", nomes[i], votos[i]);

	printf("Hello, World!\n");
	return 0;
}