#include <gtest/gtest.h>
#include <stdio.h>
// #include <string.h>

extern "C" {
    #include "../naive/naive.h"
    #include "../parallel/parallel.h"
    #include "../array/array.h"
}

TEST(Testnaivecount, Checkcorrectarguments) {
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

    ASSERT_EQ(450, naive_sum_numbers_100[0]);
    ASSERT_EQ(460, naive_sum_numbers_100[1]);
    ASSERT_EQ(500, naive_sum_numbers_100[5]);
    ASSERT_EQ(540, naive_sum_numbers_100[9]);

    ASSERT_EQ(49500, naive_sum_numbers_1000[0]);
    ASSERT_EQ(49600, naive_sum_numbers_1000[1]);
    ASSERT_EQ(50000, naive_sum_numbers_1000[5]);
    ASSERT_EQ(50400, naive_sum_numbers_1000[9]);
}

TEST(Testnaivecount, Checkincorrectarguments) {
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

    ASSERT_EQ(NULL, naive_sum_numbers_100_size);
    ASSERT_EQ(NULL, naive_sum_numbers_100_K);
    ASSERT_EQ(NULL, naive_sum_numbers_100_I);
}
/*TEST(Testnaivecount, Checkincorrectwork) {
    int array_of_numbers_100[100];
    int* naive_sum_numbers_100;
    int array_of_numbers_10[10];
    int* naive_sum_numbers_10;
    for(int i = 0; i < 100; i++)
    {
        array_of_numbers_100[i] = i;
    }
    for(int i = 0; i < 10; i++)
    {
        array_of_numbers_10[i] = i;
    }

    naive_sum_numbers_100 = naive_count(array_of_numbers_100, 100, 10, 100);
    naive_sum_numbers_10 = naive_count(array_of_numbers_10, 10, 10, 10);

    EXPECT_EQ(NULL, naive_sum_numbers_100);

    EXPECT_EQ(NULL, naive_sum_numbers_10);
}*/

