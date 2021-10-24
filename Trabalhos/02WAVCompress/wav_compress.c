#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

/* 
 * Victor R.  No: 12566140
 *
 * compressor de arquivos de audio por meio da transformada discreta de fourier
*/

//funcao dada + alteracoes que le dados de um arquivo de audio e salva em um vetor
unsigned char *read_wav_data(char *fname, int *size/* , unsigned char *file_header[] */)
{
    FILE *fp = fopen(fname, "rb");
    unsigned char buf4[4];

    //fread(file_header, sizeof(char), 44, fp);
    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1] << 8 | buf4[2] << 16 | buf4[3] << 24;

    unsigned char *data = malloc(sizeof(*data) * (dataSize));

    int i = 0;
    while (i < dataSize)
    {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    *size = dataSize;
    return data;
}

//escreve os dados num arquivo de audio
/* int write_wav_data(int size, unsigned char *file_header, unsigned char *audio)
{
    
    FILE *fp = fopen("saida.wav", "wb");
    fwrite(file_header, sizeof(char), 44, fp);
    fwrite(file_header, sizeof(char), size, fp);

    return 1;
} */

//funcao dada + alteracoes da transformada discreta de forrier
double complex *DFT(unsigned char *audio, int length, int *coefs_zero) {
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k] += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        // printf("%.1lf + %.1lfi\n", creal(coef[k]), cimag(coef[k]));
        if ((creal(coef[k])<=0.0) && (cimag(coef[k])<=0.0))
        {
            *coefs_zero += 1;
        }
        
    }
    return coef;
}

//inversa da transformada discreta de fourier
double complex *inverse_DFT(double complex *dft, int length) {
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[n] += dft[k] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }

        
    }
    return coef;
}

void insertion_sort(double *vec, int size)
{
    int i, change = 1;
    double tmp;

    while (change == 1)
    {
        change = 0;
        for (i = 0; i < size - 1; i++)
        {
            if (vec[i] < vec[i+1])
            {
                change = 1;
                tmp = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = tmp;
            } 
        }
    }
}

//calcula o vetor magnitude e o ordena
double *magnitude_counter(double complex *dft, int size)
{
    double *magnitudes = calloc(size, sizeof(double));
    int i;
    for ( i = 0; i < size; i++)
    {
        magnitudes[i] = sqrt(pow(creal(dft[i]), 2) + pow(cimag(dft[i]), 2));
    }
    insertion_sort(magnitudes, size);
    return magnitudes;
}

//le linha de texto
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

int main(int argc, char const *argv[])
{
    unsigned char *audio/* , file_header[44] */;
    double complex *tdf;
    char *file_name;
    int size, to_compress, coefs_to_show=0, i;
    double *magnitudes, magnitude;

    //leitura e atribuicoes
    file_name = read_line();
    scanf(" %d", &to_compress);
    audio = read_wav_data(file_name, &size/*,  &file_header */);
    tdf = DFT(audio, size, &coefs_to_show);
    magnitudes = magnitude_counter(tdf, size);

    //comprime o arquivo eliminando ondas inuteis
    for (i = 0; i < size; i++)
    {
        magnitude = sqrt(pow(creal(tdf[i]), 2) + cimag(tdf[i]));
        if (magnitudes[to_compress] > magnitude)
        {
            audio[i] = 0;
        }
        
    }

    //saida para o que eh pedido
    printf("%i\n%i\n", size, coefs_to_show);
    for ( i = 0; i < to_compress; i++)
    {
        printf("%i\n", (int)magnitudes[i]);
    }

    //criando o audio descompactado
    /* tdf = inverse_DFT(tdf, size);
    for ( i = 0; i < size; i++)
    {
        audio[i] = creal(tdf[i]);
    }
    write_wav_data(size, *file_hearder, audio); */
    
    //liberacao de alocacao
    free(file_name);
    free(audio);
    free(tdf);
    free(magnitudes);
    
    return 0;
}
