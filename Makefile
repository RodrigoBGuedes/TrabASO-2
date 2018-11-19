CC = gcc
FLAGS = -O2 -pthread

filesys:
	$(CC) main.c $(FLAGS)
	./a.out