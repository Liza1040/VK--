#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"

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