/* Nomes: José Carlos Clausen Neto
		  Raissa Furlan Davinha
		  Luiz Felipe Zerbetto Masson
*/
/*
http://stackoverflow.com/questions/19692515/sleeping-barber-algorithm-with-multiple-barbers

cria um vetor de struc com espaço para cada barbeiro, ligano eles ao local;
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define CHAIRS 7                /* número de cadeiras para os clientes à espera */
#define TRUE 1
#define FALSE 0
#define NUM_CLIENTE	27
#define NUM_BARBEIROS	3
#define SIZE 10

typedef struct Books {
   int id;
   char mensagem[SIZE * 4];
   int quantidade;
   int resposta[SIZE];
} Book;

/* Variáveis Globais */
sem_t customers;						/* número de cliente à espera de atendimento */
sem_t barbers;							/* número de barbeiros à espera de clientes */
pthread_mutex_t mutex;					/* para exclusão mútua */
int lugaresLivres = CHAIRS;				/* clientes que estão esperando (não estão cortando) */
int lugares[CHAIRS];
int lugarvago = 0;
int proximocliente = 0;
Book cadeiras[CHAIRS];


/* Protótipos */
void* barber(void *arg);
void* customer(void *arg);
void cut_hair(int id, int cliente, int *v, int quantidade);
void customer_arrived(int id);
void get_haircut(int id, Book mensagem, int time);
void giveup_haircut(int id);
void numtoa(int i, char* aux);
void stringToInt(char* aux, int vezes, int* v);

/* Main */
int main() {
	sem_init(&customers, TRUE, 0);
	sem_init(&barbers, TRUE, 0);
	pthread_mutex_init( &(mutex), NULL);
	int status, count, i;
	
	pthread_t b[NUM_BARBEIROS], c[NUM_CLIENTE];
	/* criando barbeiroS */
	for(count =0; count < NUM_BARBEIROS; count++) {
		status = pthread_create(&b[count], NULL, barber, (void*) count);
		if ( status )
		{
			printf("Erro criando thread %d, retornou codigo %d\n", count, status );
			fflush(stdout);
			return 0;
		}
		sleep(1);
	}


	/* criação de clientes */
	for(count =0; count < NUM_CLIENTE; count++) {
		status = pthread_create(&c[count], NULL, customer, (void*) count);
		if ( status )
		{
			printf("Erro criando thread %d, retornou codigo %d\n", count, status );
			fflush(stdout);
			return 0;
		}
		sleep(1);
	}
	printf("Lugares Livres: %d\n", lugaresLivres);
	fflush(stdout);
	for(i = 0; i < NUM_CLIENTE; i++)
		pthread_join(c[i],NULL);	//para fazer a junção das threads
	pthread_mutex_destroy( &(mutex) );	
	sem_destroy(&customers);
	sem_destroy(&barbers);
	
	return 0;
}

void *barber(void *arg) {
	
	int id, proximo, idcliente;
	
	id = arg;
	
	while(TRUE) {
		sem_wait(&barbers);   /* vai dormir se o número de clientes for 0 */
		pthread_mutex_lock( &(mutex) );     /* obtém acesso a 'lugaresLivres' */
		proximocliente = (proximocliente+1) % CHAIRS;
		proximo = proximocliente;
		idcliente = cadeiras[proximo].id;		
		//troca o id do cliente pelo do barbeiro para o cliente
		cadeiras[proximo].id = id;
		lugaresLivres = lugaresLivres + 1;

		//função que transforma a string em um vetor que sera ordenado
		stringToInt(cadeiras[proximo].mensagem, cadeiras[proximo].quantidade, cadeiras[proximo].resposta);
		
		/*ordena o vetor criado em ordem decrescente*/
//		cut_hair(id, idcliente, cadeiras[proximo].resposta, cadeiras[proximo].quantidade);
		pthread_mutex_unlock( &(mutex) );       /* libera 'lugaresLivres' */
		sem_post(&customers);     /* um barbeiro está agora pronto para cortar cabelo */
		cut_hair(id, idcliente, cadeiras[proximo].resposta, cadeiras[proximo].quantidade);
		

//		printf("Lugares Livres: %d\n", lugaresLivres);
	}
	pthread_exit(NULL);
}

