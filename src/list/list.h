#ifndef INCLUDE_LIST
#define INCLUDE_LIST

struct film {
	char * name;
	int year_of_release;
	char * genre;
	float average_rating;
	struct film * next_film;
};

struct film * add_film(struct film * head, char *const tmp_name, const int tmp_year, char *const tmp_genre, const float tmp_rating);
void print_film(const struct film * const list_films);
void delete(struct film *list_films);
struct film * get_film(struct film * head, int number_film)

#endif //INCLUDE_LIST