run: a.out test.sh
	./test.sh

a.out: cal.c
	gcc cal.c -lm 

test.sh: test_data

.PHONY: clean
clean:
	-rm -rf a.out 