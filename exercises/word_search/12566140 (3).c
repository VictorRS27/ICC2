#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line()
{
    int i = 0, eofReader;
    char *line = malloc(sizeof(char));
    do
    {
        eofReader = getchar();
        line[i] = eofReader;
        if (line[i] == '\n' || line[i] == '\r' || eofReader == EOF)
        {
            line[i] = '\0';
        }
        else
        {
            line = realloc(line, (i + 2) * sizeof(char));
        }
        i++;
    } while (line[i - 1] != '\0' && eofReader != EOF);
    return line;
}

int eofReader;
char *readFileLine(FILE *leitura)
{
    int i = -1;
    char *line = malloc(sizeof(char));
    do
    {
        i++;
        line = realloc(line, (i + 1) * sizeof(char));
        eofReader = fgetc(leitura);
        // printf("%d", eofReader);
        line[i] = eofReader;
        // posiciona /0 para escrita da imagem com a mascara %s
        if (line[i] == '\n')
        {
            line[i] = '\0';
        }
        // para escrita e preciso que tenha \n
        if (eofReader == EOF)
        {
            line[i] = '\0';
        }

    } while (line[i] != '\n' && line[i] != '\0');
    return line;
}

typedef struct node
{
    char *word;
    struct node *next;
} node_t;

typedef struct list
{
    node_t *start;
    int size;
} list_t;

list_t *create()
{
    list_t *l;
    l = (list_t *)malloc(sizeof(list_t));

    l->start = NULL;
    l->size = 0;
    return l;
}

int insert(list_t *l, char *x)
{
    node_t *prev, *j, *i = (node_t *)malloc(sizeof(node_t));

    if (l == NULL || i == NULL)
        return 0;

    i->word = x;
    if (l->start == NULL)
    {
        l->start = i;
        i->next = NULL;
        l->size++;
        return 1;
    }
    j = l->start;
    while (j != NULL && j->word[0] < i->word[0])
    {
        prev = j;
        j = j->next;
    }
    if (j == l->start)
    {
        l->start = i;
    }
    else
    {
        prev->next = i;
    }
    i->next = j;
    
    l->size++;
    return 1;
}

typedef struct head
{
    int total_words;
    node_t *next;
} head_t;

int main(int argc, char const *argv[])
{
    head_t alphabet[26];

    for (int k = 0; k < 26; k++)
    {
        alphabet[k].total_words = 0;
    }

    list_t *words = create();
    node_t *i;
    int operator, j = 0, is_updated = 0, counter_exit_2 = 1;
    char *file_name, *word;
    while (1)
    {
        scanf(" %d", &operator);
        //printf("comando lido foi: %d\n", operator);
        if(getchar()=='\r');
        getchar();

        switch (operator)
        {
        case 1:
            //printf("leitura do nome do arquivo:\n");
            file_name = read_line();
            FILE *read = fopen(file_name, "r");
            while (eofReader != EOF)
            {
                word = readFileLine(read);
                insert(words, word);
            }

            i = words->start;
            //printf("comeco escrita teste:\n");
            while (j < 3)
            {
                printf("%s\n", i->word);
                i = i->next;
                j++;
            }
            j=0;
            //printf("\nfim escrita teste:\n");

            eofReader = 0;
            free(file_name);
            is_updated = 0;
            break;
        case 2:
            i = words->start;
            alphabet[(int)i->word[0] - 97].next = i;
            alphabet[(int)i->word[0]-97].total_words = 1;

            for (int k = words->size; k > 0; k--)            
            {
                //printf("começou a procura uma diferente a partir de %d\n", k);
                j = 1;
                //printf("%p %p\n", i, i->next);
                while (i->next != NULL && i->word[0] == i->next->word[0])
                {
                    //printf("duas letras iniciais iguais\n");
                    k--;
                    j++;
                    i = i->next;
                }
                if (i->next != NULL)
                {
                    //printf("achou que %c é menor que %c\n", i->word[0], i->next->word[0]);
                    //printf("salvou a cabeca para %c em alphabet[%d] e a quantia %d de valores com a letra anterior em %d\n", i->next->word[0], (int)i->next->word[0]-97, j, (int)i->word[0]-97);
                    alphabet[(int)i->next->word[0]-97].next = i->next;
                    alphabet[(int)i->word[0]-97].total_words = j;
                    counter_exit_2++;
                }
                else
                {
                    //printf("salvou o valor %d em alphabet[%d] como total\n", j, (int)i->word[0]-97);
                    alphabet[(int)i->word[0]-97].total_words = j;                    
                }
                i = i->next;
            }
            printf("%d\n", counter_exit_2);
            j=0;
            
            is_updated = 1;
            break;
        case 3:
        
            word = read_line();
            if (!is_updated)
            {
                printf("Vetor de indices nao atualizado.\n");
                break;
            }
            i = alphabet[word[0]-97].next;
            //printf("percorrendo %d casas procurando pela palavra %s\n", alphabet[word[0]-97].total_words, word);
            for (j = 0; j < alphabet[word[0]-97].total_words; j++)
            {
                if (strcmp(i->word, word) == 0)
                {
                    printf("%d\n", j);
                    j = alphabet[word[0]-97].total_words+1;
                    break;
                }
                i = i->next;
            }
            if (j == alphabet[word[0]-97].total_words)
            {
                printf("Palavra nao existe na lista.\n");
            }
            //printf("comparação entre %s e %s = %d",word, words->start->word, strcmp(words->start->word, word));
            
            
            break;
        default:
            // livrar
            return 0;
            break;
        }
    }

    return 0;
}
