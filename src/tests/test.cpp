#include <gtest/gtest.h>

extern "C" {
    #include "list/list.h"
    #include "find_film/find_film.h"
}

TEST(Testaddfilminlist, Checkheaditemlist) {
    struct film* head_list_films = read_films_from_file("list_films.txt");
    struct film* find_film = get_film(head_list_films, 1)

    EXPECT_STREQ("Елки", find_film->name);
    EXPECT_EQ(2010, find_film->year_of_release);
    EXPECT_STREQ("комедия", find_film->genre);
    EXPECT_EQ(6.9, find_film->average_rating);
}