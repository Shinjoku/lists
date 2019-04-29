/*******************************************************************************
* Este programa esta baseado no segundo experimento do curso sobre tempo real 
* do Laboratorio Embry-Riddle
* 
* Seguem os comentarios originais:
*
* Experiment #2: Multi-Tasking, Measuring Drift
*
*    Programmer: Eric Sorton
*          Date: 01/27/97
*           For: MSE599, Special Topics Class
*
*       Purpose: When a basic sleep call is used to determine the precise time
*                when an action will occur the problem of drift occurs. 
*                The measurement of time is imprecise.  Similarly, the time in 
*                which the sleep call returns is imprecise.  Over time, this 
*                will cause the ocurrence of time to drift.  Just as if a clock 
*                loses 1 second every day, over one day, it is significant, but 
*                over a year, it loses 365 seconds, which is over 6 minutes.  
*                This is an example of drift.
*
*       Proposito: Quando uma chamada básica sleep eh usada para determinar o
*                instante exato em que alguma acao vai ocorrer, ocorre o problema
*                do desvio. A medicao de tempo eh imprecisa. Similarmente, o tempo
*                que demora o retorno da chamada sleep tambem eh impreciso. Ao
*                longo do tempo, isto ocasionara um desvio de tempo. Algo como se
*                um relogio perdesse um segundo a cada dia. Ao longo de um dia, 
*                essa diferenca e insignificante, mas, ao longo de um ano, sao 
*                perdidos 365 segundos, o que e superior a 6 minutos. Este e um
*                exemplo de desvio.
*
*******************************************************************************/

/*
 * Includes Necessarios, verifique se as bibliotecas no diretorio sys/ estao
 * lah. Caso nao estejam, verifique onde estao e altere o include
 */

#include <sys/time.h>		/* for gettimeofday() */
#include <unistd.h>	    	/* for gettimeofday() and fork() */
#include <stdio.h>	    	/* for printf() */
#include <sys/types.h>		/* for wait() */
#include <sys/wait.h>		/* for wait() */
#include <stdlib.h>
#include <signal.h>

/*
 * Pergunta 1: o que o compilador gcc faz com o arquivo .h, cujo nome aparece após o include?
 */

/*
 * Pergunta 2: apresentar (parcialmente) e explicar o que há em <stdio.h>
 */

/*
 * Pergunta 3: qual eh a funcao da diretiva include (linha que começa com #), com relação ao compilador?
 */

/*
 * NO_OF_ITERATIONS e o numero de vezes que vai se repetir o loop existente
 * em cada futuro processo filho. 
 */

#define NO_OF_ITERATIONS	1000

/*
 * NO_OF_CHILDREN eh o numero de filhos a serem criados, cada qual responsavel
 * pela medida do desvio. 
 */

#define NO_OF_CHILDREN	5

/*
 * SLEEP_TIME corresponde a quantidade de tempo para ficar bloqueado.
 */

#define SLEEP_TIME 1000

/*
 * MICRO_PER_SECOND define o numero de microsegundos em um segundo
 */

#define MICRO_PER_SECOND	1000000

/*USLEEP_TIME define o número de segundos que serão usados na chamada do comando usleep
*/
#define USLEEP_TIME	1400
/*
 * Programa Principal. Contem tanto o codigo para o processo pai como
 * o codigo dos futuros filhos
 */

int main( int argc, char *argv[] )
{
/*
 * Pergunta 4: o que são e para que servem argc e argv? Não esqueca de
 * considerar o * antes de argv.
 */
	/*
	 * start_time e stop_time conterao o valor de tempo antes e depois
	 * que as trocas de contexto comecem
		 */

	struct timeval start_time;
	struct timeval stop_time;

	  /*
	   * Outras variaveis importantes
	   */

	  float drift;
	  int count;
	  int child_no;
	  int rtn;
	  int pid[NO_OF_CHILDREN];

	/*
	 * Criacao dos processos filhos
	 */

	rtn = 1;
	for( count = 0; count < NO_OF_CHILDREN; count++) {
		if( rtn != 0 ) {
			rtn = fork();
			pid[count] = rtn;
		} else {
			break;
		}
	}


	/*
	 * Verifica-se rtn para determinar se o processo eh pai ou filho
	 */

	if( rtn == 0 ) {

	/*
		 * Portanto, sou filho. Faco coisas de filho. 
		 */
		 
		 
		 char nFilho[32];
		 char nMicSec[32];	 

		 sprintf(nFilho, "%d", count);
		 sprintf(nMicSec, "%d",  USLEEP_TIME);
		 //itoa(count, q, 10);
		 
		 char *args[4] = {"./progexec", nFilho, nMicSec, NULL};
		 
		//execl("./progexec", &args, (char *) NULL);
		execv(args[0], args);
		
		//exit(0);
	} else {
		/*
		 * Sou pai, aguardo o termino dos filhos
		 */
		usleep(1000);
		int i;
		for(i = 0; i < NO_OF_CHILDREN; i++){
			kill(pid[i], SIGKILL);
			printf("Processo %d foi Terminado.\n", pid[i]);	
		}	

		for( count = 0; count < NO_OF_CHILDREN; count++ ) {
			wait(NULL);
		}
	}

	exit(0);
}
