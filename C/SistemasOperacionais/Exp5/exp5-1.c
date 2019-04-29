/* Nomes: José Carlos Clausen Neto
		  Raissa Furlan Davinha
		  Luiz Felipe Zerbetto Masson
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>			//msgget, msgctl
#include <sys/msg.h>			// msgget, msgctl
#include <string.h>				//strcpy, strcat;

// Defines---------------------------------------------
#define MESSAGE_MTYPE	1
#define FALSE			0
#define TRUE			1
#define CHAIRS			7
#define NO_OF_CUSTOMERS 20
#define MQ_ID			2793
#define SIZE			8

// Variáveis Globais-----------------------------------
shared int waiting;
int pid[NO_OF_CUSTOMERS + 1];

// Structs >> ---------------------------------------------

	// Usado para definir o que será transferido pela fila;
typedef struct {
	int id;
	int no_of_numbers;
	char string[SIZE * 4];
	int resposta[SIZE];
} data_t;


	// Usado para transferir as mensagens pela fila;
typedef struct {
	long mtype;
	char mtext[sizeof(data_t)];
} msgbuf_t;

// Protótipos >>
	// Funções auxiliares ---------------------------------

void enter_region(int process);

struct timeval getTime(void);

void numtoa(int i, 000000000000000000000000000char* aux);

void stringToInt(char* aux, int vezes, int* v);

int createQueue(void);

void removeQueue(int queue_id);

int parbegin(void);	

int parend(void);
	
	// Funções Principais---------------------------------
int receive(int queue, int vet);

void send(int queue_id);

void barber(int i);

void customer(int i);

void apreciate_hair(int nClient, int nBarber, int cont, int result, int timer);

int cut_hair(int queue_id);

// Main---------------------------------------------------	
int main(int argc, char *argv[]){
	
	int queue = createQueue();
	
	int waiting = 0;
	int i = 0, rtn;
	
	rtn = parbegin();
	
	if(rtn == 0 && i != 0){
		customer(i);
		sleep(10);
		exit(0);
	} else {
		
		i++;
		barber(i);
		sleep(10);
		exit(0);
	}
	
	parend();
	
	removeQueue(queue);
}

//Funções - Definição >>
	// Funções auxiliares-------------------------------

void enter_region(int process){
	
	int other;
	
	other = 1 - process;
	interested[process] = TRUE;
	turn = process;
	while(turn == process && interested[other] == TRUE) /* Comando Nulo */;
}
	
struct timeval getTime(){
	
	struct timeval timer;
	
	gettimeofday( &timer, NULL);
	
	return timer;
}

void numtoa(int i, char* aux){		// Working
	
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
	}
}

void stringToInt(char* aux, int vezes, int* v){
	
	char* point;
	char aux2[5];
	int valor = 0, count;	


	for(count = 0; count < vezes; count++){
		valor = count * 4;
		point = &aux[valor];
		strncpy(aux2, point, 4);
		v[count] = atoi(aux2);
	}
}

int createQueue(){
	
	key_t key = MQ_ID;
	int queue_id;

	if( (queue_id = msgget(key, IPC_CREAT | 0666)) == -1 ) {
		
		fprintf(stderr,"Impossivel criar a fila de mensagens!\n");
		exit(1);
	}
	return queue_id;
}

void removeQueue(int queue_id){
	
	if( msgctl(queue_id, IPC_RMID,NULL) == -1 ) {
		
		fprintf(stderr,"Impossivel remover a fila!\n");
		exit(1);
	}
}

int parbegin(){
	
	int rtn = 1;
	int i;
	
	for(i = 0; i < NO_OF_CUSTOMERS + 1; i++)
		if(rtn != 0)
			pid[i] = rtn = fork();
		else
			break;
		
	return rtn;
}	

int parend(){
	
	int i;
	
	for(i = 0; i < NO_OF_CUSTOMERS + 1; i++)
		kill(pid[i], SIGTERM);
		
	return 0;
}

	// Funções Principais----------------------------------------
int receive(int queue_id, int* vet){
	
	msgbuf_t message_buffer;
	data_t *data_ptr = (data_t *) (message_buffer.mtext);
	
	
	// Recebendo informações da fila de mensagens
	if( msgrcv(queue_id, (struct msgbuf *) &message_buffer, sizeof(data_t), MESSAGE_MTYPE, 0) == -1 ) {
		printf("Impossivel receber mensagem!\n");
		exit(1);
	}
	
	stringToInt(vet, data->ptr.no_of_numbers, data_ptr->string);
	
	int number = data_ptr->no_of_numbers;
	
	return number;
}

void send(int queue_id, int rtn){
	
	msgbuf_t message_buffer;
	data_t *data_ptr = (data_t *) (message_buffer.mtext);
	
	struct timeval timer;
	
	gettimeofday(&timer, NULL);
	
	char stringAux[SIZE];									// No máximo 8 * 4 casas;
	int nNumbers = ((timer.tv_usec / 47) % 8) + 1;		// Pois são no máximo 8 números;
	
	// Gerando string de inteiros;
	for(i = 0; i < nNumbers; i++){
		gettimeofday(&timer, NULL);
		numtoa(timer.tv_usec, stringAux);
	}
	
	// Passando os dados para o buffer
	message_buffer.mtype = MESSAGE_MTYPE;
	
	data_ptr->no_of_numbers = nNumbers;
	strcpy(data_ptr->string, stringAux);
	
	// Enviando o buffer para a fila de mensagens
	if( msgsnd(queue_id, (struct msgbuf *) &message_buffer, sizeof(data_t), 0) == -1 ) {
		printf("Impossivel enviar mensagem!\n");
		exit(1);
	}
}

void barber(int i){
	/*cliente deve passar ao barbeiro que lhe atende, na mensagem, um string com
um número variável de números inteiros, aleatoriamente definidos entre 2 (dois) e
1023 */
	
	while (1) {
	
		waiting = waiting-1;
		up(&exc_aces);
		cut_hair(i);
		up(barbers);
	}
}

void customer(int i){
	
	start = getTime();
	
	down(&exc_aces);
	
	if (waiting < CHAIRS){
		
		waiting = waiting + 1;
		send(queue_id, rtn);
		down(&barbers);
		end = getTime();
		apreciate_hair(i, ,stop.usec - start.usec);
	}
	else
		up(&exc_aces);
		
}

void apreciate_hair(int nClient, int nBarber, int cont, int result, int timer){
	/*exiba o número do cliente, o número do barbeiro, o conteúdo
do que se quer ordenar, o resultado da ordenação e o tempo de demora para ser
atendido */
	printf("Numero do cliente: %i\n", nClient);
	printf("Numero do barbeiro: %i\n", nBarber);
	printf("Conteudo desordenado: %i\n", cont);
	printf("Conteudo ordenado: %i\n", result);
	printf("Tempo de atendimento %i\n", timer);
}

int cut_hair(int queue_id){
	/*converta o string enviado pelo cliente em vários inteiros. Ordene
esses números, de forma decrescente*/

	int vet[8];
	int number, i;
	
	number = receive(queue_id, vet);
	
	for(i = 0; i < number; i++)
		printf("%d ", vet[i]);

}