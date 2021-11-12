#include <stdio.h>
#include <stdlib.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 *
 * Otimização do quick sort que recebe um tamanho de vetor (n), um metodo de escolha do pivo(1/2), e os seus n valores
 * 1 - escolha com base na mediana de tres
 * 2 - sorteio de pivo aleatorio
 * o algoritmo ainda aplica o insertion sort a partir de vetores abaixo de 10 numeros e agrupa numeros iguais para 
 * evitar trocas desnecessarias
 */

void insertionSort(int arr[], int start, int end)
{
	int i, j, key;
	for (i = start; i <= end; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

// função auxiliar para realizar as trocas de elementos
void swap(int *vetor, int i, int j)
{
	int temp = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = temp;
}

//funcao para a selecao do pivo
int METHOD;
int select_pivo(int *vetor, int inicio, int fim)
{
	// mediana
	if (METHOD == 1)
	{
		swap(vetor, (inicio + fim + (fim - inicio) / 2 + inicio)/3, fim);
		return vetor[fim];
	}
	// aleatorio
	srand(42);

	int ramdom = rand() % (fim - inicio) / 2;
	swap(vetor, ramdom + inicio, fim);
	return vetor[fim];
}

void quicksort(int *vetor, int inicio, int fim)
{
	//condicao de parada / insertion
	if (fim - inicio <= 10)
	{
		insertionSort(vetor, inicio, fim);
		return;
	}
	int pivo = select_pivo(vetor, inicio, fim) ;
	int i = inicio - 1;
	int j;

	//separa vetor entre menores ou iguais e maiores
	for (j = inicio; j <= fim - 1; j++)
	{
		if (vetor[j] <= pivo)
		{
			i = i + 1;
			swap(vetor, i, j);
		}
	}
	//i indica o ultimo dos menores ou iguais, +1 tornao ultimos dos maiores
	i++;
	int middle = i;
	//percorre os menores ou iguais separando entre menores e iguais
	for (j = inicio; j < i; j++)
	{
		if (vetor[j] == pivo)
		{
			i = i - 1;
			if (j < fim)
			{
				swap(vetor, i, j);
			}
			
		}
	}
	// i terminara na posicao 
	int equals_start = i;
	// colocando o pivo na primeira posicao dos maiores
	swap(vetor, middle, fim);

	quicksort(vetor, inicio, equals_start -1);
	quicksort(vetor, middle +1, fim);
	return;
}

int main(int argc, char const *argv[])
{
	long int size;

	scanf("%li", &size);
	scanf(" %d", &METHOD);
	int *vetor = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		scanf(" %d", &vetor[i]);
	}

	quicksort(vetor, 0, size - 1);

	for (int i = 0; i < size; i++)
	{
		printf("%i\n", vetor[i]);
	}

	free(vetor);
	return 0;
}
