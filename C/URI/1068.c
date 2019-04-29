#include <stdio.h>

int main (){
    
    char string[1001];
    int n, i, abre, fecha;
    
    while(fgets(string, 1001, stdin)){
        
        fflush(stdin);
        
        abre = 0;
        fecha = 0;
        
        i = 0;
        
        while(string[i] != '\0'){
            
            if(string[i] == '(')
                abre++;
            else if (string[i] == ')'){
                
                fecha++;
                
                if(fecha > abre){
                    puts("incorrect");
                    break;
                }
                
            }
            
            
            i++;
        }
        
        if(fecha == abre)
            puts("correct");
        else if(fecha < abre)
            puts("incorrect");
            
        
    }
    
}

// Solved