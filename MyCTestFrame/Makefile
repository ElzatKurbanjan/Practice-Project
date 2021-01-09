.PHONY: clean

all: use_test.o ./src/test.o
	gcc ./src/test.o use_test.o -o ./bin/my_app

./src/test.o: ./src/test.c ./include/test.h ./include/color.h
	gcc -I./include -c ./src/test.c -o ./src/test.o

use_test.o: use_test.c ./include/test.h
	gcc -I./include -c use_test.c

clean:
	-rm ./bin/my_app ./src/*.o ./*.o
