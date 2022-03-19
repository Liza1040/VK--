#include <gtest/gtest.h>
#include <stdio.h>
#include <string.h>

extern "C" {
    #include "../list/list.h"
    #include "../find/find_film.h"
}

TEST(Testaddfilminlist, Checkitemlist) {
    struct film* head_list_films = NULL;

    char* film_1 = new_string("Елки");
    char* genre_1 = new_string("комедия");

    char* film_2 = new_string("Лето");
    char* genre_2 = new_string("приключения");

    char* film_3 = new_string("Зима");

    char* genre_3 = new_string("драма");

    head_list_films = add_film(head_list_films, film_1, 2010, genre_1, 6.9);
    head_list_films = add_film(head_list_films, film_2, 2021, genre_2, 5);
    head_list_films = add_film(head_list_films, film_3, 2020, genre_3, 7.5);
    
    EXPECT_STREQ("Елки", head_list_films->name);
    EXPECT_EQ(2010, head_list_films->year_of_release);
    EXPECT_STREQ("комедия", head_list_films->genre);
    EXPECT_EQ(6.9f, head_list_films->average_rating);
    EXPECT_EQ(get_film(head_list_films, 2), head_list_films->next_film);

    EXPECT_STREQ("Лето", get_film(head_list_films, 2)->name);
    EXPECT_EQ(2021, get_film(head_list_films, 2)->year_of_release);
    EXPECT_STREQ("приключения", get_film(head_list_films, 2)->genre);
    EXPECT_EQ(float(5), get_film(head_list_films, 2)->average_rating);
    EXPECT_EQ(get_film(head_list_films, 3), get_film(head_list_films, 2)->next_film);

    EXPECT_STREQ("Зима", get_film(head_list_films, 3)->name);
    EXPECT_EQ(2020, get_film(head_list_films, 3)->year_of_release);
    EXPECT_STREQ("драма", get_film(head_list_films, 3)->genre);
    EXPECT_EQ(7.5f, get_film(head_list_films, 3)->average_rating);
    EXPECT_EQ(NULL, get_film(head_list_films, 3)->next_film);

    delete_film(head_list_films);
}

TEST(Testreadfilmsfromfile, Checkemptyfile) {
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

TEST(Testfindfilmimlist, Checkcorrectdata) {
    char buffer_list_films [] = "Елки; 2010; комедия; 6.9\nВерх; 2000; комедия; 6\nНаследники; 2015; мюзикл; 7.9\nИ в печали, и в радости; 2001; романтика; 10";
    FILE* stream_list_films =fmemopen(buffer_list_films, strlen(buffer_list_films), "r");
    struct film *head_list_films = read_films_from_file(stream_list_films);

    char buffer_1 [] = "2010; комедия; 6; 9";
    char buffer_2 [] = "2015; мюзикл; 9; 1";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    FILE* stream_2 =fmemopen(buffer_2, strlen(buffer_2), "r");

    struct film *head_1 = find_film_in_list(head_list_films, stream_1);
    struct film *head_2 = find_film_in_list(head_list_films, stream_2);

    EXPECT_STREQ("Елки", head_1->name);
    EXPECT_EQ(2010, head_1->year_of_release);
    EXPECT_STREQ("комедия", head_1->genre);
    EXPECT_EQ(6.9f, head_1->average_rating);

    EXPECT_STREQ("Наследники", head_2->name);
    EXPECT_EQ(2015, head_2->year_of_release);
    EXPECT_STREQ("мюзикл", head_2->genre);
    EXPECT_EQ(7.9f, head_2->average_rating);

    delete_film(head_1);
    delete_film(head_2);
    fclose(stream_1);
    fclose(stream_2);

    fclose(stream_list_films);
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
}

TEST(Testfindfilmimlist, Checkfilmsfound) {
    char buffer_list_films [] = "Елки; 2010; комедия; 6.9\nВерх; 2000; комедия; 6\nНаследники; 2015; мюзикл; 7.9\nИ в печали, и в радости; 2001; романтика; 10";
    FILE* stream_list_films =fmemopen(buffer_list_films, strlen(buffer_list_films), "r");
    struct film *head_list_films = read_films_from_file(stream_list_films);

    char buffer_1 [] = "2010; комедия; 6; 9";
    char buffer_2 [] = "2015; мюзикл; 9; 1";

    FILE* stream_1 =fmemopen(buffer_1, strlen(buffer_1), "r");
    FILE* stream_2 =fmemopen(buffer_2, strlen(buffer_2), "r");

    struct film *head_1 = find_film_in_list(head_list_films, stream_1);
    struct film *head_2 = find_film_in_list(head_list_films, stream_2);

    EXPECT_STREQ("Елки", head_1->name);
    EXPECT_EQ(2010, head_1->year_of_release);
    EXPECT_STREQ("комедия", head_1->genre);
    EXPECT_EQ(6.9f, head_1->average_rating);

    EXPECT_STREQ("Наследники", head_2->name);
    EXPECT_EQ(2015, head_2->year_of_release);
    EXPECT_STREQ("мюзикл", head_2->genre);
    EXPECT_EQ(7.9f, head_2->average_rating);

    fclose(stream_1);
    fclose(stream_2);
    fclose(stream_list_films);
    delete_film(head_1);
    delete_film(head_2);
    delete_film(head_list_films);
}

int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}