//Создать структуру для хранения информации о кинофильме: его названии, годе выпуска, жанре, средней оценке аудитории. Составить с ее использованием программу построения списка фильмов, рекомендуемых для просмотра, по заданным критериям: диапазону оценок, жанру и году выпуска.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct film {
	char * name;
	int year_of_release;
	char * genre;
	float average_rating;
	struct film * next_film;
};

struct film* read_films_from_file();
struct film * add_film(struct film * head, char *const tmp_name, const int tmp_year, char *const tmp_genre, const float tmp_rating);
void print_film(const struct film * const list_films);
void delete(struct film *list_films);
struct film *find_film_in_list(struct film * list_films);


int main() {
	struct film *find_films =  NULL;
	struct film *list_films = read_films_from_file();
	if(list_films)
	{
		find_films = find_film_in_list(list_films);
		if(find_films)
		{
			print_film(find_films);
			delete(find_films);
		}
		delete(list_films);
	}
	return 0;
}


struct film * read_films_from_file()
{
	struct film *list_films = NULL;
	struct film *head_list_films = NULL;
	struct film *new_film = NULL;
	int n = 0;
	char * tmp_name = NULL;
	int tmp_year = 0;
	char * tmp_genre = NULL;
	float tmp_rating = 0;
	FILE *file;
	if ((file = fopen("list_films.txt", "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
	}
	while ((n = fscanf(file, "%ms%d%ms%f\n", &tmp_name, &tmp_year, &tmp_genre, &tmp_rating)) != EOF) 
	{
		if (tmp_name != NULL && tmp_year >= 1888 && tmp_genre != NULL && tmp_rating >= 0 && tmp_rating <= 10 && n == 4)
		{
			head_list_films = add_film(head_list_films, tmp_name, tmp_year, tmp_genre, tmp_rating);
		}
		else 
		{
			if (tmp_name != NULL)free(tmp_name);
			if (tmp_genre != NULL)free(tmp_genre);
		}
	}
	fclose(file);
	if (head_list_films == NULL)	
	{
		printf("Файл, содержащий список фильмов, пуст!\n");
		if (tmp_name != NULL)free(tmp_name);
		if (tmp_genre != NULL)free(tmp_genre);
	}
	return head_list_films;
}

//struct film * cteate_list_film(char *const tmp_name, const int tmp_year, char *const tmp_genre, const float tmp_rating)
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


struct film *find_film_in_list(struct film * list_films)
{
	struct film *head_find_films = NULL;
	struct film *find_films = NULL;
	struct film *new_film = NULL;
	int n = 0;
	int find_year = 0;
	char * find_genre = NULL;
	float min_rating = 0;
	float max_rating = 0;
	FILE *file;
	struct film * safe_exit()
	{
		if (find_genre != NULL)
			free(find_genre);
		fclose(file);
		return head_find_films;
	}


	if ((file = fopen("find_film.txt", "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		return head_find_films;	
	}
	n = fscanf(file,"%d%ms%f%f",&find_year,&find_genre,&min_rating,&max_rating);
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