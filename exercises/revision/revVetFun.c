#include <stdio.h>
#include <stdlib.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 * 
 * 
 * Programa para ler um vetor e exibir cada elemento diferente, na ordem digitada, com as repeticoes
 * ao lado entre parenteses
*/

//Conta quantas vezes o keyValue se repete no vetor
int repeatCounter(int vetor[], int keyValue, int size)
{
    int i, repeats = 0;
    for (i = 0; i < size; i++)
    {
        if (vetor[i] == keyValue)
        {
            repeats++;
        }
    }
    return repeats;
}

//Verifica se um numero da atual casa do vetor ja foi exibido na tela antes
int noRepeatsVerifier(int currentHouse, int vetor[])
{
    int i;
    for (i = currentHouse-1; i >= 0; i--)
    {
        if (vetor[i] == vetor[currentHouse])
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int i = -1, end, vetor[100] = {0}, size;

    //le o vetor e atribui quanto dele foi usado
    do
    {
        i++;
        end = scanf(" %i", &vetor[i]);
    } while (end == 1);
    size = i;

    // percorre o vetor exibindo os valores diferentes e printando seu numero de repeticoes
    for (i = 0; i < size; i++)
    {
        if (!(noRepeatsVerifier(i, vetor)))
        {
            printf("%i (%i)\n", vetor[i], repeatCounter(vetor, vetor[i], size));
        }
    }

    return 0;
}
