#include <stdio.h>
#include <stdlib.h>

/*
 * Victor Rodrigues da Silva  No 12566140
 * 
 * 
 * Programa que le labirinto de pessoas pedindo ajuda e escapa
*/

//struct para tamanho e coordenadas
struct plan
{
    int X;
    int Y;
};

//leitura de strings
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

//leitura de linha char em arquivo
char *readFileLine(FILE *leitura)
{
    int i = 0, eofReader;
    char *line = malloc(sizeof(char));
    do
    {
        eofReader = fgetc(leitura);
        line[i] = eofReader;
        line = realloc(line, (i + 2) * sizeof(char));
        //posiciona /0 para escrita da imagem com a mascara %s
        if (line[i] == '\n' || eofReader == EOF)
        {
            line[i + 1] = '\0';
        }
        //para escrita e preciso que tenha \n
        if (eofReader == -1)
        {
            line[i] = '\n';
        }

        i++;
    } while (line[i - 1] != '\n' && line[i - 1] != '\r');
    return line;
}

//funcao recursiva para caaminhar no mapa
struct plan size;
int walk(char **map, struct plan position)
{
    int flag=0;
    map[position.Y][position.X] = '*';
    map[position.Y][position.X] = '*';
    if (position.Y - 1 < 0 || position.X + 1 >= size.X || position.Y + 1 >= size.Y || position.X - 1 < 0)
    {
        return 1;
    }
    
    if (map[position.Y - 1][position.X] == '.')
    {
        position.Y--;
        flag = walk(map, position);
        position.Y++;
    }
    if (flag == 0 && map[position.Y][position.X + 1] == '.')
    {
        position.X++;
        flag = walk(map, position);
        position.X--;

    }
    if (flag == 0  && map[position.Y + 1][position.X] == '.')
    {
        position.Y++;
        flag = walk(map, position);
        position.Y--;
    }
    if (flag == 0  && map[position.Y][position.X - 1] == '.')
    {
        position.X--;
        flag = walk(map, position);
        position.X++;
    }
    return flag;
}

//conta quantas vezes um caracter se repete numa matriz
int characterCounter(char **text, char value)
{
    int i, j, total=0;
    for ( i = 0; i < size.Y; i++)
    {
        for ( j = 0; j < size.X; j++)
        {
            if (text[i][j]==value)
            {
                total++;
            }
        }
    }
    return total;
}
int main(int argc, char const *argv[])
{
    int i = 0, enemies, paths, steps;
    double exploration;
    struct plan startPosition;
    //leitura do arquivo
    char *fileName = read_line();
    FILE *read = fopen(fileName, "r");
    if (read == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(0);
    }
    //leitura do dados no arquivo
    fscanf(read, "%d %d\n", &size.Y, &size.X);
    fscanf(read, "%d %d\n", &startPosition.Y, &startPosition.X);
    char **labrinth = malloc(size.Y * sizeof(char *));
    for (i = 0; i < size.Y; i++)
    {
        labrinth[i] = readFileLine(read);
    }
    fclose(read);

    //processamento
    enemies = characterCounter(labrinth, '#');
    paths = characterCounter(labrinth, '.');
    walk(labrinth, startPosition);
    steps = characterCounter(labrinth, '*');
    exploration = 100 * steps / paths;

    //saida
    for (i = 0; i < size.Y; i++)
    {
        printf("%s", labrinth[i]);
    }
    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", enemies);
    printf("----Numero total de caminhos validos:   %d\n", paths);
    printf("----Numero total de caminhos visitados: %d\n", steps);
    printf("----Exploracao total do labirinto: %.1lf%%", exploration);

    //liberando a matriz dinamica
    for ( i = 0; i < size.Y; i++)
    {
        free(labrinth[i]);
    }
    free(labrinth);
    
    return 0;
}
