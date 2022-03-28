packages:
	sudo apt-get update -y && \
	sudo apt-get install build-essential && \
	pip3 install cpplint

build:
	cd src && \
	mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build . && \
	./tests/test_film

test:
	./src/build/tests/test_film && \
	valgrind --tool=memcheck --leak-check=yes ./src/build/tests/test_film

report:
	lcov -t "tests/test_film" -o coverage.info -c -d find/ && genhtml -o report coverage.info

	