CC = gcc
FLAGS = -g

slast: slast.o
	$(CC) $(FLAGS) -o slast slast.o
	
slast.o: slast.c
	$(CC) $(FLAGS) -c slast.c
	
clean:
	rm -f slast.o slast