void *customer(void *arg) {
	//variaveis da controle do cliente
	int id, meulugar, idbarbeiro;
	int time_inicio, time_fim;
	
	/*control variable of cliente - only ends when client gets hair cut*/
	int atendido = FALSE;
	
	//variaveis da operação com mensagem
	int contador, count, number;
	struct timespec ts;
	
	while(atendido == FALSE){
	
		pthread_mutex_lock( &(mutex) );          /* entra na região crítica */
		id = arg;
		customer_arrived(id);
		/*get the incial time*/	
		clock_gettime(CLOCK_MONOTONIC, &ts);
		time_inicio = ts.tv_sec;
		
		if(lugaresLivres > 0) {      /* se não houver cadeiras vazias, saia */
			lugaresLivres = lugaresLivres - 1;		  /* dencrementa o contador de lugares vagos */
			lugarvago = ((lugarvago+1) % CHAIRS);
			meulugar = lugarvago;
			cadeiras[meulugar].id = id;
			
			//Gerando numero randomico de vezes
			srand((time_t)ts.tv_nsec);
			contador = rand()%10;
			if(contador ==0){
				contador = 1;
			}
		
			//preenchendo string para não conter lixo
			strcpy(cadeiras[meulugar].mensagem, "");
		
			//n vezes gera um numero aleatorio e coloca na string
			for(count=0; count < contador; count++){
				number = rand()%1023;
				//função de preencher a mensagem
				numtoa(number, cadeiras[meulugar].mensagem);
			}
		
			//passa quantos vezes foram
			cadeiras[meulugar].quantidade = contador;
			
			pthread_mutex_unlock( &(mutex) );/*Libera a região critica*/
			sem_post(&barbers);/*acorda Barbeiro*/
			sem_wait(&customers);/*espera seu corte*/
			pthread_mutex_lock( &(mutex) );          /* entra na região crítica */
			
			idbarbeiro = cadeiras[meulugar].id;
		
			/*get final time and calculet it*/
			clock_gettime(CLOCK_MONOTONIC, &ts);
			time_fim = ts.tv_sec;
			time_fim = time_fim - time_inicio;
			get_haircut(id, cadeiras[meulugar], time_fim);          /* sentado e sendo servido */
			pthread_mutex_unlock( &(mutex) );       /* libera o acesso a 'lugaresLivres' -> para o barbeiro/outro cliente mecher */
			
//			printf("Lugares Livres: %d\n", lugaresLivres);
			pthread_exit(NULL);
		} else {
			pthread_mutex_unlock( &(mutex) );/*Libera a região critica*/
			/* a barbearia está cheia; não espera */
			giveup_haircut(id);
			atendido = FALSE;
		}
	}
}


/*------------Função para ordenar o vetor int criado-----------*/
void cut_hair(int id, int cliente, int *v, int quantidade) {
	int aux = 0;
	int j, i;
	
	fflush(stdout);
	for(i=0; i < quantidade; i++){
		for(j =0; j < quantidade-1; j++){
			if(v[j] < v[j+1])
			{
				aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;
			}
		}
	}
	sleep(5);
	printf("Barbeiro %d estah cortando o cabelo do Cliente %d!\n", id+1, cliente+1);
}

void customer_arrived(int id) {
	printf("Cliente %d chegou para cortar cabelo!\n", id+1);
	fflush(stdout);
}

/**---------Função para imprimir os dados----------*/
void get_haircut(int id, Book mensagem, int time) {
	
	int count;
	
	printf("Cliente %d estah tendo o cabelo cortado pelo Barbeiro %d!\n", id+1, mensagem.id+1);
	fflush(stdout);
	
	printf("Mensagem: %s\n", mensagem.mensagem);
	fflush(stdout);
	
	printf("Resposta: ");
	fflush(stdout);
	for(count=0; count<mensagem.quantidade; count++){
		printf("%d ", mensagem.resposta[count]);
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
	
	printf("Tempo de execução: %d\n", time);
	fflush(stdout);
}

void giveup_haircut(int id) {
	printf("Cliente %d foi tomar sorvete! (O salao estah muito cheio!)\n", id+1);
	fflush(stdout);
	sleep(2);
}

/*---------Função de conversão de int para string---*/
void numtoa(int i, char* aux){
	
	char num[5];
	
	if(i < 10){
		strcat(aux, "000");
		sprintf(num, "%d", i);
		strcat(aux, num);
	}
	else if(i < 100){
		strcat(aux, "00");
		sprintf(num, "%d", i);
		strcat(aux, num);
	}
	else if(i < 1000){
		strcat(aux, "0");
		sprintf(num, "%d", i);
		strcat(aux, num);
	}
	else{
		strcat(aux, "");
		sprintf(num, "%d", i);
		strcat(aux, num);
		printf("%s\n",aux);
	}
}


/*--------Função de conversão de string para int-----------*/
void stringToInt(char* aux, int vezes, int* v){
	char* point;
	char aux2[5];
	int valor =0, count;	


	for (count = 0; count < vezes; count++){
		valor = count*4;
		point = &aux[valor];
		strncpy(aux2, point, 4);
		v[count] = atoi(aux2);
	}
}
