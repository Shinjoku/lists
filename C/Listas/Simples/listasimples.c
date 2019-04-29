#include <stdio.h>
#include <stdlib.h>

//2 -> 3 -> 4 -> 5

//Endereço de memória;
//Valor;
//Prox;

typedef struct no_t{
    
   int val;
   struct no_t *prox;
}no;

void insereInicio(no **lista){
    
    no *aux = (*lista);
    
    (*lista) = (no *) malloc(sizeof(no));
    scanf("%i", &(*lista)->val);
    (*lista)->prox = aux;
    
}

void insereFinal(no **lista){
    
    if(!(*lista)){
        
        (*lista) = (no *) malloc(sizeof(no));
        scanf("%i", &(*lista)->val);
        (*lista)->prox = NULL;
    }
    else
        insereFinal(&(*lista)->prox);
}

void insereOrdenado(no **lista, int n){
    
    if(!(*lista)){
        
        (*lista) = (no *) malloc(sizeof(no));
        (*lista)->val = n;
        (*lista)->prox = NULL;
        
    } else if(n <= (*lista)->val){ // GENE AWL
        
        no *aux = (no *) malloc(sizeof(no));
        
        aux->prox = (*lista);       // o antigo início vira prox do antecessor
        (*lista) = aux;             // o novo início é marcado pelo antecessor
        (*lista)->val = n;
        
    } else
        insereOrdenado(&(*lista)->prox, n);
    
}

void removerUltimo(no **lista){
    
    if(!(*lista)->prox){
        no *aux = (*lista);
        (*lista) = NULL;
        free(aux);
    } else
        removerUltimo(&(*lista)->prox);
    
}

void removerPrimeiro(no **lista){
    
    no *aux = (*lista);
    (*lista) = (*lista)->prox;
    free(aux);
    
}

void removerN(no **lista, int n){
    if((*lista)->val == n){
        removerPrimeiro(&(*lista));
    } else {
        removerN(&(*lista)->prox, n);
    }
}

void print(no *lista){
    
    if(lista){
        printf("%i ", lista->val);
        print(lista->prox);
    }
    
}

int main(){
    
    int i, n;
    no *lista = NULL;
    
    for(i = 0; i < 5; i++){
        scanf("%i", &n);
        insereOrdenado(&lista, n);
    }
    
    removerN(&lista, 3);
    
    print(lista);
}