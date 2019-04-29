#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "arquivos.h"

//Entradas: Raiz da árvore;
//Saídas: Printa a árvore em ordem de CPF no arquivo "Assinantes.txt";
void gravaArquivo(no *raiz, FILE *pArquivo){
    
    int i = 1;
    
    if(raiz){
    	
        gravaArquivo(raiz->esq, pArquivo);    
        
    	lista *aux = raiz->proxtel;
    	fprintf(pArquivo, "CPF: %lli\n", raiz->cpf);
    	fprintf(pArquivo, "Nome: %s", raiz->nome);
    	
    	fprintf(pArquivo, "Telefones:\n");
    	
    	while(aux){
    		fprintf(pArquivo, "%i: %lli\n", i, aux->tel);
    		i++;
    		aux = aux->prox;
    	}
    	fprintf(pArquivo, "\n");
    	gravaArquivo(raiz->dir, pArquivo);
    }
}								//Working

//Entradas: Void;
//Saídas: Struct árvore com os dados que serão inseridos;
no* pegaDadosArq(long long int cpf, FILE* pArquivo){

	no *dados = NULL;
	dados = (no *) malloc(sizeof(no));
	lista *aux = NULL;
	long long int telefone;
	
	if(!dados){
		
		puts("ERRO\n");
		return NULL;
	}
	
	
	dados->cpf = cpf;
	
	fscanf(pArquivo,"%s", &dados->nome);
	printf("%s", dados->nome);
	
	fscanf(pArquivo, "%lli", &telefone);
	
	
	while(telefone > 0){
		
			insereFimListaArq(&dados->proxtel, telefone);
			fscanf(pArquivo, "%lli", &telefone);
	}
	
	dados->esq = NULL;
	dados->dir = NULL;
	
	return dados;
}							

//Entradas: raiz da árvore;
//Saídas: 0 Sucesso || -1 Falha;
int cadastraNaArvoreArq(no **raiz, long long int cpf, FILE* pArquivo){
	
	if(!(*raiz)){																//Verificar se existe raiz;
	
		*raiz = pegaDadosArq(cpf, pArquivo);											//Aloca um espaço de memória;
		if(!(*raiz)) return -1;														//Verificar se malloc funcionou;
		return 0;
	}
	
	else if(cpf > (*raiz)->cpf)													//Procurar lugar certo para colocar as informações;
			return cadastraNaArvoreArq(&(*raiz)->dir, cpf, pArquivo);						//Se CPF maior -> vai pra direita;
		else																	
			return cadastraNaArvoreArq(&(*raiz)->esq, cpf, pArquivo);						//Se CPF menor -> vai pra esquerda;
			
	return -1;	
}							//Working

//Entrada: Raiz da lista de telefones e telefone;
//Saídas: 1 para Sucesso;
void insereFimListaArq(lista **pLista, long long int n){

	if (!(*pLista)){
		
		lista *aux = (lista *) malloc(sizeof(lista));
		if (!aux)
			printf("Heap overflow!");
			
		else{
			(*pLista) = aux;
			(*pLista)->tel = n;
			(*pLista)->prox = NULL;
		}
	}
	else
		insereFimListaArq(&((*pLista)->prox), n);
}						//Working



