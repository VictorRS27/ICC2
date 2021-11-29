#include <stdio.h>
#include <stdlib.h>
#include "ordered_list.h"

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 * Escalonador de processos, organizado por prioridade e a cada rotacao muda o comeco a cada rotacao
 */

//estrutura de um processo 
typedef struct
{
    int id, start_time, total_quantums, priority;
} Process_t;

//estruturas para lista circular
typedef struct cicle_node
{
    Process_t *value;
    struct cicle_node *next, *prev;
} cicle_node_t;

typedef struct cicle_list
{
    cicle_node_t *reference;
    int size, max_id;
} cicle_list_t;

cicle_list_t *cicle_create()
{
    cicle_list_t *l;
    l = (cicle_list_t *)malloc(sizeof(cicle_list_t));

    l->reference = NULL;
    l->size = 0;
    l->max_id = 0;
}

int cicle_insert(cicle_list_t *l, void *x)
{
    cicle_node_t *j, *i = (cicle_node_t *)malloc(sizeof(cicle_node_t));
    i->value = x;
    l->max_id = (l->max_id > i->value->id) ? l->max_id : i->value->id;
    int same_name_found = 0, k;

    //insercao
    if (l->size == 0)
    {
        l->reference = i;
        l->reference->prev = i;
        l->reference->next = i;
    }
    else if (l->size == 1)
    {
        l->reference->next = i;
        l->reference->prev = i;
        i->next = l->reference;
        i->prev = l->reference;
    }
    else //numeros maiores que 2
    {
        j = l->reference;
        k = l->size;

        //acha o primeiro valor de igual prioridade
        while (j->value->priority > i->value->priority && k != 0)
        {
            if (i->value->id == j->value->id)
            {
                same_name_found = 1;
            }

            j = j->next;
            k--;
        }
        //percorre as iguais prioridades achando um valor com mais quantums a executar;
        while (j->value->priority == i->value->priority && k != 0 && j->value->total_quantums <= i->value->total_quantums)
        {
            if (i->value->id == j->value->id)
            {
                same_name_found = 1;
            }

            j = j->next;
            k--;
        }
        //insere o valor no local encontardo
        j->prev->next = i;
        i->prev = j->prev;
        j->prev = i;
        i->next = j;

        // termina a sequencia, dessa vez so procurando por valor igual de id
        while (k!= 0)
        {
            if (i->value->id == j->value->id)
            {
                same_name_found = 1;
            }
            j = j->next;
            k--;
        }
        
        //corrige ids iguais com base no id maximo salvo na lista
        if (same_name_found)
        {
            i->value->id = l->max_id+1;
        }
    }

    //reposiciona a referecia da lista circular caso o valor deva ter sido colocado antes do 
    //primeiro elemento (antiga referencia)
    if (i->value->priority > l->reference->value->priority)
    {
        l->reference = i;
    }
    if (i->value->priority == l->reference->value->priority && l->reference->value->total_quantums > i->value->total_quantums)
    {
        l->reference = i;
    }

    l->size++;
}


int main(int argc, char const *argv[])
{
    list_t *to_execute;
    Process_t *new_process;

    to_execute = create();
    //leitura de processos e armazenamento ordenado
    while (1)
    {
        new_process = malloc(sizeof(Process_t));
        if (scanf(" %d %d %d %d", &new_process->id, &new_process->start_time, &new_process->total_quantums, &new_process->priority) != 4)
            break;
        getchar(); //\r
        getchar(); //\n
        insert(to_execute, new_process->start_time, (void *)new_process);
        //printf("%d %d %d %d\n", new_process->id, new_process->start_time, new_process->total_quantums, new_process->priority);
    }

    int quantums = 1, k = 0;
    Process_t *found_new_process;
    cicle_list_t *robin = cicle_create();
    cicle_node_t *i, *tmp, *fake_reference;

    // criacao da lista circular adicionando os valores dos processos iniciados com 1 quantum
    found_new_process = lremove_by_elem(to_execute, quantums);
    while (found_new_process != NULL)
    {
        //printf("%d %d %d %d\n", found_new_process->id, found_new_process->start_time, found_new_process->total_quantums, found_new_process->priority);
        cicle_insert(robin, found_new_process);
        found_new_process = (Process_t *)lremove_by_elem(to_execute, quantums);
    }


    /* i = robin->reference;
    k = robin->size;
    while (k!= 0)
    {
        printf("%d %d %d %d\n", i->value->id, i->value->start_time, i->value->total_quantums, i->value->priority);
        k--;
        i = i->next;
    } */
    
    //rotacao do round robin
    i = robin->reference; 
    while (robin->size != 0)
    {
        //rotacao da lista
        while (k < robin->size)
        {
            //reduz o valor de quantums restantes e verifica se algum rocesso chegou ao fim
            i->value->total_quantums--;
            if (i->value->total_quantums <= 0)
            {
                //saida e remocao da lista circular
                printf("%d %d\n", i->value->id, quantums);
                if (robin->size > 1)
                {
                    if (i == robin->reference)
                    {
                        robin->reference = robin->reference->next;
                    }
                    tmp = i->prev;
                    i->prev->next = i->next;
                    i->next->prev = i->prev;
                    free(i->value);
                    free(i);
                    i = tmp;
                    
                }
                else
                {
                    free(i->value);
                    free(i);
                    free(robin);
                    destroy(to_execute);
                    return 0;
                }

                robin->size--;
            }
            i = i->next;

            //soma 1 quantum e verfica se algum processo deve iniciar nesse momento
            quantums++;
            found_new_process = lremove_by_elem(to_execute, quantums);
            while (found_new_process != NULL)
            {
                //printf("    %d %d %d %d\n", found_new_process->id, found_new_process->start_time, found_new_process->total_quantums, found_new_process->priority);
                cicle_insert(robin, found_new_process);
                // printf("%d\n", robin->reference->value->id);
                if (found_new_process->priority > i->value->priority)
                {
                    i = robin->reference;
                }
                
                found_new_process = NULL;
                found_new_process = (Process_t *)lremove_by_elem(to_execute, quantums);
            }
        }
        i = i->next;
    }


    return 0;
}
