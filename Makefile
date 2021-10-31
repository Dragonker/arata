CC=gcc

arata: main.c string.c
	$(CC) -o arata main.c string.c

test: test.c
	$(CC) -o test test.c
