.PHONY: all
all: test

%.o: %.c
	gcc -Wall $^ -c $@ -ggdb3 -O0 -fsanitize=address

test: list.o test.o
	gcc -o $@ $^ -ggdb3 -O0 -fsanitize=address

test_double_linked_list: double_linked_list.o test.o
	gcc -o $@ $^ -ggdb3 -O0 -fsanitize=address

.PHONY: clean
clean:
	rm -f test *.o
