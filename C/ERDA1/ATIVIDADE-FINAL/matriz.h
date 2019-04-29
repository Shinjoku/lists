#ifndef MATRIZ_H
#define MATRIZ_H
#include "lista.h"

// Constantes:-------
#define MAXCOMANDO 3
#define MAXNOME 51
#define MAXTAMVET 50
//-------------------

// Funções:-------------------------------------
int criarMatriz(char *, int, int, mor *, int);									// Retorna 0 para sucesso e 1 para falha;

float elemento(int, int, char *, mor *, int);

int imprimirMatriz(char *, mor *, int);											// Retorna 0 para sucesso e 1 para falha; 

no* no_retornaPonteiro(int, int, char *, mor *, int);							// Retorna No para sucesso e NULL para falha;

cabeca* cabeca_retornaPonteiro(int, char *, mor *, int);						// Retorna Cabeca para sucesso e NULL para falha;

int adicionarElemento(int, int, char *, mor *, float, int);						

int adicionarLinha(int, char *, mor *, float *, int, int);						// Retorna 0 para sucesso e 1 para falha;

int adicionarColuna(int, char *, mor *, float *, int, int);						// Retorna 0 para sucesso e 1 para falha;

int transporMatriz(char *, char *, mor *, int);									// Retorna 0 para sucesso e 1 para falha;

int somarMatrizes(char *, char *, char *, mor *, int);							// Retorna 0 para sucesso e 1 para falha;

int dividirMatrizes(char *, char *, char *, mor *, int);						// Retorna 0 para sucesso e 1 para falha;

int multiplicarMatrizes(char *, char *, char *, mor *, int);					// Retorna 0 para sucesso e 1 para falha;

int multiplicarMatrizes2(char *, char *, char *, mor *, int);					// Retorna 0 para sucesso e 1 para falha;
	
int destruirMatriz(char *, mor *, int *);										// Retorna 0 para sucesso e 1 para falha;
//----------------------------------------------
#endif