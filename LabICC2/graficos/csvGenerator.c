#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TO_DO 100 // mude para tamanho do vetor
#define MARKS 10  // tamanho das marcas para media

void insertion_sort(int vetor[], int size)
{
    int i, j, key;
    for (i = 1; i < size; i++)
    {
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key)
        {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = key;
    }
}

void bubble_sort(int *vetor)
{
    int i, aux, troca;
    while (troca == 1)
    {
        troca = 0;
        for (i = 0; i <= TO_DO; i++)
        {
            if (vetor[i] > vetor[i + 1])
            {
                troca = 1;
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
            }
        }
    }
    /* int i, j, tmp;

    for (i = 1; i < TO_DO; i++) {

        for (j = 0; j < TO_DO - i; j++) {

            if (vetor[j] > vetor[j + 1]) {
                tmp          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = tmp;
            }
        }
    } */
}

void intercala(int p, int q, int r, int v[])
{
    int *w;                            //  1
    w = malloc((r - p) * sizeof(int)); //  2
    int i = p, j = q;                  //  3
    int k = 0;                         //  4

    while (i < q && j < r)
    { //  5
        if (v[i] <= v[j])
            w[k++] = v[i++]; //  6
        else
            w[k++] = v[j++]; //  7
    }                        //  8
    while (i < q)
        w[k++] = v[i++]; //  9
    while (j < r)
        w[k++] = v[j++]; // 10
    for (i = p; i < r; ++i)
        v[i] = w[i - p]; // 11
    free(w);             // 12
}
void mergesort(int p, int r, int v[])
{
    if (p < r - 1)
    {                          // 1
        int q = (p + r) / 2;   // 2
        mergesort(p, q, v);    // 3
        mergesort(q, r, v);    // 4
        intercala(p, q, r, v); // 5
    }
}

void rev_intercala(int p, int q, int r, int v[])
{
    int *w;                            //  1
    w = malloc((r - p) * sizeof(int)); //  2
    int i = p, j = q;                  //  3
    int k = 0;                         //  4

    while (i < q && j < r)
    { //  5
        if (v[i] >= v[j])
            w[k++] = v[i++]; //  6
        else
            w[k++] = v[j++]; //  7
    }                        //  8
    while (i < q)
        w[k++] = v[i++]; //  9
    while (j < r)
        w[k++] = v[j++]; // 10
    for (i = p; i < r; ++i)
        v[i] = w[i - p]; // 11
    free(w);             // 12
}
void rev_mergesort(int p, int r, int v[])
{
    if (p < r - 1)
    {                              // 1
        int q = (p + r) / 2;       // 2
        rev_mergesort(p, q, v);    // 3
        rev_mergesort(q, r, v);    // 4
        rev_intercala(p, q, r, v); // 5
    }
}

void swap(int *vetor, int i, int j)
{
    int temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}
int select_pivo(int *vetor, int inicio, int fim)
{
    swap(vetor, (inicio + fim + (fim - inicio) / 2 + inicio) / 3, fim);
    return vetor[fim];
}
void quickSort(int *vetor, int inicio, int fim)
{
    // condicao de parada
    if (fim - inicio <= 0)
    {
        return;
    }
    int pivo = select_pivo(vetor, inicio, fim);
    int i = inicio - 1;
    int j;

    // separa vetor entre menores ou iguais e maiores
    for (j = inicio; j <= fim - 1; j++)
    {
        if (vetor[j] <= pivo)
        {
            i = i + 1;
            swap(vetor, i, j);
        }
    }
    // i indica o ultimo dos menores ou iguais, +1 tornao ultimos dos maiores
    i++;
    int middle = i;
    // percorre os menores ou iguais separando entre menores e iguais
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

    quickSort(vetor, inicio, equals_start - 1);
    quickSort(vetor, middle + 1, fim);
    return;
}

void heapifyMax(int *vetor, int pai, int tamanho)
{
    int filho = pai * 2;

    if (filho > tamanho)
        return;

    if (vetor[filho] > vetor[pai] || (filho + 1 <= tamanho && vetor[filho + 1] > vetor[pai]))
    {
        if (filho + 1 <= tamanho && vetor[filho + 1] > vetor[filho])
            filho = filho + 1;

        int aux = vetor[pai];
        vetor[pai] = vetor[filho];
        vetor[filho] = aux;

        heapifyMax(vetor, filho, tamanho);
    }
}
void heapsort(int *vetor, int tamanho)
{
    int ultimoPai = (int)tamanho / 2.0;
    int i;
    for (i = ultimoPai; i >= 1; i--)
        heapifyMax(vetor, i, tamanho);

    // processo de ordena��o
    while (tamanho >= 2)
    {
        // seleciona maior
        int maior = vetor[1];
        vetor[1] = vetor[tamanho];
        vetor[tamanho] = maior;

        tamanho--;
        heapifyMax(vetor, 1, tamanho);
    }
}

