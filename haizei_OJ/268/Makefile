run: a.out
	./a.out < test_data

a.out: friend_queue.c
	gcc friend_queue.c

.PHONY: clean
clean:
	-rm a.out