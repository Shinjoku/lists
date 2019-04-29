//#define PROTECT


/*
 * Includes Necessarios
 */
#include <errno.h>				/* errno and error codes */
#include <sys/time.h>			/* for gettimeofday() */
#include <stdio.h>				/* for printf() */
#include <unistd.h>				/* for fork() */
#include <sys/types.h>			/* for wait() */
#include <sys/wait.h>			/* for wait() */
#include <signal.h>				/* for kill(), sigsuspend(), others */
#include <sys/ipc.h>			/* for all IPC function calls */
#include <sys/shm.h>			/* for shmget(), shmat(), shmctl() */
#include <sys/sem.h>			/* for semget(), semop(), semctl() */
#include <stdlib.h>


/*
 * Constantes Necessarias
 */
#define SEM_KEY_P		0x2643
#define SEM_KEY_C		0x2202
#define SEM_KEY_B		0x2403
#define C_SHM_KEY		0x1532
#define G_SHM_KEY		0x2041
#define B_SHM_KEY		0x2342
#define NO_OF_CHILDREN	8
#define Max_Size		65		// 64 caracters do vetor global g_letters_and_numbers + \0


/*
 * As seguintes variaveis globais contem informacao importante. A variavel
 * p_sem_id e g_shm_id contem as identificacoes IPC para o semaforo e para
 * o segmento de memoria compartilhada que sao usados pelo programa. A variavel
 * g_shm_addr e um ponteiro inteiro que aponta para o segmento de memoria
 * compartilhada que contera o indice inteiro da matriz de caracteres que contem
 * o alfabeto que sera exibido.
*/

//estrutura do buffer
typedef struct VS {
	char vector [Max_Size];
} shv;

//Semaforo produtor
int	p_sem_id;

//Semaforo consumidor
int c_sem_id;

//Semaforo Buffer
int buffer_sem_id;

//indice produtor
int	g_shm_id;
int	*g_shm_addr;

//indice consumidor
int c_shm_id;
int *c_shm_addr;


//Buffer compartilhado
shv *shm_vec_addr;
int shm_vec_id;


/*
 * As seguintes duas estruturas contem a informacao necessaria para controlar
 * semaforos em relacao a "fecharem", se nao permitem acesso, ou 
 * "abrirem", se permitirem acesso. As estruturas sao incializadas ao inicio
 * do programa principal e usadas na rotina PrintAlphabet(). Como elas sao
 * inicializadas no programa principal, antes da criacao dos processos filhos,
 * elas podem ser usadas nesses processos sem a necessidade de nova associacao
 * ou mudancas.
*/
struct sembuf	g_sem_op1[1];
struct sembuf	g_sem_op2[1];

