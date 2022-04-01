#ifndef INCLUDE_PARALLEL
#define INCLUDE_PARALLEL

int* count_numbers(const int* const array_of_numbers, const int array_size, int K, int I);
void work_procces(const int* const array_procces, int* parallel_sum_numbers, int K, int I, int start_position, int finish_position, int number_procces);
int* read_array_from_file(FILE *file, const int array_size);

#endif //INCLUDE_PARALLEL