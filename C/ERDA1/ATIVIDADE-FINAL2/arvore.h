#ifndef ARVORE_H
#define ARVORE_H
#include "lista.h"


//Funções:
int cadastraNaArvore(no **, long long int);				//Entradas: Raiz da árvore; Saídas: 0 Sucesso || -1 Falha;

no* pegaDados(long long int);							//Entradas: Void; Saídas: Struct árvore com os dados que serão inseridos;

long long int rem2(no **);							            //Entradas: Raiz da árvore; Saídas: Nó que será o substituto do que foi selecionado para ser removido;

void rem(no **, long long int);					        //Entradas: Raiz da árvore e cpf; Saídas: Nada. Executa a ação e atualiza a raiz primária;

int verifica(no *, long long int);	                    //Entradas: Raiz da árvore e CPF; Saídas: 1 se existe || 0 se não existe;

void emOrdem(no *); 								    //Entradas: Raiz; Saídas: Printa os nós;

int printaUm(no *, long long int);						//Entradas: Raiz, CPF; Saídas: Print do assinante;

void printaBonito(no *, int);							//Entradas: Raiz, altura do nó; Saidas: Print da lista em forma de árvore;

void printaPorNome(no *, char *);						//Entradas: Árvore, nome; Saídas: Printa o assinante correspondente;

void printaPorTelefone(no *, long long int);            //Entradas: Árvore, telefone; Saídas: Printa o assinante correspondente;

int alteraCadastro(no **, no **, long long int);		//Entradas: Raiz, Início, cpf; Saídas: -1 se CPF não encontrado; 0 para Sucesso;

void remEspecialAltera(no **, long long int);			//Entradas: Raiz da árvore e o CPF que será removido; Saídas: Nada. Simplesmente executa a ação e atualiza a raiz primária;

no *remEspecialAltera2(no **);							//Entradas: Raiz da árvore; Saídas: Nó que será o substituto do que foi selecionado para ser removido;

int CadastraEspecialAltera(no **, no *);				//Entradas: Início da árvore, raiz; Saídas: 1 para sucesso; 

#endif