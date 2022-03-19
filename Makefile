packages:
	sudo apt-get update -y && \
	sudo apt-get install build-essential && \
	sudo apt-get install -y cppcheck clang-tidy python3-pip libc6-dbg lcov libgtest-dev && \
	pip3 install cpplint && \
	sudo apt-get install valgrind

build:
	cd src && \
	mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build . && \
	./src/build/film

check: 
	./linters/run.sh

test:
	./src/build/tests/test_film && \
	valgrind --tool=memcheck --leak-check=yes ./src/build/tests/test_film

report:	
	lcov -t "build/tests/test_film" -o coverage.info -c -d build/find -d build/list

	