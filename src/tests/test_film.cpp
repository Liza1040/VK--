#include <gtest/gtest.h>

extern "C" {
    #include "../list/list.h"
    #include "../find/find_film.h"
}

TEST(Testaddfilminlist, Checkheaditemlist) {
    struct film* head_list_films = read_films_from_file("list_films.txt");
    struct film* find_film = get_film(head_list_films, 1);
    
    ASSERT_STREQ("Елки", find_film->name);
    ASSERT_EQ(2010, find_film->year_of_release);
    ASSERT_STREQ("комедия", find_film->genre);
    ASSERT_EQ(6.9f, find_film->average_rating);
}

int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}