#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printa(int *enderecodeBatata){
    
    *enderecodeBatata = 16;
    printf("endereco de enderecodeBatata: %lli\n", enderecodeBatata);
    printf("Valor de batata na função: %lli\n", *enderecodeBatata);
    
}

int main(){
	
	int *batata; // 2
	
	// *batata = batata (dentro da main)

	batata = 55;
	
	printf("endereco de batata na main: %lli\n", &batata);
	printa(&batata); // *enderecodeBatata = &batata
	
	// enderecodeBatata = 2
	// *enderecodeBatata = 55 = 9
	
	printf("valor de batata na main: %i\n", batata);
}

// * ---> Conteúdo de ...
// & ---> Endereço de ...