#include <stdio.h>

int main(){
      
      int vagas, pessoas, entrada, saida, entradaM = 0, saidaM = 0, entradaA = 0, saidaA = 0, i, ver = 0, cont = 0;
      
      scanf("%i %i", &pessoas, &vagas);
      
      while(vagas != 0 && pessoas != 0){      
            
            for(i = 0; i < pessoas; i++){
                  
                  
                  scanf("%i %i", &entrada, &saida);
                  cont++;
                  
                  if(((entrada < saidaM) && (saida >= saidaM)) || ((entrada < saidaA) && (saida >= saidaA)))
                        ver = 1;
                  else{
                        cont--;
                              
                        if(entrada > entradaM)
                              entradaM = entrada;
                              
                        if(saida > saidaM)
                              saidaM = saida;
                  }
                  
                  entradaA = entrada;
                  saidaA = saida;
            }
            
            if(ver == 0 && cont <= vagas)
                  printf("Sim\n");
            else
                  printf("Nao\n");
                  
            cont = 0;
            ver = 0;
            entradaM = 0;
            entradaA = 0;
            saidaA = 0;
            saidaM = 0;
            
            scanf("%i %i", &pessoas, &vagas);
            
      }
      
      return 0;
}