//Создать структуру для хранения информации о кинофильме: его названии, годе выпуска, жанре, средней оценке аудитории. Составить с ее использованием программу построения списка фильмов, рекомендуемых для просмотра, по заданным критериям: диапазону оценок, жанру и году выпуска.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"
#include "find_film/find_film.h"

#define FIND_FILM "../find_film.txt"
#define LIST_FILM "../list_films.txt"

int main() {
	struct film *find_films =  NULL;
	struct film *list_films = read_films_from_file(LIST_FILM);
	if(list_films)
	{
		find_films = find_film_in_list(list_films, FIND_FILM);
		if(find_films)
		{
			print_film(find_films);
			delete(find_films);
		}
		delete(list_films);
	}
	return 0;
}
