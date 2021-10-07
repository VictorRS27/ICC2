#include <stdio.h>
#include <stdlib.h>

typedef struct shell
{
    char color[15];
    char texture[15];
    double diameter;
} shell_t;

int main(int argc, char const *argv[])
{
    int total_shell, i, j, distance;
    scanf("%d", &total_shell);
    getchar();

    shell_t tmp, *shells = (shell_t *)malloc(total_shell * sizeof(shell_t));
    for (i = 0; i < total_shell; i++)
    {
        scanf(" %lf %s %s", &shells[i].diameter, shells[i].color, shells[i].texture);
    }

    distance = total_shell / 2;
    while (distance >= 1)
    {

        for (i = distance; i < total_shell; i++)
        {
            tmp = shells[i];
            j = i;
            while (j >= distance && tmp.diameter < shells[j - distance].diameter)
            {
                shells[j] = shells[j - distance];
                j = j - distance;
            }
            shells[j] = tmp;
        }
        distance = distance/2;
    }

    for (i = 0; i < total_shell; i++)
    {
        printf("%.3lf %s %s\n", shells[i].diameter, shells[i].color, shells[i].texture);
    }

    free(shells);
    return 0;
}