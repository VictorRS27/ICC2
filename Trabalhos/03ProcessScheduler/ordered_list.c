#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordered_list.h"

typedef struct node
{
    void *cargo;
    elem reference;
    struct node *next;
} node_t;

struct list
{
    node_t *start, *end;
    int size;
};

list_t *create()
{
    list_t *l;
    l = (list_t *)malloc(sizeof(list_t));

    l->end = NULL;
    l->start = NULL;
    l->size = 0;
}

void destroy(list_t *l)
{
    if (l != NULL)
    {
        node_t *i = l->start;
        while (i != NULL)
        {
            l->start = i->next;
            free(i);
            i = l->start;
        }
        free(l);
    }
}

int insert(list_t *l, elem x, void *y)
{
    node_t *prev, *j, *i = (node_t *)malloc(sizeof(node_t));

    if (l == NULL || i == NULL)
        return 0;

    i->reference = x;
    i->cargo = y;
    //printf("%p %p\n", i->cargo, y);

    if (l->start == NULL)
    {
        l->start = i;
        l->end = i;
        i->next = NULL;
        //printf("coloquei o valor %d como primeiro item da lista: %d e ultimo:%d\n", i->reference, l->start->reference, l->end->reference);
        return 1;
    }
    j = l->start;
    while (j != NULL && j->reference <= x)
    {        
        prev = j;
        j = j->next;
    }
    if (j == NULL)
    {
        l->end = i;
        prev->next = i;
    }
    if (j == l->start)
    {
        l->start = i;
    }else{
        prev->next = i;
    }
    i->next = j;

    //printf("%d %d %d %d\n", j->reference, l->start->reference, l->end->reference, x);

    l->size++;
    return 1;
}

void print(list_t *l)
{
    node_t *i = l->start;
    while (i!= NULL)
    {
        printf("%d ", i->reference);
        i = i->next;
    }
}


void *lremove_by_elem(list_t *l, elem cutter)
{
    void *exit;
    node_t *i = l->start;
    node_t *prev;
    while (i != NULL)
    {
        //printf("%d\n", i->reference);
        if (i->reference == cutter)
        {
            exit = i->cargo;
            //printf("%p %p\n", i->cargo, exit);

            if (i == l->start)
            {
                l->start = l->start->next;
                free(i);
            }
            else if (i == l->end)
            {
                l->end = prev;
                l->end->next = NULL;
                free(i);
            }
            else
            {
                prev->next = i->next;
                free(i);
            }
            l->size--;
            return exit;
        }
        else
        {
            prev = i;
            i = i->next;
        }
    }
    return NULL;
}