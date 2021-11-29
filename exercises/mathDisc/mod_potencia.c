#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 *
 * Calcula a^e(mod d) onde a = argv[1] < d = argv[2], e e = argv[3]
 * Primiro de forma economica, mantando o valor em mod "d" a cada multplicacao da potencia
 * Depois a mesma conta com forca bruta, fazendo a potencia e arriscando overflow (comentada);
 */

int main(int argc, char const *argv[])
{
    // recebimento e atribuição de valores
    int a = atoi(argv[1]), e = atoi(argv[2]), d = atoi(argv[3]);
    int i = e, exit = 1;

    // para garantir que "a" esteja em mod "d"
    a = a % d;

    while (i > 0)
    {
        // calcula o valor da primeira multiplicacao da potencia e converte a mod "d"
        exit = (exit * a) % d;
        //printf("resultado parcial elevado a %d: %d\n", i, exit);
        i--;
    }

    printf("\n\n  %u∧%u (mod %u) =%u\n\n", a, e, d, exit);

/* O problma resulvido a forca bruta 
    exit = pow(10, 15);

    printf("o resultado bruto é %d (mod %d) = %d\n", exit, d, exit % d); */

    return 0;
}
