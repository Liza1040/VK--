#ifndef INCLUDE_PARALLEL
#define INCLUDE_PARALLEL

int* count_numbers(const int* const array_of_numbers, const int array_size, int K, int I);
int* work_procces(const int* const array_procces, int* parallel_sum_numbers, int K, int I, int start_position, int finish_position, int number_procces);
int* sum_numbers_for_k(int* sum_numbers_for_procces, int*parallel_sum_numbers, int count_thread, int K);

#endif //INCLUDE_PARALLEL