#include <stdio.h>

void quick(int vet[], int Esq, int Dir){
    
    int i, j;
    int pivo, aux;
    printf("Chamou quick com %d %d \n", Esq, Dir);
    i = Esq; j = Dir;
    pivo = vet[(i+j)/2];
    
    do{
        while (vet[i] < pivo) i++;
        while (vet[j] > pivo) j--;
        if (i <= j){
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        } 
    } while (i < j);
    
    if (Esq < j) quick (vet, Esq, j);
    if (Dir > i) quick (vet, i, Dir);
}

int main(){
    
    int vet[20];
    int i;
    
    for(i = 0; i < 10; i++)
        scanf("%i", &vet[i]);
        
        
    puts("");
    
    for(i = 0; i < 10; i++)
        printf("%i ", vet[i]);
    
    puts("");
    
    quick(vet, 0, 9);
    
    for(i = 0; i < 10; i++)
        printf("%i ", vet[i]);
    
    puts("");
}