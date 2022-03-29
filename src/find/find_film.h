#ifndef INCLUDE_FIND_FILM
#define INCLUDE_FIND_FILM

#include "../list/list.h"
struct film *find_film_in_list(struct film * list_films, FILE *file);
struct film* read_films_from_file(FILE *file);
char* new_string(const char* buf);

#endif //INCLUDE_FIND_FILM