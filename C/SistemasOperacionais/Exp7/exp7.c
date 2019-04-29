#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int flags_open(char flag[]);

int main(int argc, char **argv){
	
	int i=0, descrit=0, criado=0;
	
	char arquivo[100];
	
	for(i=1; i < argc; i++){
		
		/*testando se é open*/
		if(!strcmp(argv[i], "open")){
			int flag =0, ler_escreve = 0;
			
			/*anda com o i cada passo pra pegar os parametros de open*/
			i++;
			//nome do arquivo pra abrir
			strcpy(arquivo, argv[i]);
			i++;
			
			//flag para como abrir o arquivo
			flag = flags_open(argv[i]);
			//Caso seja criado pra leitura
			if (flag == 64){
				descrit = open(arquivo, flag, S_IRUSR);
				if(descrit < 0){
					printf("Erro ao abrir o arquivo\n");
				}
				else{
					printf("Arquivo %s aberto pra ler\n", arquivo);
					criado=1;
				}
			}
			//Caso seja criado pra escrever
			else if(flag == 65){
				descrit = open(arquivo, flag, S_IWUSR);
				if(descrit < 0){
					printf("Erro ao abrir o arquivo\n");
				}
				else{
					printf("Arquivo %s aberto pra escrever\n", arquivo);
					criado=1;
				}
				printf("descrit: %d\n", descrit);
			}
			//Caso seja criado pra ler e escrever
			else if(flag == 66){
				descrit = open(arquivo, flag, S_IWUSR | S_IRUSR);
				if(descrit < 0){
					printf("Erro ao abrir o arquivo\n");
				}
				else{
					printf("Arquivo %s aberto pra ler e escrever\n", arquivo);
					criado=1;
				}
			}
			//Caso já exista
			else{
				/* Quando o open é chamado, o valor de retorno é um 
				descritor de arquivo, não o caminho*/
				descrit = open(arquivo, flag);
				if(descrit < 0){
					printf("Erro ao abrir o arquivo\n");
				}
				else{
					printf("Arquivo %s aberto\n", arquivo);
					criado=1;
				}
			}
			
		}
		//Fechar Arquivo
		else if(strcmp(argv[i], "close") == 0){
			if(close(descrit) < 0)
			{
				printf("Falha ao fechar o arquivo");
			}
			else{
				printf("vc fechou o arquivo %s\n", arquivo);
			}
			
		}
		//Escrever em um Arquivo
		else if(strcmp(argv[i], "write") == 0){
			i++;
			printf("descrit: %d\n", descrit);			
			if (write(descrit, argv[i], strlen(argv[i])) != strlen(argv[i])) {
				printf("Erro ao escrever no arquivo\n");
			}
			else
			{
				printf("Escrito: %s\n", argv[i]);
			}
				
		}
		//Ler em um arquivo
		else if(strcmp(argv[i], "read") == 0){
			i++;
			int tamanho;
			//precisa de uma string - ponteiro da erro
			char leitura[100];
			tamanho = atoi(argv[i]);
			if(read(descrit, leitura, tamanho) < 0){
				printf("Erro ao ler o arquivo\n");
			}
			else{
				printf("Lido: %s\n", leitura);
			}
		}
		//Sekk em um arquivo
		else if(strcmp(argv[i], "seek") == 0){
			i++;
			int ponto=0;
			ponto = atoi(argv[i]);
			printf("%d\n", ponto);
			if(lseek(descrit, ponto, SEEK_SET) < 0){
				printf("Erro ao dar seek no arquivo");
			}
		}
		//Nada
		else{
			printf("Comando invalido\n");
		}
		
	}
	return 0;
}


int flags_open(char flag[]){

	int retorno_int=0,aux2=0, j=0;
	
	while(j < strlen(flag)){
		if(flag[j] == 'r'){
			if(aux2 ==1){
				retorno_int += O_RDWR;
			}
			else{
				retorno_int += O_RDONLY;
				aux2++;
			}
		}
		else if(flag[j] ==  'w'){
			if(aux2 ==1){
				retorno_int += O_RDWR;
			}
			else{
				retorno_int += O_WRONLY;
				aux2++;
			}
		}
		else if(flag[j] == 'a'){
			retorno_int += O_APPEND;
			return retorno_int;
		}
		else if(flag[j] == 't'){
			retorno_int += O_TRUNC;
			
		}
		else if(flag[j] == 'c'){
			retorno_int += O_CREAT;
		}
		else if(flag[j] == 'e'){
			retorno_int += O_EXCL;
		}
		printf("Flag: %d\n", retorno_int);
		j++;
	}
	return retorno_int;
}