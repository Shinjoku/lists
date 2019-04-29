#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	int leds[10] = {6, 2, 5, 5, 4, 5, 6, 3 , 7, 6};
	int i = 0, j, k, qntd;
	int aux = 0;
	char entrada[10];
	char indice;
	
	scanf("%i", &qntd);
	
	for(k = 0; k < qntd; k++){
		
		fflush(stdin);
		scanf("%s", &entrada);
		
		while(entrada[i] != '\0'){
			
			for(j = 0; j < 10; j++){
				
				indice = j + 48;
				
				if(entrada[i] == indice)
					aux += leds[j];
			}
			
			i++;
		}
		
		printf("%i leds\n", aux);
		aux = 0;
		i = 0;
		fflush(stdin);
	}
}


//Solved