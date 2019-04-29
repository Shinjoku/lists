#include <stdio.h>

int main(){
 
    int n, esc, i, qtd;
    float aux = 0;
    
    scanf("%i", &n);
    
    for(i = 0; i < n; i++){
        
        scanf("%i %i", &esc, &qtd);
        
        if(esc == 1001)
            aux += 1.50 * qtd;
        else if(esc == 1002)
            aux += 2.50 * qtd;
        else if(esc == 1003)
            aux += 3.50 * qtd;
        else if(esc == 1004)
            aux += 4.50 * qtd;
        else if(esc == 1005)
            aux += 5.50 * qtd;
    }
    
    printf("%.2f\n", aux);
}

// Solved