#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 * tabela hash feita por amor a programacao :) 
 */

#define P 1000000007

int eofReader;
char *read_word()
{
    int i = -1;
    char *line = malloc(sizeof(char));
    do
    {
        i++;
        eofReader = getchar();
        line[i] = eofReader;
        if (i == 0 && (line[i] == '\n' || line[i] == '\r'))
        {
            line[i] = getchar();
        }

        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r' || eofReader == EOF)
        {
            line[i] = '\0';
        }
        else
        {
            line = realloc(line, (i + 2) * sizeof(char));
        }
    } while (line[i] != '\0' && eofReader != EOF);
    return line;
}


typedef struct node node_t;
struct node
{
    char *word;
    node_t *next;
};


int hash_size;
int found_hash(char *word)
{
    long int hash_value = 0, j = 0;
    while (word[j] != '\0')
    {
        hash_value += word[j] * pow(263, j);
        hash_value = hash_value % P;
        j++;
    }
    return hash_value = hash_value % hash_size;
}

int add(node_t **lists)
{
    char *word;
    int hash_value = 0;
    node_t *k;
    word = read_word();
    hash_value = found_hash(word);
    k = lists[hash_value]->next;
    //percorre os encadeamentos
    while (k != NULL)
    {
        //cancela a acao se o valor ja existir
        if (strcmp(word, k->word) == 0)
        {
            return 0;
        }
        k = k->next;
    }
    node_t *new_value = malloc(sizeof(node_t *));
    new_value->word = word;
    new_value->next = lists[hash_value]->next;
    lists[hash_value]->next = new_value;
    return 1;
}

int del(node_t **lists)
{
    char *word;
    node_t *k, *tmp;
    word = read_word();
    int hash_value = found_hash(word);
    k = lists[hash_value];
    //percorre os encadeamentos
    while (k->next != NULL)
    {
        //elimina a palavra ao encontra-la
        if (strcmp(word, k->next->word) == 0)
        {
            tmp = k->next;
            k->next = k->next->next;
            free(tmp);
            return 1;
        }

        k = k->next;
    }
    return 0;
}

int check(node_t **lists)
{
    char *word;
    node_t *k;
    word = read_word();
    k = lists[found_hash(word)]->next;
    //percorre os encadeamentos
    while (k != NULL)
    {
        //retorna se encontrar o valor
        if (strcmp(word, k->word) == 0)
        {
            return 1;
        }

        k = k->next;
    }
    return 0;
}

void get(int to_show, node_t **lists)
{
    node_t *k;
    k = lists[to_show]->next;
    //percorre os encadeamentos
    while (k != NULL)
    {
        printf("%s ", k->word);
        k = k->next;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    char *operator;
    int total_ops, tmp;
    scanf(" %d", &hash_size);
    getchar();

    //criacao e inicializacao do vetor da tabela
    node_t *k, **lists = (node_t **)malloc(hash_size * sizeof(node_t *));
    for (int i = 0; i < hash_size; i++)
    {
        lists[i] = malloc(sizeof(node_t));
        lists[i]->next = NULL;
        lists[i]->word = NULL;
    }
    
    scanf(" %d", &total_ops);
    getchar();
    for (int i = 0; i < total_ops; i++)
    {
        operator= read_word();

        if (strcmp(operator, "add") == 0)
        {
            add(lists);
        }
        else if (strcmp(operator, "del") == 0)
        {
            del(lists);
        }
        else if (strcmp(operator, "check") == 0)
        {
            if (check(lists))
            {
                printf("sim\n");
            }
            else
            {
                printf("não\n");
            }
        }
        else if (strcmp(operator, "get") == 0)
        {
            scanf(" %d", &tmp);
            getchar();
            get(tmp, lists);
        }
    }

    for (int i = 0; i < hash_size; i++)
    {
        k = lists[i]->next;
        while (k != NULL)
        {
            free(k->word);
            k = k->next;
        }
        free(lists[i]);
    }
    
    free(lists);
    return 0;
}
