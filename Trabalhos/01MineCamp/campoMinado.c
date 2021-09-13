#include <stdio.h>
#include <stdlib.h>

/*
 * Victor Rodrigues da Silva        n:12566140
 * 
 * jogo de campo minado, o campo deve estar em arquivo separado e tem 3 comandos
 * 1 mostra o tabuleiro
 * 2 preenche as dicas e mostra o tabuleiro
 * 3 recebe coordenadas e mostra o tabuleiro em mascara ou real dependendo do conteudo
 * do ponto escolhido
*/

struct point
{
    int X;
    int Y;
};

//leitura de strings stdin
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

//leitura de matriz char em arquivo
struct point size;
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
        if (line[i] == '\n')
        {
            line[i] = '\0';
        }
        //para escrita e preciso que tenha \n
        if (eofReader == EOF)
        {
            line[i] = '\0';
            size.Y = 1;
        }
        else
        {
            size.X = i;
        }
        i++;
    } while (line[i - 1] != '\0');

    return line;
}

//substitui o valor '.' pelo valor de uma bomba ao lado
void addHint(char **board, int y, int x)
{
    int tmp;
    if (board[y][x] == '.')
    {
        board[y][x] = '1';
    }
    else if (board[y][x] != '*')
    {
        tmp = (int)board[y][x];
        tmp++;
        board[y][x] = (char)tmp;
    }
}

//recebe uma mina e adiciona 1 a todos os '.' ao redor
void fillHints(char **board, struct point mine)
{
    //printf("\nmina:%d %d\n", mine.Y, mine.X);
    if (mine.Y - 1 >= 0)
    {
        if (mine.X - 1 >= 0)
        {
            //printf("sou A e mandei encher %d %d", mine.Y - 1, mine.X - 1);
            addHint(board, mine.Y - 1, mine.X - 1);
        }
        if (mine.X + 1 < size.X)
        {
            //printf("sou B e mandei encher %d %d", mine.Y - 1, mine.X + 1);
            addHint(board, mine.Y - 1, mine.X + 1);
        }
        //printf("sou C e mandei encher %d %d", mine.Y - 1, mine.X);
        addHint(board, mine.Y - 1, mine.X);
    }
    if (mine.Y + 1 < size.Y)
    {
        if (mine.X - 1 >= 0)
        {
            //printf("sou D e mandei encher %d %d", mine.Y + 1, mine.X - 1);
            addHint(board, mine.Y + 1, mine.X - 1);
        }
        if (mine.X + 1 < size.X)
        {
            //printf("sou E e mandei encher %d %d", mine.Y + 1, mine.X + 1);
            addHint(board, mine.Y + 1, mine.X + 1);
        }
        //printf("sou F e mandei encher %d %d", mine.Y + 1, mine.X);
        addHint(board, mine.Y + 1, mine.X);
    }
    if (mine.X - 1 >= 0)
    {
        //printf("sou G e mandei encher %d %d", mine.Y, mine.X - 1);
        addHint(board, mine.Y, mine.X - 1);
    }
    if (mine.X + 1 < size.X)
    {
        //printf("sou H e mandei encher %d %d", mine.Y, mine.X + 1);
        addHint(board, mine.Y, mine.X + 1);
    }
}

