#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TO_DO 10000 //mude para tamanho do vetor
#define MARKS 20 //tamanho das marcas para media

void insertion_sort(int vetor[], int size){
    int i, j, key;
    for (i = 1; i < size; i++) {
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = key;
    }
}

void bubble_sort (int *vetor) {
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

void intercala (int p, int q, int r, int v[]) 
{
   int *w;                                 //  1
   w = malloc ((r-p) * sizeof (int));      //  2
   int i = p, j = q;                       //  3
   int k = 0;                              //  4

   while (i < q && j < r) {                //  5
      if (v[i] <= v[j])  w[k++] = v[i++];  //  6
      else  w[k++] = v[j++];               //  7
   }                                       //  8
   while (i < q)  w[k++] = v[i++];         //  9
   while (j < r)  w[k++] = v[j++];         // 10
   for (i = p; i < r; ++i)  v[i] = w[i-p]; // 11
   free (w);                               // 12
}

void mergesort (int p, int r, int v[])
{
   if (p < r-1) {                 // 1
      int q = (p + r)/2;          // 2
      mergesort (p, q, v);        // 3
      mergesort (q, r, v);        // 4
      intercala (p, q, r, v);     // 5
   }
}

void rev_intercala (int p, int q, int r, int v[]) 
{
   int *w;                                 //  1
   w = malloc ((r-p) * sizeof (int));      //  2
   int i = p, j = q;                       //  3
   int k = 0;                              //  4

   while (i < q && j < r) {                //  5
      if (v[i] >= v[j])  w[k++] = v[i++];  //  6
      else  w[k++] = v[j++];               //  7
   }                                       //  8
   while (i < q)  w[k++] = v[i++];         //  9
   while (j < r)  w[k++] = v[j++];         // 10
   for (i = p; i < r; ++i)  v[i] = w[i-p]; // 11
   free (w);                               // 12
}

void rev_mergesort (int p, int r, int v[])
{
   if (p < r-1) {                 // 1
      int q = (p + r)/2;          // 2
      rev_mergesort (p, q, v);        // 3
      rev_mergesort (q, r, v);        // 4
      rev_intercala (p, q, r, v);     // 5
   }
}

int main(int argc, char const *argv[])
{
    clock_t start, end;
    double times[MARKS];
    int to_order[TO_DO];
    srand(time(NULL));

    
    for (int i = 0; i < MARKS; i++)
    {
        //printf("marca:%d\n", i);
        for (int j = 0; j < TO_DO; j++)
        {
            to_order[j] = rand();
            //printf("%d ", to_order[j]);
        }
        //printf("\n");

        mergesort(0, TO_DO, to_order);

    /*     for (int j = 0; j < TO_DO; j++)
        {
            printf("%d ", to_order[j]);
        }
        printf("\n"); */

        start = clock();
        //mergesort(0, TO_DO, to_order);
        //bubble_sort(to_order);
        insertion_sort(to_order, TO_DO);
        end = clock();
        times[i] = ((double)end - (double)start) / CLOCKS_PER_SEC; 


        /* for (int j = 0; j < TO_DO; j++)
        {
            printf("%d ", to_order[j]);
        }
        printf("\n"); */
    }
    
    FILE *file = fopen("insertion_best.csv", "a");

    for (int i = 0; i < MARKS; i++)
    {
        fprintf(file, "%d,%.6f,%c\n", TO_DO, (double)times[i], 'w');
    }

    fclose(file);

    return 0;
}
