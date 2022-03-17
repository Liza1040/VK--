build:
	cd src && gcc main.c find_film/find_film.c list/list.c -Wall -o main.out
test:
	cd src && \
	cppcheck --error-exitcode=1 *.c *.h && \
	g++ test/test.cpp -o test.out main.c find_film/find_film.c list/list.c -lgtestgtest -lpthread && \
	./test.out
run: build
	cd src && ./main.out