#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

main(argc, argv)
	 int argc;
	 char *argv[];	// Dizer qual host e porta quer acessar
{
	int i;
	// DATA é o q será transmitido no sendto
	char *DATA = (char *) malloc(sizeof(char) * 1024);
	
	// Inicialização da DATA
	strcpy(DATA, "");
	
	//Obtenção das palavras:
	for(i = 3; i < argc; i++){
		strcat(DATA, argv[i]);
		if(i < argc - 1)
			strcat(DATA, " ");
	}
	
	//Setando o tamanho da string recebida para passar para o sendto:
	int len = strlen(DATA);
	
	int sock, cont, length;
	struct sockaddr_in name; // Estrutura pra conter um endereço de internet definido em in.h
	/*
		sin_family; 	// e.g. AF_INET
	    sin_port;   	// e.g. htons(3490)
	    sin_addr;   	// see struct in_addr, below
	    sin_zero[8];	// zero this if you want to
    */
	struct hostent *hp, *gethostbyname();

		/* Cria o socket de comunicacao */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0) {
	/*
	/- houve erro na abertura do socket
	*/
		perror("opening datagram socket");
		exit(1);
	}
	/* Associa */
		hp = gethostbyname(argv[1]);	// Retorna uma struct com várias informações do hostname que 
		if (hp == 0) {					//	foi dado inicialmente
			fprintf(stderr, "%s: unknown host ", argv[1]);
			exit(2);
		}
	// Especifica o único endereço que se quer fazer a troca
	bcopy((char *) hp->h_addr, (char *) &name.sin_addr, hp->h_length);
	
	// Especifica o conjunto de endereços da família
	name.sin_family = AF_INET;		
	name.sin_port = htons(atoi(argv[2]));			
	length = sizeof(name);
	
	/* Envia */
	if (sendto (sock, DATA, len, 0, 
		(struct sockaddr *) &name,
				sizeof name) < 0)
			perror("sending datagram message");

	if(recvfrom(sock, (char *)&cont, sizeof cont, 0, 
		(struct sockaddr *) &name,
			   &length) < 0)
			perror("Sending error packet");
		printf("	%i\n", cont);
	
		close(sock);
		exit(0);
}