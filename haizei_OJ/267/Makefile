TEST_SET:=${shell ls test_data}

run: ${TEST_SET} a.out
	./a.out < test_data/1
	./a.out < test_data/2
	./a.out < test_data/3
	./a.out < test_data/4
	./a.out < test_data/5
	./a.out < test_data/6
	./a.out < test_data/7
	./a.out < test_data/8
	./a.out < test_data/9
	./a.out < test_data/10
	./a.out < test_data/11
	./a.out < test_data/12
	./a.out < test_data/13
	./a.out < test_data/14
a.out : solution.c
	gcc solution.c

${TEST_SET} : 

