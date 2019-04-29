#include <stdio.h>
#include <stdlib.h>

long double division(int x){

    if(x == 0)
        return 1 / 2;
    else if(x)
        return 1 / (2 + division(x-1));
        
}

int main(){
    
    int i, x;
    
    scanf("%i", &x);

    printf("%.10Lf\n", 1 + division(x));
    
}

// Solved