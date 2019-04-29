#ifndef LISTA_H
#define LISTA_H

//Constantes:
#define MAXNOME 81


//Structs:
typedef struct lista_t{
	
	long long int tel;
	struct lista_t *prox;
}lista;

typedef struct no_t{
	
	char nome[MAXNOME];
	long long int cpf;
	lista *proxtel;
	struct no_t *esq, *dir;
}no;


//Funções:
void insereFimLista(lista **, long long int);									//Entrada: Raiz da lista de telefones e telefone;

void excluiLista(lista **);

int existeTel(lista *, long long int);											

#endif