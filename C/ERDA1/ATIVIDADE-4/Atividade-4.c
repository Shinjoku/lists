/*
* Estrutura e Recuperação de Dados A
* Atividade 4 (Lista Ligada)
*
* Para compilar com o DEBUG ativado:
* $ gcc -DDEBUG -g Atividade4.c -o Atividade4
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct no No;
struct no {
	int chave;
	No *prox;
};

// Questao 8 - OK
int quantidade(No *Lista) {

	int cont = 0;

	if (!(Lista))
		return 0;
	else
	{
		while (Lista != NULL){
			cont++;
			Lista = Lista->prox;
		}
	}

	return cont;
}

// Questao 1 - OK
int insereInicio(No **pLista, int n) {

	No *aux;
	aux = (No *)malloc(sizeof(No));
	aux->chave = n;

	if ((*pLista) == NULL)
	{
		aux->prox = NULL;
		(*pLista) = aux;
		return 1;
	}
	else
	{
		aux->prox = (*pLista);
		(*pLista) = aux;
		return 1;
	}

}

// Questao 2 - OK
void insereFim(No **pLista, int n) {

	if (!(*pLista)){
		No *aux = (No *)malloc(sizeof(No));
		if (!aux)
		{
			printf("Heap overflow!");
		}
		else
		{
			(*pLista) = aux;
			(*pLista)->chave = n;
			(*pLista)->prox = NULL;
		}
	}
	else
		insereFim(&((*pLista)->prox), n);
}

// Questao 3 - OK
void insereK(No **pLista, int n, int k) {

		int i = 0;
		if (k > quantidade((*pLista)))
			printf("Posicao invalida!");
		else
		{
			if (k == 0 && (*pLista) != NULL)
				insereInicio(&(*pLista), n);
			else
			{
				while ((*pLista)->prox != NULL && i < k - 1)
				{
					(*pLista) = (*pLista)->prox;
					i++;
				}
				No *aux = (No *)malloc(sizeof(No));

				aux->prox = (*pLista)->prox;
				(*pLista)->prox = aux;
				aux->chave = n;
			}

		}

}

// Questao 4 - OK
void exibePrimeiro(No *Lista) {
	if (!Lista)
		printf("Lista vazia!\n");
	else
		printf("%i\n", Lista->chave);
}

// Questao 5 - OK
void exibeUltimo(No *Lista){
	if (!Lista)
		printf("Lista vazia!");
	else{

		while (Lista->prox != NULL)
		{
			Lista = Lista->prox;
		}
		printf("%i", Lista->chave);
	}

}

// Questao 6 - OK
void exibeK(No *Lista, int k) {

	if (!Lista) printf("Posicao nao existente!");
     else{
     	if (k == 0)
     		printf("%i", Lista->chave);
     	else
     		exibeK((Lista->prox), (k - 1));

     }
}

// Questao 7 - OK
int procuraN(No *Lista, int n) {

	if (!Lista) return 0;

	if (Lista->chave == n){
		return 1;
	}
	else
		procuraN((Lista->prox), n);
}

// Questao 9 - OK
int soma(No *Lista) {

	int cont = 0;



	while (Lista != NULL){
		cont += Lista->chave;
		Lista = Lista->prox;
	}

	return cont;
}

// Questao 10 - OK
float media(No *Lista) {

	float media = soma(Lista) / (float)quantidade(Lista);
	return media;
}

// Questao 11 - OK
void excluiPrimeiro(No **pLista) {

	No *aux = (*pLista);

	if (!(*pLista)) printf("Lista vazia!");

	else{
		(*pLista) = (*pLista)->prox;
		free(aux);
	}
}

// Questao 12 - OK
void excluiUltimo(No **pLista){

	No *aux;


	if (!(*pLista))
		printf("Lista vazia!");

	if (!(*pLista)->prox){
		aux = (*pLista);
		(*pLista) = NULL;
		free(aux);
	}
	else
		excluiUltimo(&(*pLista)->prox);


}

// Questao 13 - OK
void excluiK(No **pLista, int k){

    No *aux = (*pLista), *deletar;


	if (k > quantidade((*pLista)) || k < 0)
		printf("Posicao invalida");
	else
	{
        while(k > 1)
        {
            aux = aux->prox;
            k--;
        }
        deletar = aux->prox;
        aux->prox = aux->prox->prox;
        free(deletar);

	}



}

// Questao 14
void excluiN(No **pLista, int n) {

    No *aux = (*pLista), *deletar;

    while(aux->prox->chave != n)
    {
        aux = aux->prox;
    }
    deletar = aux->prox;
    aux->prox = aux->prox->prox;
    free(deletar);


}

// Cria uma lista vazia
void criaVazia(No **pLista) {
	*pLista = NULL;
}

// DEBUG: Exibe todos os elementos de uma Lista
void exibe(No *Lista) {
	while (Lista != NULL) {
		printf("%d ", Lista->chave);
		Lista = Lista->prox;
	}
}

int main() {
	int opcao = -1, n, k;
	No *Lista;
	criaVazia(&Lista);
	while (opcao != 0) {
		do {
			printf("\n");
			printf("(0) Finalizar o programa\n");
			printf("(1) Inserir elemento no inicio da lista (Q-1)\n");
			printf("(2) Inserir elemento no final da lista (Q-2)\n");
			printf("(3) Inserir elemento na k-esima posicao da lista (Q-3)\n");
			printf("(4) Exibir o primeiro elemento da lista (Q-4)\n");
			printf("(5) Exibir o ultimo elemento da lista (Q-5)\n");
			printf("(6) Exibir o k-esimo elemento da lista (Q-6)\n");
			printf("(7) Procurar um elemento da lista (Q-7)\n");
			printf("(8) Exibir a quantidade de elementos da lista (Q-8)\n");
			printf("(9) Exibir a soma dos valores da lista (Q-9)\n");
			printf("(10) Exibir a media dos valores da lista (Q-10)\n");
			printf("(11) Excluir o primeiro elemento da lista (Q-11)\n");
			printf("(12) Excluir o ultimo elemento da lista (Q-12)\n");
			printf("(13) Excluir o k-esimo elemento da lista (Q-13)\n");
			printf("(14) Excluir um elemento procurado da lista (Q-14)\n");
			printf("Opcao: ");
			scanf("%d", &opcao);
			printf("\n");
			if ((opcao<0) || (opcao>14))
				printf("Opcao invalida!\n");
		} while ((opcao<0) || (opcao>14));

		switch (opcao) {
		case 0:
			printf("Finalizando o programa.\n");
			return 0;
		case 1:
			// Insere um elemento no inicio da lista
			printf("Q-1 Insere um elemento no inicio\n");
			printf("Chave: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &n);
			if (insereInicio(&Lista, n) == 1)
				puts("Lista incluida com sucesso!");
			else
				puts("A operacao falhou!");
			break;
		case 2:
			// Insere um elemento no fim da lista
			printf("Q-2 Insere um elemento no fim\n");
			printf("Chave: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &n);
			insereFim(&Lista, n);
			break;
		case 3:
			// Insere um elemento na k-esima posicao da lista
			printf("Q-3 Insere um elemento na k-esima posicao\n");
			printf("Chave: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &n);
			printf("k: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &k);
			insereK(&Lista, n, k);
			break;
		case 4:
			// Exibe o primeiro elemento da lista
			printf("Q-4 Exibe o primeiro elemento\n");
			printf("Chave: ");
			exibePrimeiro(Lista);
			printf("\n");
			break;
		case 5:
			// Exibe o ultimo elemento da lista
			printf("Q-5 Exibe o ultimo elemento\n");
			printf("Chave: ");
			exibeUltimo(Lista);
			printf("\n");
			break;
		case 6:
			// Exibe o k-esimo elemento da lista
			printf("Q-6 Exibe o k-esimo elemento\n");
			printf("k: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &k);
			printf("Chave: ");
			exibeK(Lista, k);
			printf("\n");
			break;
		case 7:
			// Procura por um elemento da lista
			printf("Q-7 Procura por um elemento\n");
			printf("Chave: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &n);
			if (procuraN(Lista, n))
				printf("Elemento %d encontrado.\n", n);
			else
				printf("Elemento %d não encontrado.\n", n);
			break;
		case 8:
			// Exibe a quantidade de elementos da lista
			printf("Q-8 Exibe a quantidade de elementos\n");
			printf("Quantidade de elementos: %d\n", quantidade(Lista));
			break;
		case 9:
			// Exibe a soma dos elementos da lista
			printf("Q-9 Exibe a soma dos elementos\n");
			printf("Soma: %d\n", soma(Lista));
			break;
		case 10:
			// Exibe a media dos elementos da lista
			printf("Q-10 Exibe a media dos elementos\n");
			printf("Media: %f\n", media(Lista));
			break;
		case 11:
			// Exclui o primeiro elemento da lista
			printf("Q-11 Exclui o primeiro elemento\n");
			excluiPrimeiro(&Lista);
			break;
		case 12:
			// Exclui o ultimo elemento da lista
			printf("Q-12 Exclui o ultimo elemento\n");
			excluiUltimo(&Lista);
			break;
		case 13:
			// Exclui o k-esimo elemento da lista
			printf("Q-13 Exclui o k-esimo elemento\n");
			printf("k: ");
			fflush(stdin);
			// __fpurge(stdin);
			scanf("%d", &k);
			excluiK(&Lista, k);
			break;
		case 14:
			// Exclui um elemento procurado da lista
			printf("Q-14 Exclui um elemento procurado\n");
			printf("Chave: ");
			fflush(stdin);
			//__fpurge(stdin);
			scanf("%d", &n);
			excluiN(&Lista, n);
			break;
		default:
			break;
		}
#ifdef DEBUG
		printf("\n[DEBUG] Lista: ");
		exibe(Lista);
		printf("\n");
#endif
	}
}