//copia os valores do campo com dicas para a matriz com mascara, 
//contanto que estejam vizinhos a um ponto perto de onde foi criado
void reveal(char **board, struct point current, char **mask)
{
    //printf("%d %d\n", size.Y, size.X);
    mask[current.Y][current.X] = board[current.Y][current.X];
    if (board[current.Y][current.X] == '.')
    {
        if (current.Y - 1 >= 0)
        {
            current.Y--;
            if (current.X - 1 >= 0 && mask[current.Y][current.X - 1] == 'X')
            {
                current.X--;
                reveal(board, current, mask);
                current.X++;
            }
            if (current.X + 1 < size.X && mask[current.Y][current.X + 1] == 'X')
            {
                current.X++;
                reveal(board, current, mask);
                current.X--;
            }
            if (mask[current.Y][current.X] == 'X')
            {
                reveal(board, current, mask);
            }
            current.Y++;
        }
        if (current.Y + 1 < size.Y-1)
        {
            current.Y++;
            if (current.X - 1 >= 0 && mask[current.Y][current.X - 1] == 'X')
            {
                current.X--;
                reveal(board, current, mask);
                current.X++;
            }
            if (current.X + 1 < size.X && mask[current.Y][current.X + 1] == 'X')
            {
                current.X++;
                reveal(board, current, mask);
                current.X--;
            }
            if (mask[current.Y][current.X] == 'X')
            {
            reveal(board, current, mask);
            }
            current.Y--;
        }
        if (current.X - 1 >= 0 && mask[current.Y][current.X - 1] == 'X')
            {
                current.X--;
                reveal(board, current, mask);
                current.X++;
            }
            if (current.X + 1 < size.X && mask[current.Y][current.X + 1] == 'X')
            {
                current.X++;
                reveal(board, current, mask);
                current.X--;
            }


        /*if (current.X - 1 >= 0 && mask[current.Y][current.X - 1] == 'X')
        {
            current.X--;
            reveal(board, current, mask);
            current.X++;
        }
        if (current.X + 1 < size.X && mask[current.Y][current.X + 1] == 'X')
        {
            current.X++;
            reveal(board, current, mask);
            current.X--;
        }

        if (current.Y + 1 < size.Y - 1 && mask[current.Y + 1][current.X] == 'X')
        {
            //printf("%d, %d\n",current.Y + 1, size.Y);
            current.Y++;
            reveal(board, current, mask);
            current.Y--;
        }*/
    }
}

//cria uma mascara de mesmas dimesoes do campo e preenche com X
char **fillMaskBoard()
{
    int i, j;
    char **mask = malloc(size.Y * sizeof(char *));
    for (i = 0; i < size.Y; i++)
    {
        mask[i] = malloc((size.X + 1) * sizeof(char));
        for (j = 0; j < size.X; j++)
        {
            mask[i][j] = 'X';
            if (j == size.X)
            {
                mask[i][j] = '\0';
            }
        }
        //printf("%d\n", i);
    }

    return mask;
}

//mostra um campo ou mascara
void showBoard(char **board)
{
    int i, j;
    for (i = 0; i < size.Y - 1; i++)
    {
        for (j = 0; j < size.X; j++)
        {
            printf("%c", board[i][j]);
        }
        if (i < size.Y - 2)
        {
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    int i = 0, j = 0, operator= 0;
    char **board = malloc(sizeof(char *));
    char *fileName, **maskBoard;
    struct point mine, selected;
    scanf("%d", &operator);
    getchar();
    fileName = read_line();
    FILE *read = fopen(fileName, "r");
    if (read == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(0);
    }
    do
    {
        board = realloc(board, (i + 1) * sizeof(char *));
        board[i] = readFileLine(read);
        i++;
    } while (size.Y != 1);
    size.Y = i;
    fclose(read);

    switch (operator)
    {
    case 1:
        showBoard(board);
        break;

    case 2:
        for (i = 0; i < size.Y - 1; i++)
        {
            for (j = 0; j < size.X; j++)
            {
                if (board[i][j] == '*')
                {
                    mine.X = j;
                    mine.Y = i;
                    fillHints(board, mine);
                }
            }
        }
        showBoard(board);
        break;

    case 3:
        for (i = 0; i < size.Y - 1; i++)
        {
            for (j = 0; j < size.X; j++)
            {
                if (board[i][j] == '*')
                {
                    mine.X = j;
                    mine.Y = i;
                    fillHints(board, mine);
                }
            }
        }
        scanf("%d %d", &selected.Y, &selected.X);
        //printf("%d %d %c", size.Y, size.X, board[selected.Y][selected.X]);
        switch (board[selected.Y][selected.X])
        {
        case '*':
            showBoard(board);
            break;

        case '.':
            maskBoard = fillMaskBoard();
            reveal(board, selected, maskBoard);
            showBoard(maskBoard);
            for (i = 0; i < size.Y - 1; i++)
            {
                free(maskBoard[i]);
            }
            free(maskBoard);
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':

            maskBoard = fillMaskBoard();
            maskBoard[selected.Y][selected.X] = board[selected.Y][selected.X];
            showBoard(maskBoard);
            for (i = 0; i < size.Y - 1; i++)
            {
                free(maskBoard[i]);
            }
            free(maskBoard);
            break;
        default:
            break;
        }

        break;

    default:
        break;
    }

    for (i = 0; i < size.Y; i++)
    {
        free(board[i]);
    }
    free(board);
    free(fileName);

    return 0;
}