typedef struct
{
    int key;
    int value;
    // outros atributos
} Record;
typedef struct node
{
    Record elem;
    struct node *next;
} Node;
typedef struct bucket
{
    Node *begin;
    Node *end;
} Bucket;
void bucketSort(Record *vetor, int tamanho)
{
    // 1) Percorrer as chaves e verificar o m�nimo e m�ximo
    int max, min;
    max = min = vetor[0].key;
    int i = 0;
    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i].key > max)
            max = vetor[i].key;
        if (vetor[i].key < min)
            min = vetor[i].key;
    }

    // 2) Cria��o de um vetor adicional de listas (buckets)
    Bucket *B = (Bucket *)calloc(max - min + 1, sizeof(Bucket));

    // 3) Percorrer o vetor e preencher os buckets de acordo com as chaves
    for (i = 0; i < tamanho; i++)
    {
        int posicaoKey = vetor[i].key - min;

        // criando novo n�
        Node *novo = malloc(sizeof(Node));
        novo->elem = vetor[i];
        novo->next = NULL;

        // inserindo na fila
        if (B[posicaoKey].begin == NULL)
            B[posicaoKey].begin = novo;
        else
            (B[posicaoKey].end)->next = novo;
        B[posicaoKey].end = novo;
    }

    // 4) Posicionar os elementos no vetor original, retirando elementos da lista
    int j = 0;
    for (i = 0; i <= (max - min); i++)
    {
        Node *posicao;
        posicao = B[i].begin;
        while (posicao != NULL)
        {
            vetor[j] = posicao->elem;
            j++;

            Node *deletar = posicao;
            posicao = posicao->next;
            B[i].begin = posicao;
            free(deletar);
        }
    }
    free(B);
}
void rev_bucketSort(Record *vetor, int tamanho)
{
    // 1) Percorrer as chaves e verificar o m�nimo e m�ximo
    int max, min;
    max = min = vetor[0].key;
    int i = 0;
    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i].key > max)
            max = vetor[i].key;
        if (vetor[i].key < min)
            min = vetor[i].key;
    }

    // 2) Cria��o de um vetor adicional de listas (buckets)
    Bucket *B = (Bucket *)calloc(max - min + 1, sizeof(Bucket));

    // 3) Percorrer o vetor e preencher os buckets de acordo com as chaves
    for (i = 0; i < tamanho; i++)
    {
        int posicaoKey = vetor[i].key - min;

        // criando novo n�
        Node *novo = malloc(sizeof(Node));
        novo->elem = vetor[i];
        novo->next = NULL;

        // inserindo na fila
        if (B[posicaoKey].begin == NULL)
            B[posicaoKey].begin = novo;
        else
            (B[posicaoKey].end)->next = novo;
        B[posicaoKey].end = novo;
    }

    // 4) Posicionar os elementos no vetor original, retirando elementos da lista
    int j = 0;
    for (i = (max - min) - 1; i >= 0; i--)
    {
        Node *posicao;
        posicao = B[i].begin;
        while (posicao != NULL)
        {
            vetor[j] = posicao->elem;
            j++;

            Node *deletar = posicao;
            posicao = posicao->next;
            B[i].begin = posicao;
            free(deletar);
        }
    }
    free(B);
}

void countingSort(int *vetor, int tamanho)
{
    int max, min, j = 0;
    max = min = vetor[0];
    int i = 0;
    for (i = 1; i < tamanho; i++)
    {
        if (vetor[i] > max)
            max = vetor[i];
        if (vetor[i] < min)
            min = vetor[i];
    }

    int *vetorCounting = calloc((max - min + 1), sizeof(int));

    for (i = 1; i < tamanho; i++)
    {
        vetorCounting[vetor[i] - min]++;
    }

    for (i = 0; i < max - min + 1; i++)
    {
        while (vetorCounting[i] != 0)
        {
            vetor[j] = i;
            vetorCounting[i]--;
            j++;
        }
        
    }
    free(vetorCounting);
}

int main(int argc, char const *argv[])
{
    int geracaoVetor = atoi(argv[1]);
    int tamanhoVetor = atoi(argv[2]);
    clock_t start, end;
    double times[MARKS];
    int *to_order = malloc(tamanhoVetor * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < MARKS; i++)
    {
        for (int j = 0; j < tamanhoVetor; j++)
        {
            if (geracaoVetor == 0) // aleat�rio
                to_order[j] = rand() % 1000;
            else if (geracaoVetor == 1) // ordenado
                to_order[j] = i;
            else if (geracaoVetor == 2) // invertido
                to_order[j] = tamanhoVetor - i;
            else if (geracaoVetor == 3 && j <= tamanhoVetor / 2) // primeira metade ordenada e o restante aleat�rio
                to_order[j] = j;
            else if (geracaoVetor == 3) // primeira metade ordenada e o restante aleat�rio
                to_order[j] = (rand() % 1000) + i;
        }
        start = clock();
        // mergesort(0, TO_DO, to_order);
        //  bubble_sort(to_order);
        //  insertion_sort(to_order, TO_DO);

        // quickSort(to_order, 0, TO_DO);
        // heapsort(to_order, TO_DO);

        // bucketSort(to_order, tamanhoVetor);
        countingSort(to_order, tamanhoVetor);
        end = clock();
        times[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;

        /* for (int j = 0; j < TO_DO; j++)
        {
            printf("%d ", to_order[j]);
        }
        printf("\n"); */
    }

    FILE *file = fopen("counting_best.csv", "a");

    for (int i = 0; i < MARKS; i++)
    {
        fprintf(file, "%d,%.6f\n", tamanhoVetor, (double)times[i]);
    }

    fclose(file);

    return 0;
}
