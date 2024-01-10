CC = gcc
CFLAGS = -Wall -pedantic -g
FRONTEND_SRC = frontend.c utils.c hash_table.c linked_list.c
BACKEND_SRC = backend.c utils.c hash_table.c linked_list.c
FRONTEND_OBJS = $(FRONTEND_SRC: .c = .o)
BACKEND_OBJS = $(BACKEND_SRC: .c = .o)

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -pg

frontend_: frontend.o utils.o hash_table.o linked_list.o
	$(CC) $(CFLAGS) -lm -o -g $@ $^ 

backend: backend.o utils.o hash_table.o linked_list.o
	$(CC) $(CFLAGS) -lm -o -c -g $@ $^

full: frontend.o backend.o utils.o hash_table.o linked_list.o
	$(CC) $(CFLAGS) -lm -o -c -g $@ $^
	
clean: 
	rm frontend frontend_test stdout.txt stdout_new.txt test
	clear

frontend: frontend.c 
	gcc -Wall -pedantic -g frontend.c backend.c hash_table.c linked_list.c utils.c -o frontend
	valgrind --leak-check=full ./frontend

test: tests.c
	gcc -Wall -pedantic -g backend.c frontend.c hash_table.c linked_list.c utils.c tests.c -lcunit -o test
	valgrind --leak-check=full --show-leak-kinds=all ./test

.PHONY: frontend test
