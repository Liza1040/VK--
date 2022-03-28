packages:
	sudo apt-get update -y && \
	sudo apt-get install build-essential && \
	# sudo apt-get install libgtest-dev && \
	pip3 install cpplint && \
	sudo apt-get install valgrind lcov

build:
	cd src && \
	mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build .

test:
	./src/build/tests/test_film && \
	valgrind --tool=memcheck --leak-check=yes ./src/build/tests/test_film

report:
	lcov -t "tests/test_film" -o coverage.info -c -d find/ && genhtml -o report coverage.info

	