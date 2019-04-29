#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MICRO_SECONDS 1000000

int main(int argc, char* argv[]){

    int sleepTime;

    sleepTime = atoi(argv[2]);
    printf("Tempo de espera do processo #%s: %d\n", argv[1], sleepTime);
    usleep(sleepTime);
    printf("Esse é o programa intruso #%s  /o/\n", argv[1]);
    
}
