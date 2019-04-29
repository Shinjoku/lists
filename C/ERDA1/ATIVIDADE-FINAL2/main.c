#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "arquivos.h"

/*
Integrante 1 - Nome: José Carlos Clausen Neto				RA: 15055825
Integrante 2 - Nome: Paulo Baraldi Mausbach					RA: 15156490
Integrante 3 - Nome: Laert Espagnoli Neto					RA: 15160823

Resultados obtidos:
Projeto básico: 100% concluído
(Feito) Opcional 1 - Obs: Vale 1 ponto;
(Metade)Opcional 2 - Obs: Vale 1 ponto;
(Feito) Opcional 3 - Obs: Vale 2 pontos;
(Feito) Opcional 4 - Obs: Vale 2 pontos;

*/

void printaMenu(void);

void main(){
	
//Variáveis necessárias para o programa:

	char nome[MAXNOME];
	long long int cpf, tel;
	int escolha;
	no *raiz = NULL;
	FILE *pArquivo = NULL;
	
//Leitura do arquivo Assinantes.txt--------------------------------------------------------------------------

	/*//Inicializa o arquivo;
	pArquivo = fopen("Assinantes.txt", "r");
	
	while(fscanf(pArquivo, "%lld", cpf) != EOF){
		while(cpf != 0){
			cadastraNaArvoreArq(raiz, cpf, pArquivo);
		}
	}
	
	//Fechamento do arquivo;
	fclose(pArquivo);*/
	
//Fim da leitura do arquivo----------------------------------------------------------------------------------	

//Início do menu---------------------------------------------------------------------------------------------
	do{
	
	  printaMenu();
	  scanf("%d", &escolha);
	  
	  
	  switch(escolha)
	  {
	    case 0:								//Finalização do programa;
	    	puts("Finalizando o programa");
	    	break;
	    case 1:								//cadastrar novo;
		    puts("Digite o CPF:");
		    scanf("%lli", &cpf);
		    if(cadastraNaArvore(&raiz, cpf)) puts("ERRO\n");
		    else puts("SUCESSO\n");
	      break;
	      
	    case 2:								//remover cadastro;
		    puts("Digite o CPF que deseja remover:");
		    scanf("%lli", &cpf);
		    rem(&raiz, cpf);
	      break;
	    case 3:								//altera cadastro;
		   	puts("Digite o CPF que se deseja alterar o cadastro:");
		   	scanf("%lli", &cpf);
		   	alteraCadastro(&raiz,&raiz,cpf);
	      break;
	    case 4:								//imprimir um cadastro;
	    	puts("Digite o CPF que deseja imprimir o cadastro:");
		    scanf("%lli", &cpf);
		    if(printaUm(raiz,cpf) != 1) puts("CPF nao identificado");
	       break;
	    case 5:								//imprimir todos cadastros;
	    	emOrdem(raiz);
	      break;
	    case 6:								//Printar em arvore;
	    	printaBonito(raiz, 0);
	    	break;
	    case 7:								//Printa por Telefone;
	    	puts("Digite o Telefone que deseja imprimir os cadastros:");
	    	scanf("%lli", &tel);
	    	printaPorTelefone(raiz, tel);
	    	break;
	    case 8:								//Printa por Nome;
	    	puts("Digite o Nome que deseja imprimir os cadastros:");
	    	__fpurge(stdin);
	    	fgets(nome, MAXNOME, stdin);
	    	printaPorNome(raiz, nome);
	    	break;
	    default: puts("Opcao Invalida");
	  }
	  
	  __fpurge(stdin);
	  puts("\nDigite qualquer tecla para prosseguir");
	  getchar();
	
	}while(escolha != 0);
//Fim do menu-------------------------------------------------------------------------------------------------
	
//Armazenamento de dados no arquivo---------------------------------------------------------------------------

	pArquivo = fopen("Assinantes.txt", "w");
	
	if(!pArquivo){
		puts("Erro na criacao/abertura do arquivo");			//Verifica se a abertura do arquivo aconteceu;
		return 0;
	}

	gravaArquivo(raiz, pArquivo);
	
	//Desaloca a memória alocada para o arquivo, fechando o ponteiro.
	fclose(pArquivo);
	
	puts("Dados armazenados no arquivo Assinantes.txt");
}

void printaMenu(void){
  
  system("clear");
  printf("0)Sair\n");
  printf("1)Cadastrar Novo\n");
  printf("2)Remover Cadastro\n");
  printf("3)Altera Cadastro\n");
  printf("4)Imprimir um cadastro\n");
  printf("5)Imprimir todos cadastros\n");
  printf("6)Imprimir desenho arvore\n");
}