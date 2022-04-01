#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "parallel.h"

#define COUNT_PROCESS 10

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

int child_work(int* array_procces, int array_size_for_procces, int k, int I)
{
    int sum_number =0;
    for(int i = 0;i < I;i++)
    {
        if(k+10 * i + 1 > array_size_for_procces)
        {
            return sum_number;
        }
    // if(k+10 * i > array_size_for_procces)
    // {
    //     printf("Выход за границу массива!\n");
    //     free(naive_sum_numbers);
    //     return NULL;
    // }
        sum_number = sum_number + array_procces[k+10 * i];
    }
    return sum_number;
}

int* count_numbers(const int* const array_of_numbers, const int array_size, int K, int I)
{
    int count_thread = sysconf(_SC_NPROCESSORS_ONLN);
    printf("%d\n",count_thread);
    int pids[count_thread];
    int* parallel_sum_numbers = (int*) malloc(K*sizeof(int));
    //for (size_t i = 0; i < count_thread; ++i)
    int i;
    printf("%ld\n",sysconf(_SC_STREAM_MAX));
    while(sysconf(_SC_NPROCESSORS_ONLN) < count_thread)
    {        printf("Time to fork\n");

        pids[i] = fork();
        i++;
                printf("Hello world\n");
                
        int len_array_for_process = array_size / count_thread;
        int remainder = array_size % count_thread;
        int* array_procces = (int*) malloc(len_array_for_process + remainder);
        int array_size_for_procces;

        if (pids[i] == -1) 
        {
            printf("fork failed\n");
            return NULL;
        }
        else if (pids[i] == 0) 
        {
            if(i < count_thread - 1)
            {
                array_procces = memcpy(array_procces,array_of_numbers + len_array_for_process, len_array_for_process);
                array_size_for_procces = len_array_for_process;
            }
            else if(i == count_thread - 1)
            {
                array_procces = memcpy(array_procces,array_of_numbers + len_array_for_process, len_array_for_process + remainder);
                array_size_for_procces = len_array_for_process + remainder;
            }
            for(int k = 0; k < K; k++)
            {
                int sum_numbers_for_procces = child_work(array_procces, array_size_for_procces, k, I);
                if( k == 0)
                {
                    parallel_sum_numbers[k] = sum_numbers_for_procces;
                }
                else parallel_sum_numbers[k] = parallel_sum_numbers[k] + sum_numbers_for_procces;
            }
        }
        else
        {
            printf("Created process = %d\n", pids[i]);
        }
        free(array_procces);
    }
    for (size_t i = 0; i < COUNT_PROCESS; ++i) {
    int status = 0;
    waitpid(-1, &status, WUNTRACED);
    }
    return parallel_sum_numbers;
}
