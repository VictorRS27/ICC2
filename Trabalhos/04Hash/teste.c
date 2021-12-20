#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define P 1000000007;

typedef struct node node_t;
struct node
{
    char *word;
    node_t *next;
};

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

int hash_size;
int found_hash(char *word)
{
    long long int hash_value = 0, j = 0;
    while (word[j] != '\0')
    {
        hash_value += word[j] * pow(263, j);
        hash_value = hash_value % P;
        j++;
    }
    hash_value = hash_value % hash_size;
    return hash_value;
}



int add(char *word, node_t *lists)
{
    int hash_value = 0;
    node_t *k;
    word = read_word();
    hash_value = found_hash(word);
    k = lists[hash_value].next;
    while (k != NULL)
    {
        //printf("%p\n", k);
        if (strcmp(word, k->word) == 0)
        {
            return 0;
        }
        k = k->next;
    }
    node_t *new_value = malloc(sizeof(node_t *));
    new_value->word = word;
    new_value->next = lists[hash_value].next;
    lists[hash_value].next = new_value;
    return 1;
}

int main(int argc, char const *argv[])
{
    hash_size = 5;
    char *word ="world";

    node_t *k, lists[5];

    for (int i = 0; i < hash_size; i++)
    {
        lists[i].next = NULL;
        lists[i].word = NULL;
    }

    for (int i = 0; i < hash_size; i++)
    {        
        printf("%p ", lists[i].next);
        printf("%p\n", lists[i].word);
    }
    printf("%d\n", found_hash(word));

    printf("%d\n", add(word, lists));
    printf("%s\n", lists[found_hash(word)].next->word);

    /* free(lists); */
    return 0;
}