/*
 * O seguinte vetor de caracteres contem o alfabeto que constituira o string
 * que sera exibido.
*/
char g_letters_and_numbers[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 1234567890";

/*
 * Funcoes
 */

void Producer(int no_son);

void Consume(int no_son);

/*
 * Programa Principal
 */
int main( int argc, char *argv[] )
{
	/*
	 * Variaveis necessarias
	 */
	int rtn;
	int count;
	int i;
	  
	
	/*
	 * Para armazenar os ids dos processos filhos, permitindo o posterior
	 * uso do comando kill
	 */
	int pid[NO_OF_CHILDREN];

	/*
	 * Construindo a estrutura de controle do semaforo
	 */
	// Para desbloquear:
	g_sem_op1[0].sem_num   =  0;
	g_sem_op1[0].sem_op    =  1;
	g_sem_op1[0].sem_flg   =  0;
	
	// Para bloquear:
	g_sem_op2[0].sem_num =  0;
	g_sem_op2[0].sem_op  = -1;
	g_sem_op2[0].sem_flg =  0;

// Criação Semaforos --------------------------------------------------------------------------
	/*
	 * Criando o semaforo produtor
	 */	
	if( ( p_sem_id = semget( SEM_KEY_P, 1, IPC_CREAT | 0666 ) ) == -1 ) {
		fprintf(stderr,"chamada a semget() falhou, impossivel criar o conjunto de semaforos!");
		exit(1);
	}
	//Abrindo semaforo produtor
	if( semop( p_sem_id, g_sem_op1, 1 ) == -1 ) {
		fprintf(stderr,"chamada semop() falhou, impossivel inicializar o semaforo!");
		exit(1);
	}
	
	
	/*
	 * Criando o semaforo consumidor
	 */	
	if( ( c_sem_id = semget( SEM_KEY_C, 1, IPC_CREAT | 0666 ) ) == -1 ) {
		fprintf(stderr,"chamada a semget() falhou, impossivel criar o conjunto de semaforos!");
		exit(1);
	}
	//Semaforo consumidor já esta fechado então não precisa do 2 if
	
	
	/*
	 * Criando o semaforo buffer
	 */	
	if( ( buffer_sem_id = semget( SEM_KEY_B, 1, IPC_CREAT | 0666 ) ) == -1 ) {
		fprintf(stderr,"chamada a semget() falhou, impossivel criar o conjunto de semaforos!");
		exit(1);
	}
	//Abrindo Semaforo buffer
	if( semop( buffer_sem_id, g_sem_op1, 1 ) == -1 ) {
		fprintf(stderr,"chamada semop() falhou, impossivel inicializar o semaforo!");
		exit(1);
	}


// Criaçao Segmentos de Memória -------------------------------------------------------------
	/*
	 * Criando o segmento de memoria compartilhada = Indice produtor
	 */
	if( (g_shm_id = shmget( G_SHM_KEY, sizeof(int), IPC_CREAT | 0666)) == -1 ) {
		fprintf(stderr,"Impossivel criar o segmento de memoria compartilhada1!\n");
		exit(1);
	}

	if( (g_shm_addr = (int *) shmat(g_shm_id, NULL, 0)) == (int *) -1 ) {
		fprintf(stderr,"Impossivel associar o segmento de memoria compartilhada!\n");
		exit(1);
	}
		//colocando o indice com valor da 1 posição
	*g_shm_addr = 0;
	
	/*
	 * Criando o segmento de memoria compartilhada = Indice cosumidor
	 */
	if( (c_shm_id = shmget( C_SHM_KEY, sizeof(int), IPC_CREAT | 0666)) == -1 ) {
		fprintf(stderr,"Impossivel criar o segmento de memoria compartilhada2!\n");
		exit(1);
	}

	if( (c_shm_addr = (int *) shmat(c_shm_id, NULL, 0)) == (int *) -1 ) {
		fprintf(stderr,"Impossivel associar o segmento de memoria compartilhada!\n");
		exit(1);
	}
	//colocando o indice com valor da 1 posição
	*c_shm_addr = 0;
	
	
	/*
	 * Criando o segmento de memoria buffer
	 */
	if( (shm_vec_id = shmget( B_SHM_KEY, sizeof(shv), IPC_CREAT | 0666)) == -1 ) {
		fprintf(stderr,"Impossivel criar o segmento de memoria compartilhada3!\n");
		exit(1);
	}

	if( (shm_vec_addr = (shv *) shmat(shm_vec_id, NULL, 0)) == (shv *) -1 ) {
		fprintf(stderr,"Impossivel associar o segmento de memoria compartilhada!\n");
		exit(1);
	}
	
	//preenchendo o buffer com nulo
	for(i =0; i < Max_Size; i++){
		shm_vec_addr->vector[i] = '#';
	}
	
	
	
	   /*
		* Criando os filhos
		*/
	   rtn = 1;
	   for( count = 0; count < NO_OF_CHILDREN; count++ ) {
			   if( rtn != 0 ) {
					pid[count] = rtn = fork();
			   } else {
					break;
			   }
	   }

	   /*
		* Verificando o valor retornado para determinar se o processo e 
		* pai ou filho 
		*/
		
	   if( rtn == 0 ) {
				/*
				 * Eu sou um filho
				 */
		if(count <= 4){
			printf("Filho %i comecou como produtor ...\n", count);
			fflush(stdout);
			Producer(count);
		}
		else{
			printf("Filho %i comecou como consumidor...\n", count);
			fflush(stdout);
			Consume(count);
		}

		} else {
			usleep(2000); //0.002 Segundos;

			/*
			 * Matando os filhos 
			 */
			for(i = 0; i < NO_OF_CHILDREN; i++){
				kill(pid[i], SIGKILL);
			}

			/*
			 * Removendo as memorias compartilhadas ------------------------------------------------
			 */
			if( shmctl(g_shm_id, IPC_RMID, NULL) != 0 ) {
				fprintf(stderr,"Impossivel remover o segmento de memoria compartilhada!\n");
				exit(1);
			}
			
			if( shmctl(shm_vec_id, IPC_RMID, NULL) != 0 ) {
				fprintf(stderr,"Impossivel remover o segmento de memoria compartilhada!\n");
				exit(1);
			}
			
			if( shmctl(c_shm_id, IPC_RMID, NULL) != 0 ) {
				fprintf(stderr,"Impossivel remover o segmento de memoria compartilhada!\n");
				exit(1);
			}

			/*
			 * Removendo os semaforos --------------------------------------------------------------
			 */
			if( semctl( p_sem_id, 0, IPC_RMID, 0) != 0 ) {
				fprintf(stderr,"Impossivel remover o conjunto de semaforos!\n");
				exit(1);
			}
			
			if( semctl( c_sem_id, 0, IPC_RMID, 0) != 0 ) {
				fprintf(stderr,"Impossivel remover o conjunto de semaforos!\n");
				exit(1);
			}
			
			if( semctl( buffer_sem_id, 0, IPC_RMID, 0) != 0 ) {
				fprintf(stderr,"Impossivel remover o conjunto de semaforos!\n");
				exit(1);
			}



			exit(0);
		}
}


/*
 * Esta rotina realiza a exibicao de caracteres. Nela e calculado um numero
 * pseudo-randomico entre 1 e 3 para determinar o numero de caracteres a exibir.
 * Se a protecao esta estabelecida, a rotina entao consegue o recurso. Em
 * seguida, PrintChars() acessa o indice com seu valor corrente a partir da
 * memoria compartilhada. A rotina entra em loop, exibindo o numero aleatorio de
 * caracteres. Finalmente, a rotina incrementa o indice, conforme o necessario,
 * e libera o recurso, se for o caso.
*/
void Producer(int no_son)
{
	struct timeval tv;
	int number;

//Variáveis:
	int tmp_index;
	int i, j = 0;
	
	/*
	 * Este tempo permite que todos os filhos sejam inciados
	 */
	usleep(600);

	/*
	 * Entrando no loop principal
	 */
	while(1){
		/*
		 * Conseguindo o tempo corrente, os microsegundos desse tempo
		 * sao usados como um numero pseudo-randomico. Em seguida,
		 * calcula o numero randomico atraves de um algoritmo simples
		 */
		if( gettimeofday( &tv, NULL ) == -1 ) {
			fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
			exit(1);
		}
		number = ((tv.tv_usec / 47) % 5) + 1;
		
/*
 * O #ifdef PROTECT inclui este pedaco de codigo se a macro
 * PROTECT estiver definida. Para sua definicao, retire o comentario
 * que a acompanha. semop() e chamada para fechar o semaforo.
*/
		
		
		
		
//----------------------Produtor------------------//
#ifdef PROTECT //Producer
	//Travando semáforo do produtor
		if( semop( p_sem_id, g_sem_op2, 1 ) == -1 ) {
			fprintf(stderr,"chamada semop() falhou, impossivel fechar o recurso!");
			exit(1);
		}
#endif
		
		
		/*
		 * Lendo o indice do segmento de memoria do produtor
		 */
		tmp_index = *g_shm_addr;
		
		
// Travando semaforo do buffer
#ifdef PROTECT //Buffer
		if(semop( buffer_sem_id, g_sem_op2, 1) == -1) {
			fprintf(stderr,"chamada semop() falhou, impossivel fechar o recurso!");
			exit(1);
		}
		
#endif		
	
	fflush(stdout);
	printf("Filho %i------------\n", no_son);
	fflush(stdout);
	printf("Caracteres produzidos: ");
	fflush(stdout);
	// Produzindo:
		for(i = 0; i < number; i++) {
		// verifica se pode preencher
			if( (tmp_index + i < Max_Size)){
			//Tratamento se buffer maior que a variavel global das letras
				if(tmp_index + i > sizeof(g_letters_and_numbers)){
					shm_vec_addr->vector[tmp_index + i] = g_letters_and_numbers[(tmp_index + i) - sizeof(g_letters_and_numbers)];
					printf("%c", shm_vec_addr->vector[tmp_index + i]);
				}
				else{
					if(shm_vec_addr->vector[tmp_index + i] == '#'){
						shm_vec_addr->vector[tmp_index + i] = g_letters_and_numbers[tmp_index + i];
						printf("%c", shm_vec_addr->vector[tmp_index + i]);
						usleep(1);
					}
				}
			}
		}
		
		puts("");
		//("Buffer: (P) %s\n", shm_vec_addr->vector);
		fflush(stdout);
		printf("Indice: %i, indice global produtor: %i\n", tmp_index + i, *g_shm_addr);
		fflush(stdout);
		printf("--------------------\n");
		
		j = 0;
// Liberando semaforo do buffer
#ifdef PROTECT //Buffer
		if(semop( buffer_sem_id, g_sem_op1, 1) == -1) {      		
			fprintf(stderr,"chamada semop() falhou, impossivel liberar o recurso!");
			exit(1);
		}
#endif	
		
		/*
		 * Atualizando o indice na memoria compartilhada
		 */
		*g_shm_addr = tmp_index + i;

//Caso o buffer chegue no fim - printar e voltar ao inicio
		if(tmp_index + i > Max_Size) {
			fprintf(stderr,"\n");

			*g_shm_addr = 0;
		}
#ifdef PROTECT //Consumer
		//liberando semaforo do consumidor
		if(semop( c_sem_id, g_sem_op1, 1) == -1) {      		
			fprintf(stderr,"chamada semop() falhou, impossivel liberar o recurso!");
			exit(1);
		}
#endif
	}
}




//-------------------Consumidor-------------------//
void Consume(int no_son){

	struct timeval tv;
	int number;

	int tmp_index;
	int i, j = 0;

	/*
	 * Este tempo permite que todos os filhos sejam inciados
	 */
	usleep(600);

	/*
	 * Entrando no loop principal
	 */
	while(1){
		/*
		 * Conseguindo o tempo corrente, os microsegundos desse tempo
		 * sao usados como um numero pseudo-randomico. Em seguida,
		 * calcula o numero randomico atraves de um algoritmo simples
		 */
		if( gettimeofday(&tv, NULL ) == -1) {
			fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
			exit(1);
		}
		number = ((tv.tv_usec / 47) % 5) + 1;
	
		//printf("Antes C: %s\n", shm_vec_addr->vector);
#ifdef PROTECT //Consumer
		//Travando semaforo do consumidor
		if(semop(c_sem_id, g_sem_op2, 1) == -1) {
			fprintf(stderr,"chamada semop() falhou, impossivel fechar o recurso!");
			exit(1);
		}
#endif


		/*
		 * Lendo o indice do segmento de memoria do consumidor
		 */
		tmp_index = *c_shm_addr;
		
		
#ifdef PROTECT //Buffer
// Travando semaforo do buffer
		if( semop( buffer_sem_id, g_sem_op2, 1 ) == -1) {
			fprintf(stderr,"chamada semop() falhou, impossivel fechar o recurso!");
			exit(1);
		}
#endif	

		printf("Filho %i------------\n", no_son);
		fflush(stdout);
		printf("Caracteres consumidos: ");
		for( i = 0; i < number; i++ ) {
		// verifica se pode remover do buffer
			if( (tmp_index + i < Max_Size)  ){
				if(tmp_index + i < *g_shm_addr){
					printf("%c", shm_vec_addr->vector[tmp_index + i]);
					fflush(stdout);
					shm_vec_addr->vector[tmp_index + i] = '#';
					usleep(1);
				} else
					break;
			}
		}
		puts("");
		

		printf("tmp_index: %i, indice global: %i\n", tmp_index+i, *c_shm_addr);
		fflush(stdout);
		printf("--------------------\n");

   
#ifdef PROTECT //Buffer
		//liberando semaforo do buffer
		if(semop(buffer_sem_id, g_sem_op1, 1) == -1 ) {      		
			fprintf(stderr,"chamada semop() falhou, impossivel liberar o recurso!");
			exit(1);
		}
#endif	
		/*
			* Repita o numero especificado de vezes, esteja certo de nao
			* ultrapassar os limites do vetor, o comando if garante isso
		 */

		/*
		 * Atualizando o indice na memoria consumidor
		 */

		*c_shm_addr = tmp_index + i;

		/*
			 * Se o indice e maior que o tamanho do alfabeto, exibe um
			 * caractere return para iniciar a linha seguinte e coloca
			 * zero no indice
		 */
		if(tmp_index + i > Max_Size) {
			fprintf(stderr,"\n");
			printf("Buffer: (C) %s\n", shm_vec_addr->vector);
			*c_shm_addr = 0;
		}

		/*
		 * Liberando o recurso se a macro PROTECT estiver definida
		 */

#ifdef PROTECT
		//liberando semaforo do produtor
		if(semop(p_sem_id, g_sem_op1, 1) == -1) {      		
			fprintf(stderr,"chamada semop() falhou, impossivel liberar o recurso!");
			exit(1);
		}
#endif
	}
}
