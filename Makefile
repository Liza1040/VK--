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
	./tests/test_sum

test:
	./src/build/tests/test_sum && \
	valgrind --tool=memcheck --leak-check=yes ./src/build/tests/test_sum

report:	
	cd src/build && \
	lcov -t "tests/test_sum" -o coverage.info -c -d naive/ && \
	genhtml -o report coverage.info

	