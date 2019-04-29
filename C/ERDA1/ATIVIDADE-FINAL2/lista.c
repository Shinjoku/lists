#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"

//Entrada: Raiz da lista de telefones e telefone;
//Saídas: 1 para Sucesso;
void insereFimLista(lista **pLista, long long int n){

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
		insereFimLista(&((*pLista)->prox), n);
}						//Working

void excluiLista(lista **pLista) {
  
	lista *aux;

	aux = (*pLista);
	
	if((*pLista)){
		
		//Remoção do nó atual;
		(*pLista) = (*pLista)->prox;
		free(aux);

		excluiLista(pLista);
	}
}											//Working

int existeTel(lista *aux, long long int tel){
	if(!aux) return 0; 
	
	if(tel == aux->tel) return 1;
	else return existeTel(aux->prox, tel);
}								//Working

void removeNo(lista **pLista,long long int tel){
    lista *aux;
    
    if(*pLista == NULL)
    {
      return -1;//nó não encontrado
    }
    else
    {
     if(tel == (*pLista)->tel)
     {
       //remove e remenda lista
       aux = *pLista;
       *pLista = (*pLista)->prox;
       free(aux);
     }
     else
     {
       return removeNo(&(*pLista)->prox,tel);
     }
    }
}							//Working