#include <stdio.h>
#include <stdlib.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 *
 * Programa monta uma quad-tree baseado na igualdade de valores de uma matriz
 */

//estrutura de uma arvore
typedef struct tree
{
    int value;
    void **next_branchs;
} tree_t;

//grupamento com intervalos x e y
struct interval
{
    int start_x, start_y, end_x, end_y;
};

//compara se todos os itens 
int compare_itens(int **matriz, struct interval partial_size)
{
    if (partial_size.start_x == partial_size.end_x || partial_size.start_y == partial_size.end_y)
    {
        return matriz[partial_size.start_y][partial_size.start_x];
    }
    int i, j, to_compare = matriz[partial_size.start_y][partial_size.start_x];

    for (i = partial_size.start_y; i < partial_size.end_y; i++)
    {
        for (j = partial_size.start_x; j < partial_size.end_x; j++)
        {
            if (to_compare != matriz[i][j])
            {
                return -1;
            }
        }
    }
    return to_compare;
}

//funcao recursiva que constroi a arvore
tree_t *tree_build(int **matriz, struct interval partial_size)
{
    tree_t *branch = malloc(sizeof(tree_t));
    branch->next_branchs = malloc(4 * sizeof(tree_t *));

    //trata para caso a submatriz seja igual
    int flag;
    flag = compare_itens(matriz, partial_size);
    if (flag != -1)
    {
        branch->value = flag;
        branch->next_branchs[0] = NULL;
        branch->next_branchs[1] = NULL;
        branch->next_branchs[2] = NULL;
        branch->next_branchs[3] = NULL;
        return branch;
    }

    //trata para se for diferente, quebrando em mais 4 pedacos
    branch->value = -1;
    int i, j, branch_counter = 0, diference = (partial_size.end_x - partial_size.start_x) / 2;
    for (i = 0; i < 2; i++)
    {
        partial_size.start_y += diference * i;
        partial_size.end_y = partial_size.start_y + diference;
        for (j = 0; j < 2; j++)
        {
            partial_size.start_x += diference * j;
            partial_size.end_x = partial_size.start_x + diference;


            branch->next_branchs[branch_counter] = tree_build(matriz, partial_size);
            branch_counter++;
        }
        partial_size.start_x -= diference ;
        partial_size.end_x -= diference ;

    }
    return branch;
}

//mostra os elementos da arvore 
void print(tree_t *branch)
{
    printf("%i ", branch->value);
    int i;
    for (i = 0; i < 4; i++)
    {
        if (branch->next_branchs[i] != NULL)
        {
            print(branch->next_branchs[i]);
        }
    }
}

//livra o espaco alocado pela arvore
void destroy(tree_t *branch)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (branch->next_branchs[i] != NULL)
        {
            destroy(branch->next_branchs[i]);
        }
    }
    free(branch);
}

int main(int argc, char const *argv[])
{
    struct interval size;
    int **matriz, i, j;
    tree_t *trunk;

    //atribuicoes
    size.start_x = 0;
    size.start_y = 0;
    scanf("%i %i", &size.end_x, &size.end_y);
    matriz = calloc(size.end_y, sizeof(int *));
    for (i = 0; i < size.end_y; i++)
    {
        matriz[i] = calloc(size.end_x, sizeof(int));
        for (j = 0; j < size.end_x; j++)
        {
            scanf(" %i", &matriz[i][j]);
        }
    }

    //processamento
    trunk = tree_build(matriz, size);
    print(trunk);

    //desalocacao
    destroy(trunk);
    for (i = 0; i < size.end_y; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
