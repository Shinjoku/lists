#include <stdio.h>
#include <math.h>

int main(){
    
    int res, hora, mais, menos;

    res = hora + mais + menos;  
    
    if(res >= 24)
        res -= 24;
    else if (res < 0)
        res += 24;
        
    printf("%i\n", res);
    
}


