// В вашем распоряжении — массив из 100 млн. чисел. Составьте наивный алгоритм подсчета суммы [k+ 10i]-х элементов для каждого k = 1, 10 (i = 0, 10000000), 
//после чего реализуйте параллельный алгоритм на нескольких процессах с учетом оптимизации работы с кэш-памятью.

#include <stdio.h>
#include <stdlib.h>

#include "array/array.h"
#include "parallel/parallel.h"
#include "naive/naive.h"


#define ARRAY_OF_NUMBERS "array.txt"
#define ARRAY_SIZE 100000000
#define K 10
#define I 10000000

int main() {
	FILE *file;
    int k = K;
    int i = I;
	if ((file = fopen(ARRAY_OF_NUMBERS, "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		fclose(file);
		return -1;
	}
    int* array = read_array_from_file(file, ARRAY_SIZE);
    if(array == NULL)
    {
        fclose(file);
		return -1;
    }
    int* sum = count_numbers(array,ARRAY_SIZE, k, i);
    if(sum == NULL)
    {
        fclose(file);
		return -1;
    }
    for(int i=0; i<10;i++)
    {
        printf("%d\n",sum[i]);
    }
    free(array);
    free(sum);
    fclose(file);
    return 0;
}