/*TEST(Testreadfilmsfromfile, Checkemptyfile) {
    char buffer_empty [] = "";
    FILE* stream_empty =fmemopen(buffer_empty, strlen(buffer_empty), "r");
    struct film *head_list_films = read_films_from_file(stream_empty);
    
    EXPECT_EQ(NULL, head_list_films);
    
    fclose(stream_empty);
}

TEST(Testreadfilmsfromfile, Checknotemptyfile) {
    char buffer_not_empty [] = "Елки; 2010; комедия; 6.9";
    FILE* stream_not_empty =fmemopen(buffer_not_empty, strlen(buffer_not_empty), "r");
    
    struct film *head_list_films = read_films_from_file(stream_not_empty);

    EXPECT_STREQ("Елки", head_list_films->name);
    EXPECT_EQ(2010, head_list_films->year_of_release);
    EXPECT_STREQ("комедия", head_list_films->genre);
    EXPECT_EQ(6.9f, head_list_films->average_rating);
    EXPECT_EQ(print_film(head_list_films), head_list_films);

    fclose(stream_not_empty);
    delete_film(head_list_films);
}

TEST(Testreadfilmsfromfile, Checkskippinginvaliddata) {
    char buffer_1 [] = "Елки; 2010; комедия; 6.9\n2000; комедия; 6";
    char buffer_2 [] = "Наследники; 2011; комедия; 9\nЛето; 55; комедия; 4";
    char buffer_3 [] = "Елки; 2010; комедия; 15";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    FILE* stream_2 =fmemopen(buffer_2, strlen(buffer_2), "r");
    FILE* stream_3 =fmemopen(buffer_3, strlen(buffer_3), "r");

    struct film *head_1 = read_films_from_file(stream_1);
    struct film *head_2 = read_films_from_file(stream_2);
    struct film *head_3 = read_films_from_file(stream_3);

    EXPECT_EQ(NULL, head_1);
    EXPECT_EQ(NULL, head_2);
    EXPECT_EQ(NULL, head_3);

    fclose(stream_1);
    fclose(stream_2);
    fclose(stream_3);
}

TEST(Testreadfilmsfromfile, Checkcorrectdata) {
    char buffer_1 [] = "Елки; 2010; комедия; 6.9\nВерх; 2000; комедия; 6";
    char buffer_2 [] = "Наследники; 2015; мюзикл; 7.9\nИ в печали, и в радости; 2001; романтика; 10";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    FILE* stream_2 =fmemopen(buffer_2, strlen(buffer_2), "r");

    struct film *head_1 = read_films_from_file(stream_1);
    struct film *head_2 = read_films_from_file(stream_2);

    EXPECT_STREQ("Елки", head_1->name);
    EXPECT_EQ(2010, head_1->year_of_release);
    EXPECT_STREQ("комедия", head_1->genre);
    EXPECT_EQ(6.9f, head_1->average_rating);

    EXPECT_STREQ("Верх", get_film(head_1, 2)->name);
    EXPECT_EQ(2000, get_film(head_1, 2)->year_of_release);
    EXPECT_STREQ("комедия", get_film(head_1, 2)->genre);
    EXPECT_EQ(float(6), get_film(head_1, 2)->average_rating);

    EXPECT_STREQ("Наследники", head_2->name);
    EXPECT_EQ(2015, head_2->year_of_release);
    EXPECT_STREQ("мюзикл", head_2->genre);
    EXPECT_EQ(7.9f, head_2->average_rating);

    EXPECT_STREQ("И в печали, и в радости", get_film(head_2, 2)->name);
    EXPECT_EQ(2001, get_film(head_2, 2)->year_of_release);
    EXPECT_STREQ("романтика", get_film(head_2, 2)->genre);
    EXPECT_EQ(float(10), get_film(head_2, 2)->average_rating);

    fclose(stream_1);
    fclose(stream_2);
    delete_film(head_1);
    delete_film(head_2);
}

TEST(Testfindfilmimlist, Checkemptyfile) {
    struct film *list_films = NULL;
    char buffer_empty [] = "";
    FILE* stream_empty =fmemopen(buffer_empty, strlen(buffer_empty), "r");
    struct film *head_list_films = find_film_in_list(list_films, stream_empty);
    
    EXPECT_EQ(NULL, head_list_films);
    
    fclose(stream_empty);
}

TEST(Testfindfilmimlist, Checknotemptyfile) {
    char buffer_not_empty [] = "2010; комедия; 6; 9";
    FILE* stream_not_empty =fmemopen(buffer_not_empty, strlen(buffer_not_empty), "r");
    char buffer_1 [] = "Елки; 2010; комедия; 6.9\nВерх; 2000; комедия; 6";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    
    struct film *list_films = read_films_from_file(stream_1);
    struct film *find_films = find_film_in_list(list_films, stream_not_empty);

    EXPECT_STREQ("Елки", find_films->name);
    EXPECT_EQ(2010, find_films->year_of_release);
    EXPECT_STREQ("комедия", find_films->genre);
    EXPECT_EQ(6.9f, find_films->average_rating);

    fclose(stream_not_empty);
    delete_film(find_films);
    delete_film(list_films);
}

TEST(Testfindfilmimlist, Checkskippinginvaliddata) {
    struct film *list_films = NULL;
    char buffer_1 [] = "2010; комедия; 6.9\n2000; 6";
    char buffer_2 [] = "Наследники; 2011; комедия; 9\n55; комедия; 4";
    char buffer_3 [] = "2010 комедия 15";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    FILE* stream_2 =fmemopen(buffer_2, strlen(buffer_2), "r");
    FILE* stream_3 =fmemopen(buffer_3, strlen(buffer_3), "r");

    struct film *head_1 = find_film_in_list(list_films, stream_1);
    struct film *head_2 = find_film_in_list(list_films, stream_2);
    struct film *head_3 = find_film_in_list(list_films, stream_3);

    EXPECT_EQ(NULL, head_1);
    EXPECT_EQ(NULL, head_2);
    EXPECT_EQ(NULL, head_3);

    fclose(stream_1);
    fclose(stream_2);
    fclose(stream_3);
}

TEST(Testfindfilmimlist, Checkfilmsnotfound) {
    char buffer_list_films [] = "Елки; 2010; комедия; 6.9\nВерх; 2000; комедия; 6\nНаследники; 2015; мюзикл; 7.9\nИ в печали, и в радости; 2001; романтика; 10";
    FILE* stream_list_films =fmemopen(buffer_list_films, strlen(buffer_list_films), "r");
    struct film *head_list_films = read_films_from_file(stream_list_films);
    char buffer_1 [] = "2011; комедия; 6; 9";
    char buffer_2 [] = "2015; драма; 9; 1";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    FILE* stream_2 =fmemopen(buffer_2, strlen(buffer_2), "r");

    struct film *head_1 = find_film_in_list(head_list_films, stream_1);
    struct film *head_2 = find_film_in_list(head_list_films, stream_2);

    EXPECT_EQ(NULL, head_1);
    EXPECT_EQ(NULL, head_2);


    fclose(stream_1);
    fclose(stream_2);
    fclose(stream_list_films);
    delete_film(head_1);
    delete_film(head_2);
    delete_film(head_list_films);
}*/


int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}