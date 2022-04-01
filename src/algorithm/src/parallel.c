#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "algorithm.h"

//#define COUNT_PROCESS 100

int* work_procces(const int* const array_procces, int* parallel_sum_numbers, int K, int I, int start_position, int finish_position, int number_procces)
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
        parallel_sum_numbers[k] = sum_number;
        sum_number = 0;
    }
    return parallel_sum_numbers;
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
    int fd[count_thread][2];

    for (int i = 0; i < count_thread; ++i)
    { 
        pipe(fd[i]);
        pids[i] = fork();
        if (pids[i] == -1) 
        {
            printf("fork failed\n");
            return NULL;
        }
        if (pids[i] == 0) 
        {
            close(fd[i][0]);
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
            parallel_sum_numbers = work_procces(array_of_numbers, parallel_sum_numbers, K, I, start_position, finish_position, i);
            write(fd[i][1],parallel_sum_numbers,K*sizeof(int));
            exit(0);
        }
        close(fd[i][1]);
    } 
    for (size_t i = 0; i < count_thread-1; ++i) 
    {
        int status = 0;
        waitpid(-1, &status, WUNTRACED);
    }
    for(int i = 0;i < count_thread;i++)
    {
        read(fd[i][0],&sum_numbers_for_procces[K*i], K*sizeof(int));
    }
    parallel_sum_numbers = sum_numbers_for_k(sum_numbers_for_procces, parallel_sum_numbers, count_thread, K);
    free(sum_numbers_for_procces);
    return parallel_sum_numbers;
}

int* sum_numbers_for_k(int* sum_numbers_for_procces, int*parallel_sum_numbers, int count_thread, int K)
{
    int sum_numbers_for_k = 0;
    for(int i=0; i < K; i++)
    {
        for(int j=0; j < count_thread; j++)
        {
            sum_numbers_for_k = sum_numbers_for_k + *(sum_numbers_for_procces + j * K + i);
        }
        parallel_sum_numbers[i] = sum_numbers_for_k;
        sum_numbers_for_k = 0;
    }
    return parallel_sum_numbers;
}