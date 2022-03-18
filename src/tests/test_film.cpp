#include <gtest/gtest.h>

extern "C" {
    #include "../list/list.h"
    #include "../find/find_film.h"
}

TEST(Testaddfilminlist, Checkheaditemlist) {
    struct film* head_list_films = read_films_from_file("list_films.txt");
    struct film* find_list_film = get_film(head_list_films, 1);
    struct film* head_find_film = read_films_from_file("find_film.txt");
    struct film* find_find_film = get_film(head_find_film, 1);
    
    EXPECT_STREQ("Елки", find_list_film->name);
    EXPECT_EQ(2010, find_list_film->year_of_release);
    EXPECT_STREQ("комедия", find_list_film->genre);
    EXPECT_EQ(6.9f, find_list_film->average_rating);

    EXPECT_EQ(NULL, find_find_film);
    delete_film(head_list_films);
}

TEST(Testaddfilminlist, Checkitemlist) {
    struct film* head_list_films = read_films_from_file("list_films.txt");
    struct film* find_list_film_2 = get_film(head_list_films, 2);
    struct film* find_list_film_5 = get_film(head_list_films, 5);
    struct film* find_list_film_7 = get_film(head_list_films, 7);
    struct film* find_list_film_10 = get_film(head_list_films, 10);
    
    EXPECT_STREQ("Наследники", find_list_film_5->name);
    EXPECT_EQ(2015, find_list_film_5->year_of_release);
    EXPECT_STREQ("мюзикл", find_list_film_5->genre);
    EXPECT_EQ(7.9f, find_list_film_5->average_rating);

    EXPECT_STREQ("Призрак", find_list_film_2->name);
    EXPECT_EQ(2005, find_list_film_2->year_of_release);
    EXPECT_STREQ("комедия", find_list_film_2->genre);
    EXPECT_EQ(5.5f, find_list_film_2->average_rating);

    EXPECT_EQ(NULL, find_list_film_7);

    EXPECT_EQ(NULL, find_list_film_10);

    delete_film(head_list_films);
}

TEST(Testonopenfile, Checkonopenfile) {
    struct film* head = read_films_from_file("list_films.txt");
    struct film* find = find_film_in_list(head, "find_film.txt");

    EXPECT_EQ(NULL, read_films_from_file("1.txt"));
    EXPECT_EQ(NULL, find_film_in_list(head, "file.txt"));

    EXPECT_STREQ("Елки", head->name);
    EXPECT_STREQ("Наследники", find->name);

    delete_film(head);
    delete_film(find);
}

int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}