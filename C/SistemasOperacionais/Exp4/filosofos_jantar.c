//-- INCLUDES --------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>

//-- DEFINES ---------------------------------------------------------------------
#define N_FILOSOF 5							//Quantidade de Filósofos
#define PENSAR 0					//Identificação do estado do filosofo
#define FOME 1						//Identificação do estado do filosofo
#define COMER 2						//Identificação do estado do filosofo
#define ESQUERDA (nfilosofo+4) % N_FILOSOF	//agarrar garfo da esquerda
#define DIREITA (nfilosofo+1) % N_FILOSOF	//agarrar garfo da direita

//-- GLOBAL VARIABLES ------------------------------------------------------------
void *filosofo(void *num);
void agarraGarfo(int);
void deixaGarfo(int);
void testar(int);

pthread_mutex_t mutex;							//Região crítica
pthread_mutex_t mux_filo [N_FILOSOF];			//Mutex por filósofo


int estado[N_FILOSOF];
int nfilosofo[N_FILOSOF] = {0, 1, 2, 3, 4};


void *filosofo(void *num){
	
	int j = 0;
	
	while(j < 365){
		
		int *i = num;
		sleep(1);
		agarraGarfo(*i);
		sleep(1);
		deixaGarfo(*i);
		j++;
	}
	
	pthread_exit( (void*) 0 );		//Legado do retorno
}

void agarraGarfo(int nfilosofo){
	
	pthread_mutex_lock( &(mutex) );					//Entra na regiсo crítica
	estado[nfilosofo] = FOME;
	printf("Filosofo %d tem fome.\n", nfilosofo + 1);
	fflush(stdout);
	//+1 para imprimir filosofo 1 e nao filosofo 0
	testar(nfilosofo);
	pthread_mutex_unlock( &(mutex) );				//Sai na região crítica
	pthread_mutex_lock( &(mux_filo[nfilosofo]) );	//Bloqueia os garfos
	

	sleep(1);
}

void deixaGarfo(int nfilosofo){
	
	pthread_mutex_lock ( &(mutex) );	//Entra na regiсo crítica
	estado[nfilosofo] = PENSAR;
	printf("Filosofo %d deixou os garfos %d e %d.\n", nfilosofo + 1, ESQUERDA + 1, nfilosofo + 1);
	fflush(stdout);
	printf("Filosofo %d esta a pensar.\n", nfilosofo + 1);
	fflush(stdout);
	testar(ESQUERDA);
	testar(DIREITA);
	pthread_mutex_unlock ( &(mutex) );	//Sai da regiсo crítica
}

void testar(int nfilosofo){
	
	if(estado[nfilosofo] == FOME && estado[ESQUERDA] != COMER && estado[DIREITA] != COMER){
		  
		estado[nfilosofo] = COMER;
		sleep(2);
		printf("Filosofo %d agarrou os garfos %d e %d.\n", nfilosofo+1, ESQUERDA+1, nfilosofo+1);
		fflush(stdout);
		printf("Filosofo %d esta a comer.\n", nfilosofo+1);
		fflush(stdout);
		pthread_mutex_unlock( &(mux_filo[nfilosofo]) );	//Libera os Garfos
	}
}		

int main() {
	
	int i;
	int status;	//Criação da thread
	pthread_t thread_id[N_FILOSOF]; //identificadores das
							   //threads
	pthread_mutex_init( &(mutex), NULL);
	
	for(i = 0; i < N_FILOSOF; i++)
		pthread_mutex_init( &(mux_filo[N_FILOSOF]), NULL );
		
	for(i = 0; i < N_FILOSOF; i++){
		
		status = pthread_create(&thread_id[i], NULL, filosofo, &nfilosofo[i]);
		if ( status )
		{
			printf("Erro criando thread %d, retornou codigo %d\n", i, status );
			fflush(stdout);
			return 0;
		}
		//criar as threads
		printf("Filosofo %d esta a pensar.\n", i+1);
		fflush(stdout);
	}
	for(i = 0; i < N_FILOSOF; i++)
		pthread_join(thread_id[i],NULL);	//para fazer a junção das threads
	
	//Destroi antes de sair
	pthread_mutex_destroy( &(mutex) );
	for( i = 0 ; i < N_FILOSOF ; i++ )
	{
		pthread_mutex_destroy( &(mux_filo[i]) );
	}
	return(0);
}