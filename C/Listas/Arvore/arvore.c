#include <stdio.h>
#include <stdlib.h>

//2 -> 3 -> 4 -> 5

//Endereço de memória;
//Valor;
//Prox;

typedef struct no_t{
    
   int val;
   struct no_t *esq, *dir;
   
} no;

void insere(no **lista, int n){
    
    if(!(*lista)){
        (*lista) = (no *) malloc(sizeof(no));
        (*lista)->val = n;
        (*lista)->esq = NULL;
        (*lista)->dir = NULL;
    } else if(n > (*lista)->val)
        insere(&(*lista)->dir, n);
    else
        insere(&(*lista)->esq, n);
    
}

void print(no *lista){
    
    if(lista){
        print(lista->esq);
        printf("%i ", lista->val);
        print(lista->dir);
    }
    
}

int main(){
    
    int i, n;
    no *lista = NULL;
    
    for(i = 0; i < 10; i++){
        scanf("%i", &n);
        insere(&lista, n);
    }
    
    
    print(lista);
}