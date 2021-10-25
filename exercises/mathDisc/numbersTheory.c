#include <stdio.h>
#include <stdlib.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 *
 * Calcula o numero em [a]d que seja o inverso de [argv[o]]argv[1]
 */

// funcao recursiva que retorna o mdc entre dois numeros e descobre
// i e j tal que a*i + b*j = 1;
int i = 0, j = 0, I, J;
int found_inversor(int bigger, int lower)
{
    int mdc, rest = bigger % lower;
    //mostra os passos do algoritmo de euclides
    printf("%i = %i * %i + %i\n", bigger, lower, bigger / lower, rest);
    //define o caso base como sendo o momento que o resto eh zero, ou seja, bigger eh multiplo de lower  
    if (rest == 0)
    {
        //salva o mdc para retorno e inicia o calculo de i e j
        I = 0, J = 1;
        printf("mdc = %i\n", lower);
        return lower;
    }

    mdc = found_inversor(lower, rest);

    //calcula i e j baseado nos anteriores I e J
    i = J;
    j = I - (bigger / lower) * J;
    I = i;
    J = j;
    //mostra os valores a cada etapa
    printf("\ni = %d j = %d", i, j);
    return mdc;
}

int main(int argc, char const *argv[])
{
    //entrada e processamento
    int a = atoi(argv[1]), b = atoi(argv[2]);
    found_inversor(a, b);


    //j eh o inverso pois eh o numero q multiplicado A(144) terah 1 de diferenca para um multiplo de D(169)
    //contudo nao eh exatamente o j, mas sim o conjunto em Zd a qual ele pertence, portanto, o tornamos positivo e modularizamos por D
    j < 0 ? j = (j * -1) : 1;
    j = j % b;

    //deixando a equacao assim e provando a inversao
    printf("\n\n%d * %d + %d * %d = 1", a, i, b, j);
    //saida
    printf("\n\n o inverso de %d em Z%d é %d\n", b, a, j);

    return 0;
}
