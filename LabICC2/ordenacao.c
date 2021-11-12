#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimeVetor(int* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++){
			printf("%i ", vetor[i]);
		}
	}
	printf("\n");
}

int* insertionSort(int* vetor, int tamanho){
	int j;
	for(j = 1; j < tamanho; j++){//o elemento na posição 0 não precisa analisar
		int chave = vetor[j]; //variável auxiliar, temporária para armazenar o valor do momento
		int i = j - 1; //armazenar a posição de análise do momento
		while (i >= 0 && vetor[i] > chave){//final do vetor ; valor do vetor é maior que a chave de análise
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = chave;
	}
	
	return vetor;
}

void intercala(int* vetor, int inicio, int centro, int fim){
	//intercalação
	int* vetorAux = (int*)malloc(sizeof(int) * (fim-inicio)+1);

	int i = inicio;	// indice da primeira lista ordenada
	int j = centro+1; //indice da segunda lista ordenada
	int k = 0; //indice do vetor auxiliar

	//compara e intercala os elementos do menor para o maior
	while(i <= centro && j <= fim){
		
		if (vetor[i] <= vetor[j]){ //verifica qual é o elemento menor entre as duas listas
			vetorAux[k] = vetor[i];
			i++; //proximo elemento da primeira metade
		}
		else{
			vetorAux[k] = vetor[j];
			j++; //proximo elemento da segunda metade
		}
		k++;
	}

	while(i <= centro){//há elementos na primeira metade ainda?
		vetorAux[k] = vetor[i];
		i++;
		k++;
	}

	while(j <= fim){//há elementos na segunda metade ainda?
		vetorAux[k] = vetor[j];
		j++;
		k++;
	}

	//atualizando o vetor original com o vetor auxiliar
	for(i = inicio, k = 0; i <= fim; i++,k++)
		vetor[i] = vetorAux[k];
	free(vetorAux);
}


void mergeSort(int* vetor, int inicio, int fim){
	//caso base
	if (fim <= inicio) return; //falso durante o processo de divisão; 
	//verdadeiro quando o processo de divisão não pode ser mais executado!!! --> possibilita a intercalação

	//processo de divisão
	int centro = (int)((inicio+fim)/2.0);
	mergeSort(vetor, inicio, centro);
	mergeSort(vetor, centro+1, fim);

	//processo de conquista
	intercala(vetor, inicio, centro, fim);
}

int* bubbleSort(int* vetor, int tamanho){
	int i, j;
	for(i = 0; i < tamanho-1; i++){
		for(j = 0; j < tamanho-1-i; j++){
			if (vetor[j] > vetor[j+1]){
				int aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;		
			}
		}
	}
	
	return vetor;
}

void quickSort(int* vetor, int inicio, int fim);

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//geração dos elementos
	int *vetorInsertion = malloc(tamanhoVetor * sizeof(int));
	int *vetorMerge = malloc(tamanhoVetor * sizeof(int));
	int *vetorBubble = malloc(tamanhoVetor * sizeof(int));
	int *vetorQuick = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetorInsertion[i] = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetorInsertion[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetorInsertion[i] = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetorInsertion[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetorInsertion[i] = (rand() % 1000) + i;
		vetorMerge[i] = vetorInsertion[i];
		vetorBubble[i] = vetorInsertion[i];
		vetorQuick[i] = vetorInsertion[i];
	}
	
	printf("Insertion Gerado: ");
	imprimeVetor(vetorInsertion, tamanhoVetor);
	inicio = clock();
	vetorInsertion = insertionSort(vetorInsertion, tamanhoVetor);
	final = clock();
	printf("Insertion Ordenado: ");
	imprimeVetor(vetorInsertion, tamanhoVetor);
	printf("Tempo de ordenacao Insertion: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorInsertion);

	printf("Merge Gerado: ");
	imprimeVetor(vetorMerge, tamanhoVetor);
	inicio = clock();
	mergeSort(vetorMerge, 0, tamanhoVetor-1);
	final = clock();
	printf("Merge Ordenado: "); 
	imprimeVetor(vetorMerge, tamanhoVetor);
	printf("Tempo de ordenacao Merge: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorMerge);

	printf("Bubble Gerado: ");
	imprimeVetor(vetorBubble, tamanhoVetor);
	inicio = clock();
	bubbleSort(vetorBubble, tamanhoVetor);
	final = clock();
	printf("Bubble Ordenado: "); 
	imprimeVetor(vetorBubble, tamanhoVetor);
	printf("Tempo de ordenacao Bubble: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorBubble);

	printf("Quick Gerado: ");
	imprimeVetor(vetorQuick, tamanhoVetor);
	inicio = clock();
	quickSort(vetorQuick, 0, tamanhoVetor-1);
	final = clock();
	printf("Quick Ordenado: "); 
	imprimeVetor(vetorQuick, tamanhoVetor);
	printf("Tempo de ordenacao Quick: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorQuick);
	
	return 0;	
}

/*
	A ideia é ordenar os elementos considerando um pivô, em que os elementos à sua esquerda são menores que
	este pivô e os elementos à direita são maiores. Assim, temos duas sub-listas, uma à esquerda (controlada por i)
	e outra à direita (controlada por j).

	Exemplo: i aumenta; j diminui
	[6 7 8 0 3 4 1] -> pivo = 6, p=0, i=1 e j=6 (7<=6? [i=1]) (1>6? [j=6]) (j>i? troca)
	[  1         7] -> pivo = 6, p=0, i=1 e j=6 (1<=6? 8<=6? [i=2]) (7>6? 4>6? [j=5]) (j>i? troca)
	[  1 4     8 7] -> pivo = 6, p=0, i=2 e j=5 (4<=6? 0<=6? 3<=6? 8<=6? [i=5]) (8>6? 3>6? [j=4]) (j>i? troca)
	[  1 4 0 3 8 7] -> pivo = 6, p=0, i=5 e j=4
	[3 1 4 0 6 8 7] -> os elementos em p e j são trocados, fazendo com que o pivô esteja em sua posição final
	[        6    ] -> vetor já ordenado
	-> recursão de [3 1 4 0]
	-> recursão de [8 7]

	[3 1 4 0] -> pivo = 3, p=0, i=1 e j=3
	[  1 0 4] -> pivo = 3, p=0, i=2 e j=3
	[  1 0 4] -> pivo = 3, p=0, i=3 e j=2
	[0 1 3 4] -> os elementos em p e j são trocados, fazendo com que o pivô esteja em sua posição final
	[* * 3 * 6 * *] -> vetor já ordenado
	-> recursão de [0 1]
	-> recursão de [4]

	[0 1] -> pivo = 0, p=0, i=1 e j=1
	[0 1] -> pivo = 0, p=0, i=2 e j=1
	[0 * 3 * 6 * *] -> vetor já ordenado
	-> recursão de [1]

	[0 1 3 * 6 * *] -> vetor já ordenado
	[0 1 3 4 6 * *] -> vetor já ordenado

	[8 7] -> pivo = 0, p=0, i=1 e j=1
	[7 8] -> pivo = 0, p=0, i=2 e j=1
	[0 1 3 4 6 * 8] -> vetor já ordenado
	-> recursão de [7]

	[0 1 3 4 6 7 8] -> vetor já ordenado
*/

void quickSort(int* vetor, int inicio, int fim){
	//imprimeVetor(vetor, 15);
	//printf("Pivo: %i, fim %i\n", vetor[inicio], vetor[fim]);

	//primeira etapa: verificar caso base (vetores unitários ou nulos)
	if (fim <= inicio)
		return;

	//segunda etapa: partição em relação ao pivô
	int pivo = inicio;
	int i = inicio+1; //percorre o vetor aumentando seu valor
	int j = fim;//percorre o vetor diminuindo seu valor

	//encontrando os elementos que contradizem as regras dos elementos da lista:
	//- elementos à esquerda do pivô devem ser <= a ele ou chegar ao final do vetor
	//- elementos à direita do pivô devem ser > que ele ou chegar ao início do vetor
	int aux;
	while (i <= j){//quantas vezes forem necessárias, ou seja, até que as duas listas cruzam
		while (i <= fim && vetor[i] <= vetor[pivo]) i++; 
		while (vetor[j] > vetor[pivo]) j--; //quando j==pivo, a comparação é falsa (encontrou o inicio do vetor)

		if (j > i){
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
		}
	}

	pivo = j;
	aux = vetor[pivo]; //reposicionado o pivô
	vetor[pivo] = vetor[inicio];
	vetor[inicio] = aux;

	//terceira etapa: recursão
	quickSort(vetor, inicio, pivo-1); //j é a nova posição do pivô
	quickSort(vetor, pivo+1, fim);	
}

/*
	Análise do Quick Sort (vetor ordenado e pivo como primeiro elemento):
	- primeira iteração: [0 1 2 3 4 5 6]: [] [1 2 3 4 5 6] -> 1 + f(0) + f(n-1)
	- segunda iteração: [1 2 3 4 5 6]: [] [2 3 4 5 6] -> 1 + f(n-1)
	....

	f(n) = n + f(0) + f(n-1)
		 = n + 1 + f(n-1)
		 = n + 1 + [n-1 + 1 + f(n-2)]
		 = n + 1 + [n-1 + 1 + [n-2 + 1 + f(n-3)]] = sum(n-i) + 3.1 + f(n-3)   ***sum de i=0 a i=2

		 ....
		 = sum(n-i) + k + f(n-k)   ***sum de i=0 a i=k-1

	então, quando n-k = 1 (k = n-1):
		 = sum(n-i) + n-1 + f(1)   ***sum de i=0 a i=n-1-1
		 = sum(n-i) + n-1 + 1      ***sum de i=0 a i=n-2
		 = sum(n-i) + n            ***sum de i=0 a i=n-2

	por P.A.:
		 = ((n-1).(n-2))/2 + n
		 = (n^2 + 2n - n - 2)/2 + n
		 = (n^2 + 2 - 2)/2 + n         -->O(n^2)


	Análise do Quick Sort (vetor ordenado e pivo como elemento central):
	- primeira iteração: [0 1 2 3 4 5 6]: [0 1 2] [4 5 6] -> 

	f(n) = n + f(n/2) + f(n/2)
		 = n + 2.f(n/2)
		 .....
		 = n.log(n) -> muito próximo ao MergeSort
		 
		 
	Comparativos com MergeSort:
	- MergeSort é sempre n.log(n)
	- QuickSort pode ser n^2 ou n.log(n) -> depende da escolha do pivô
	
	Qual motivo indica a escolha do Quick Sort?
	- MergeSort tem mais consumo de memória (vetor auxiliar)  
	
	....

	Exercício: desenvolver diversas metodologias diferentes para a escolha do pivô:
	- primeiro elemento
	- elemento central
	- elemento aleatório

	- testar com vetores ordenados, não ordenados, aleatórios e parcialmente ordenados

	Utilize o código disponibilizado como base para estas modificações!!!
	Leia o Capítulo 7 (Cormen)

*/
