#include <gtest/gtest.h>
#include <stdio.h>
// #include <string.h>

extern "C" {
    #include "../algorithm/inc/algorithm.h"
}

TEST(Testcountnumbers, Checkcorrectarguments) {
    int array_of_numbers_100[100];
    int* naive_sum_numbers_100;
    int array_of_numbers_1000[1000];
    int* naive_sum_numbers_1000;
    for(int i = 0; i < 100; i++)
    {
        array_of_numbers_100[i] = i;
    }
    for(int i = 0; i < 1000; i++)
    {
        array_of_numbers_1000[i] = i;
    }
    
    naive_sum_numbers_100 = count_numbers(array_of_numbers_100, 100, 10, 10);
    naive_sum_numbers_1000 = count_numbers(array_of_numbers_1000, 1000, 10, 100);

    EXPECT_EQ(450, naive_sum_numbers_100[0]);
    EXPECT_EQ(460, naive_sum_numbers_100[1]);
    EXPECT_EQ(500, naive_sum_numbers_100[5]);
    EXPECT_EQ(540, naive_sum_numbers_100[9]);

    EXPECT_EQ(49500, naive_sum_numbers_1000[0]);
    EXPECT_EQ(49600, naive_sum_numbers_1000[1]);
    EXPECT_EQ(50000, naive_sum_numbers_1000[5]);
    EXPECT_EQ(50400, naive_sum_numbers_1000[9]);

    free(naive_sum_numbers_1000);
    free(naive_sum_numbers_100);
}

TEST(Testcountnumbers, Checkincorrectarguments) {
    int array_of_numbers_100[100];
    int* naive_sum_numbers_100_size;
    int* naive_sum_numbers_100_K;
    int* naive_sum_numbers_100_I;
    for(int i = 0; i < 100; i++)
    {
        array_of_numbers_100[i] = i;
    }
    
    naive_sum_numbers_100_size = count_numbers(array_of_numbers_100, 10, 10, 10);
    naive_sum_numbers_100_K = count_numbers(array_of_numbers_100, 100, 100, 100);
    naive_sum_numbers_100_I = count_numbers(array_of_numbers_100, 100, 100, 1000);

    EXPECT_EQ(NULL, naive_sum_numbers_100_size);
    EXPECT_EQ(NULL, naive_sum_numbers_100_K);
    EXPECT_EQ(NULL, naive_sum_numbers_100_I);

    free(naive_sum_numbers_100_size);
    free(naive_sum_numbers_100_K);
    free(naive_sum_numbers_100_I);
}