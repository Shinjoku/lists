//-- INCLUDES --------------------------------------------------------------------
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//-- DEFINES ---------------------------------------------------------------------
#define QNTD 5
#define ESQUERDA (nfilosofo+4) % N	//agarrar garfo da esquerda
#define DIREITA (nfilosofo+1) % N	//agarrar garfo da direita

//-- GLOBAL VARIABLES ------------------------------------------------------------
int j = 0;

// Filosofos
void *filosofo (void *num)
{
	int *id = (int *) num;	//Repassa o id do filósofo

	printf("Filosofo %d foi criado com sucesso\n", *id);
	fflush(stdout);

	while(j < 365){
		
		int *i = num;
		sleep(1);
		agarraGarfo(*i);
		sleep(1);
		deixaGarfo(*i);
		j++;
	}

	pthread_exit((void*) 0);		//Legado do retorno
}