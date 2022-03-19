#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../list/list.h"
#include "find_film.h"


struct film * read_films_from_file(FILE *file)
{
	struct film *head_list_films = NULL;
	int n = 0;
	char * tmp_name = NULL;
	int tmp_year = 0;
	char * tmp_genre = NULL;
	float tmp_rating = 0;
	char buf_name[256];
	char buf_genre[256];
	while ((n = fscanf(file, "%255[^;];%d; %255[^;];%f\n", &(buf_name[0]), &tmp_year, &(buf_genre[0]), &tmp_rating)) == 4 )  
	{
		tmp_name = new_string(buf_name);
		tmp_genre = new_string(buf_genre);
		if (tmp_name != NULL && tmp_year >= 1888 && tmp_genre != NULL && tmp_rating >= 0 && tmp_rating <= 10 && n == 4)
		{
			head_list_films = add_film(head_list_films, tmp_name, tmp_year, tmp_genre, tmp_rating);
			tmp_name = NULL;
			tmp_genre = NULL;
		}
		else 
		{
			break;
		}
	}
	if(n != EOF)
	{
		printf("Некорректные данные\n");
		free(tmp_name);
		free(tmp_genre);
		return NULL;
	}
	if (head_list_films == NULL)	
	{
		printf("Файл, содержащий список фильмов, пуст!\n");
		free(tmp_name);
		free(tmp_genre);
	}
	return head_list_films;
}

char* new_string(const char* buf)
{
	char* string = (char *)malloc(strlen(buf));
    strcpy(string, buf);
	return string;
}

struct film *find_film_in_list(struct film * list_films, FILE *file)
{	
	struct film *head_find_films = NULL;
	int n = 0;
	int find_year = 0;
	char * find_genre = NULL;
	float min_rating = 0;
	float max_rating = 0;
	char buf_genre[256];
	struct film * safe_exit()
	{
		if (find_genre != NULL)
		free(find_genre);
		return head_find_films;
	}

	n = fscanf(file,"%d; %255[^;];%f;%f",&(find_year), &(buf_genre[0]), &min_rating, &max_rating);
	find_genre = new_string(buf_genre);
	if (n == EOF)
	{
		printf("Файл с критериями пуст!\n");
		return safe_exit();
	}
	if (find_year < 1888 || find_genre == NULL || min_rating < 0 || min_rating > 10 || max_rating < 0 || max_rating > 10 || n != 4)
	{
		printf("Некорректные критерии для поиска фильмов!\n");
		return safe_exit();
	}
	if(min_rating > max_rating) 
	{
		int change_min_max = min_rating; 
		min_rating = max_rating; 
		max_rating = change_min_max;
	}
	
	while(list_films != NULL)
	{
		if(list_films->year_of_release == find_year &&  strcmp(list_films->genre,find_genre) == 0 && list_films->average_rating >= min_rating && list_films->average_rating <= max_rating)
		{
			char * name = strdup(list_films->name);
			char * add_genre = strdup(find_genre);
			head_find_films = add_film(head_find_films, name, find_year, add_genre, list_films->average_rating);
			list_films = list_films->next_film;
		}
		else
		{
			list_films = list_films->next_film;
		}	
	}
	if (head_find_films == NULL)
	{
		printf("Фильмы удовлетворяющие критериям не найдены!");
	}
	return safe_exit();
}