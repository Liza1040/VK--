#ifndef INCLUDE_FIND_FILM
#define INCLUDE_FIND_FILM

#include "../list/list.h"
struct film *find_film_in_list(struct film * list_films, const char* file_name);
struct film* read_films_from_file(const char* file_name);

#endif //INCLUDE_FIND_FILM