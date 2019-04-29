#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFF_SIZE 32

main(argc, argv)
int argc;
char **argv;
{
    int waiting = 1;
    int s;
    int port;
    struct sockaddr_in server;
    int length;
    char buf[BUFF_SIZE];
    
    port = atoi(argv[2]);
    
    printf("Dados resgatados:\nIP: %s  |  Porta: %i\n", argv[1], port);
    
    // 1o passo: criacao do socket
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s < 0){
        perror("socket()");
        exit(1);
    }
    
    // 2o passo: obtencao das informacoes
    server.sin_family           = AF_INET;
    server.sin_port             = htons(port);
    server.sin_addr.s_addr      = inet_addr(argv[1]);
    
    // 3o passo: tratamento e envio do buffer
    strcpy(buf, argv[3]);
    printf("buf: %s\n", buf);
    
    if(sendto(s, buf, (strlen(buf) + 1), 0, (struct sockaddr *)&server, sizeof server) != strlen(buf)){
        perror("sendto()");
        exit(1);
    }
    /*
    length = sizeof(server);
    
    // 4o passo: recebimento dos dados retornados pelo servidor
    while(waiting){
        if(recvfrom(s, buf, BUFF_SIZE, 0, 
            (struct sockaddr *)&server,
                &length) >= 0){
            waiting = 0;
            printf("Dados recebidos:\n%s\n", buf);
        }
    }
    */
    close(s);
}