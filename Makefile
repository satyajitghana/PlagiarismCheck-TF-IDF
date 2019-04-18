CC=gcc
CFLAGS=-I.
OUTPUT=pcheck

build: main.o vector.o input_helper.o file_reader.o hash_map.o pcheck.o
	$(CC) -lm main.o vector.o input_helper.o file_reader.o hash_map.o pcheck.o -o $(OUTPUT)

main.o: main.c
	$(CC) -c main.c

timeutil.o: timeutil.c timeutil.h
	$(CC) -c timeutil.c

vector.o: vector.c vector.h
	$(CC) -c vector.c

file_reader.o: file_reader.c file_reader.h
	$(CC) -c file_reader.c

hash_map.o: hash_map.c hash_map.h
	$(CC) -c hash_map.c

pcheck.o: pcheck.c pcheck.h
	$(CC) -c pcheck.c

clean:
	rm *.o $(OUTPUT)
