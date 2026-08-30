#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#define MAT_SIZE 200
#define PERFORATION_RATE 3

int data1[MAT_SIZE][MAT_SIZE];
int data2[MAT_SIZE][MAT_SIZE];
int dataSend[MAT_SIZE][MAT_SIZE];

void clean_matrix()
{
    for (int i = 0; i < MAT_SIZE; i++)
        for (int j = 0; j < MAT_SIZE; j++)
            dataSend[i][j] = 0;
}

void mul_mat_norm()
{
    for (int i = 0; i < MAT_SIZE; i++)
        for (int j = 0; j < MAT_SIZE; j++)
        {
            dataSend[i][j] = 0;
            for (int k = 0; k < MAT_SIZE; k++)
                dataSend[i][j] += data1[i][k] * data2[k][j];
        }
}

void mul_mat_mod()
{
    for (int i = 0; i < MAT_SIZE; i++)
        for (int j = 0; j < MAT_SIZE; j += PERFORATION_RATE)
        {
            dataSend[i][j] = 0;
            for (int k = 0; k < MAT_SIZE; k++)
                dataSend[i][j] += data1[i][k] * data2[k][j];
        }
}

void mul_mat_trunc()
{
    for (int i = 0; i < MAT_SIZE - PERFORATION_RATE; i++)
        for (int j = 0; j < MAT_SIZE - PERFORATION_RATE; j++)
        {
            dataSend[i][j] = 0;
            for (int k = 0; k < MAT_SIZE; k++)
                dataSend[i][j] += data1[i][k] * data2[k][j];
        }
}

int main()
{
    stdio_init_all();
    sleep_ms(3000);

    srand(30);
    for (int i = 0; i < MAT_SIZE; i++)
        for (int j = 0; j < MAT_SIZE; j++)
        {
            data1[i][j] = rand() % 300;
            data2[i][j] = rand() % 300;
        }

    clean_matrix();

    // ── Escolha a técnica descomentando uma linha ──
    // printf("INICIO_NORMAL\n");
    // mul_mat_norm();
    // printf("INICIO_MODULAR\n");
    // mul_mat_mod();
    printf("INICIO_TRUNCATION\n");
    mul_mat_trunc();

    for (int i = 0; i < MAT_SIZE; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            printf("%d", dataSend[i][j]);
            if (j < MAT_SIZE - 1)
                printf(";");
        }
        printf("\n");
    }

    printf("FIM\n");
    while (true)
        tight_loop_contents();
}