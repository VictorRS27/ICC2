#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 *
 * Escalonador de processos, organizado por prioridade e a cada rotacao muda o comeco a cada rotacao
 */

// funcao para leitura de linha de entrada
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

// funcao para leitura de linha em arquivo
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
        line[i] = eofReader;
        if (line[i] == '\n')
        {
            line[i] = '\0';
        }
        if (eofReader == EOF)
        {
            line[i] = '\0';
        }

    } while (line[i] != '\n' && line[i] != '\0');
    return line;
}

// estruturas para lista especificamente ligada
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

void clear(list_t *l)
{
    node_t *i = l->start;
    int j = l->size;
    while (j > 0)
    {
        free(i->word);
        i = i->next;
        j--;
    }
}

void destroy(list_t *l)
{
    node_t *j, *i = l->start;
    while (l->size > 0)
    {
        j = i->next;
        free(i);
        i = j;
        l->size--;
    }
    free(l);
}

int insert(list_t *l, char *x)
{
    node_t *prev, *j, *i = (node_t *)malloc(sizeof(node_t));

    if (l == NULL || i == NULL)
        return 0;

    i->word = x;
    // caso seja o primeiro valor
    if (l->start == NULL)
    {
        l->start = i;
        i->next = NULL;
        l->size++;
        return 1;
    }
    // procura primeiro valor a ser maior ou igual
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

// estrutura para alfabeto
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
        // le o comando
        scanf(" %d", &operator);
        if (getchar() == '\r')
            ;
        getchar();

        switch (operator)
        {
        // caso 1 le palavras de arquivo e salva em lista
        case 1:
            file_name = read_line();
            FILE *read = fopen(file_name, "r");
            // le palavras e insere ate o fim de arquivo
            while (eofReader != EOF)
            {
                word = readFileLine(read);
                insert(words, word);
            }

            // escreve as 3 primeiras palavras
            j = 0;
            i = words->start;
            while (j < 3)
            {
                printf("%s\n", i->word);
                i = i->next;
                j++;
            }

            j = 0;
            eofReader = 0;
            free(file_name);
            is_updated = 0;
            break;
        //atualiza vetor de struct com pronteiro para a primeira ocorrencia de cada letra do alfabeto
        case 2:
            i = words->start;
            alphabet[(int)i->word[0] - 97].next = i;
            alphabet[(int)i->word[0] - 97].total_words = 1;

            //percorre a lista colocando os primeiros valores no vetor alfabeto
            for (int k = words->size; k > 0; k--)
            {
                j = 1;
                //armazena a extensão de valores de primeira iguais 
                while (i->next != NULL && i->word[0] == i->next->word[0])
                {
                    k--;
                    j++;
                    i = i->next;
                }
                //pega cada troca de valor de primeira letra e armazena
                if (i->next != NULL)
                {
                    alphabet[(int)i->next->word[0] - 97].next = i->next;
                    alphabet[(int)i->word[0] - 97].total_words = j;
                    counter_exit_2++;//conta quantas letras tem ponteiros não nulos
                }
                else
                {
                    alphabet[(int)i->word[0] - 97].total_words = j;
                }
                i = i->next;
            }
            //saida requerida
            printf("%d\n", counter_exit_2);
            j = 0;
            counter_exit_2 = 1;

            is_updated = 1;
            break;
        //procura palavra na lista
        case 3:
            word = read_line();
            //verifica se ta atualizado
            if (!is_updated)
            {
                printf("Vetor de indices nao atualizado.\n");
                break;
            }
            //acha a primeira letra da palavra de entrada e procura na lista ligada ao alfabeto
            i = alphabet[word[0] - 97].next;
            for (j = 0; j < alphabet[word[0] - 97].total_words; j++)
            {
                if (strcmp(i->word, word) == 0)
                {
                    printf("%d\n", j);
                    j = alphabet[word[0] - 97].total_words + 1;
                    break;
                }
                i = i->next;
            }
            if (j == alphabet[word[0] - 97].total_words)
            {
                printf("Palavra nao existe na lista.\n");
            }

            break;
        //desalocação
        default:
            clear(words);
            destroy(words);
            return 0;
            break;
        }
    }

    return 0;
}
