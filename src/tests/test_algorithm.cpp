#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "../algorithm/inc/algorithm.h"
}

TEST(Testreadarrayfromfile, Checkcorrectfile) {
    char buffer [] = "1\n2\n3\n4\n5\n6\n7\n8\n99\n";
    FILE* file =fmemopen(buffer, strlen(buffer), "r");
    int* array = read_array_from_file(file,9);
    
    EXPECT_EQ(1, array[0]);
    EXPECT_EQ(2, array[1]);
    EXPECT_EQ(3, array[2]);
    EXPECT_EQ(4, array[3]);
    EXPECT_EQ(5, array[4]);
    EXPECT_EQ(6, array[5]);
    EXPECT_EQ(7, array[6]);
    EXPECT_EQ(8, array[7]);
    EXPECT_EQ(99, array[8]);

    free(array);
    fclose(file);
}

TEST(Testreadarrayfromfile, Checkincorrectfile) {
    char buffer_incorrect [] = "1\n2\n3\nghfb\n5\n6\n7\n8\n99\n";
    FILE* file_1 =fmemopen(buffer_incorrect, strlen(buffer_incorrect), "r");
    int* array_buffer_incorrect = read_array_from_file(file_1,9);
    
    char buffer_correct [] = "1\n2\n3\n4\n5\n6\n7\n8\n99\n";
    FILE* file_2 =fmemopen(buffer_incorrect, strlen(buffer_correct), "r");
    int* array_size_incorrect = read_array_from_file(file_2,50);
    
    EXPECT_EQ(NULL, array_buffer_incorrect);
    EXPECT_EQ(NULL, array_size_incorrect);

    free(array_buffer_incorrect);
    free(array_size_incorrect);
    fclose(file_1);
    fclose(file_2);
}