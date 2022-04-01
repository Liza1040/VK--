#ifndef INCLUDE_PARALLEL
#define INCLUDE_PARALLEL

int* count_numbers(const int* const array_of_numbers, const int array_size, int K, int I);
int child_work(int* array_procces, int array_size_for_procces, int k, int I);
int* read_array_from_file(FILE *file, const int array_size);

#endif //INCLUDE_PARALLEL