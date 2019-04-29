#include <stdio.h>

int main(){
    
    long long unsigned int x, y;
    
    while(scanf("%llu %llu", &x, &y) != EOF)
        printf("%llu\n", x > y ? x - y : y - x);
    
    return 0;
}

// Solved