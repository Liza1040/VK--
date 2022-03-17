#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct film * add_film(struct film * head, char *const tmp_name, const int tmp_year, char *const tmp_genre, const float tmp_rating)
{
	struct film *new_film = NULL;
	new_film = (struct film *)malloc(sizeof(struct film));
	new_film->name = tmp_name;
	new_film->year_of_release = tmp_year;
	new_film->genre = tmp_genre;
	new_film->average_rating = tmp_rating;				
	new_film->next_film = NULL;
	if(head == NULL)
	{
		return new_film;
	}
	struct film *tail = head;
	while (tail->next_film != NULL)
	{
		tail = tail->next_film;
	}
	tail->next_film = new_film;
	return head;
}


void print_film(const struct film * const list_films)
{
	if(list_films != NULL)
	{
		printf("%s ", list_films->name);
      		printf("%d ", list_films->year_of_release);
      		printf("%s ", list_films->genre);
      		printf("%f\n", list_films->average_rating);
		print_film(list_films->next_film);
	}
}


void delete(struct film *list_films)
{
	struct film *tmp;
	while(list_films != NULL)
	{
		tmp = list_films;
		list_films = list_films->next_film;
		free(tmp->name);
		free(tmp->genre);
		free(tmp);
	}
}