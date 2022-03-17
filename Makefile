build:
	cd src && gcc main.c list/list.c -Wall -o main.out
run: build
	cd src && ./main.out