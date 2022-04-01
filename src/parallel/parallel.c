#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "parallel.h"

//#define COUNT_PROCESS 10

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

void work_procces(const int* const array_procces, int* sum_numbers_for_procces, int K, int I, int start_position, int finish_position, int number_procces)
{
    int sum_number = 0;
    for(int k; k < K; k++)
    {
        for(int i = 0;i < I;i++)
        {
            if(k+10 * i >= start_position && k+10 * i <= finish_position)
            {
                sum_number = sum_number + array_procces[k+10 * i];
            }
        }
        sum_numbers_for_procces[number_procces * K + k] = sum_number;
        sum_number = 0;
    }
}

int* count_numbers(const int* const array_of_numbers, const int array_size, int K, int I)
{
    int count_thread = sysconf(_SC_NPROCESSORS_ONLN);
    int pids[count_thread];
    int* sum_numbers_for_procces = (int*) malloc(count_thread*K * sizeof(int));
    int* parallel_sum_numbers = (int*) malloc(K * sizeof(int));

    int len_array_for_process = array_size / count_thread;
    int remainder = array_size % count_thread;
    int start_position = 0;
    int finish_position = 0;

    for (int i = 0; i < count_thread; ++i)
    {        
        pids[i] = fork();
        if (pids[i] == -1) 
        {
            printf("fork failed\n");
            return NULL;
        }
        if (pids[i] == 0) 
        {
            if(i < count_thread - 1)
            {
                start_position = i * len_array_for_process;
                finish_position = (i + 1) * len_array_for_process - 1; 
            }
            if(i == count_thread - 1)
            {
                start_position = i * len_array_for_process;
                finish_position = (i + 1) * len_array_for_process - 1 + remainder; 
            }
            work_procces(array_of_numbers, sum_numbers_for_procces, K, I, start_position, finish_position, i);
            exit(0);
        }
    } 
    //start_position = 0;
    //finish_position = len_array_for_process - 1;
    //work_procces(array_of_numbers, sum_numbers_for_procces, K, I, start_position, finish_position, 0);
    for (size_t i = 0; i < count_thread-1; ++i) {
    int status = 0;
    waitpid(-1, &status, WUNTRACED);
    }

    int sum_numbers_for_k = 0;
    for(int i; i < K; i++)
    {
        for(int j; j < count_thread; j++)
        {
            sum_numbers_for_k = sum_numbers_for_k + *(sum_numbers_for_procces + j * K + i);
        }
        parallel_sum_numbers[i] = sum_numbers_for_k;
        sum_numbers_for_k = 0;
    }
    free(sum_numbers_for_procces);
    return parallel_sum_numbers;
}
