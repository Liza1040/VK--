#include <stdio.h>
#include <stdlib.h>
#include "naive.h"

int* read_array_from_file(FILE *file, const int array_size)
{
    int n = 0;
    int* array_of_numbers = (int*) malloc(array_size*sizeof(int));
    for(int i=0;i<array_size;i++)
    {
        if(n = fscanf(file, "%d",&array_of_numbers[i]) != 1)
        {
            printf("Некорректные числа или количество чисел\n");
            free(array_of_numbers);
            return NULL;
        }
    }
    return array_of_numbers;
}

int* count_numbers(const int* const array_of_numbers, const int array_size, int K, int I)
{
    int sum_number = 0;
    int* naive_sum_numbers = (int*) malloc(K*sizeof(int));
    for (int k = 0; k < K; k++)
    {
        for(int i = 0;i < I;i++)
        {
            if(k+10 * i > array_size)
            {
                printf("Выход за границу массива!\n");
                free(naive_sum_numbers);
                return NULL;
            }
            sum_number = sum_number + array_of_numbers[k+10 * i];
        }
        naive_sum_numbers[k] = sum_number;
        sum_number = 0;
    }
    return naive_sum_numbers;
}