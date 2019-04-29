#include <stdio.h>
#include <stdlib.h>
#define MAX 3000

int main(){

      int vet[MAX], ver = 1, aux, i, j, n;
      
      scanf("%i", &n);

      for(i = 0; i < n; i++){
            
            scanf("%i", &vet[i]);
            
            if(vet[i] < 0)
                  ver = 0;
      }
      
      if(ver == 1){
      
            for(i = 0; i < n; i++){
                              
                for(j = 0; j < n -1; j++){
                      
                      if(vet[j] > vet[j+1]){
                            
                            aux = vet[j+1];
                            vet[j+1] = vet[j];
                            vet[j] = aux;
                      }
                  }
            }
            
            for(i = 0; i < n-1; i++){
                  
                  if(vet[i] != (vet[i+1] - 1)){
                        
                        ver = 0;
                        break;
                  }
            }
            
            if(ver == 1)
                  printf("Jolly\n");
            else
                  printf("Nao Jolly\n");
      }
      else
            printf("Nao Jolly");
      
}