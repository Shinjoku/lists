#include <stdio.h>
#include <stdlib.h>
#define MAX 1001

int main(){
      
      char escolha[MAX], dir[] = {'O', 'N', 'L', 'S'};
      int parada, cord = 1, i;
      
      scanf("%i", &parada);
      
      do{
            
            __fpurge(stdin);
            
            fgets(escolha, MAX, stdin);
            
            for(i = 0; i < parada; i++){
                   
                  if(escolha[i] == 'D'){
                        
                        cord++;
                        if(cord > 3)
                        cord = 0;
                  }
                              
                  if(escolha[i] == 'E'){
                        
                        cord--;
                        if(cord < 0)
                        cord = 3;
                  }
            }

      
            printf("%c\n", dir[cord]);
            
            cord = 1;
            
            scanf("%i", &parada);
            
      }while(parada != 0);
}