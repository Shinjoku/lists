main:	main.o	lista.o	arvore.o arquivos.o
	gcc main.o lista.o arvore.o arquivos.o -o main

main.o:	main.c
	gcc main.c -c -w

lista.o:	lista.c	lista.h
	gcc lista.c -c -w
	
arvore.o:	arvore.c	arvore.h
	gcc arvore.c -c -w

arquivos.o:	arquivos.c	arquivos.h
	gcc arquivos.c -c -w
	
clean:
	rm *.o
	clear