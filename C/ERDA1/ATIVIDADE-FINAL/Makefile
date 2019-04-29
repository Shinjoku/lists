main:	main.o	matriz.o	lista.o
	gcc main.o matriz.o lista.o -o main

main.o:	main.c
	gcc main.c -c -w

matriz.o:	matriz.c	matriz.h
	gcc matriz.c -c -w

lista.o:	lista.c	lista.h
	gcc lista.c -c -w
	
clean:
	rm *.o
	clear