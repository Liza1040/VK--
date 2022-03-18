//Создать структуру для хранения информации о кинофильме: его названии, годе выпуска, жанре, средней оценке аудитории. Составить с ее использованием программу построения списка фильмов, рекомендуемых для просмотра, по заданным критериям: диапазону оценок, жанру и году выпуска.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"
#include "find/find_film.h"

#define FIND_FILM "find_film.txt"
#define LIST_FILM "list_films.txt"

int main() {
	struct film *find_films =  NULL;
	struct film *list_films = NULL; //read_films_from_file(LIST_FILM);
	FILE *file_list;
	FILE *file_find;
	if ((file_list = fopen(LIST_FILM, "r")) == NULL || (file_find = fopen(FIND_FILM, "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		return -1;
	}
	list_films = read_films_from_file(file_list);
	if(list_films)
	{
		//print_film(list_films);
		find_films = find_film_in_list(list_films, file_find);
		if(find_films)
		{
			print_film(find_films);
			delete_film(find_films);
		}
		delete_film(list_films);
	}
	fclose(file_list);
	fclose(file_find);
	return 0;
}
