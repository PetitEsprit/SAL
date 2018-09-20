all: main

sal.o: sal.c
	gcc -c sal.c
	
exemple.o: exemple.c
	gcc -c exemple.c
	
main: sal.o exemple.o
	gcc *.o -lSDL -o tost
	./tost

clean:
	sudo rm -f *.o *.out
