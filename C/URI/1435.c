#include <stdio.h>

int main(){

	int vet[100][100] = {{0},{0}};
	int i, j, constantson = 0, x;
	
	scanf("%i", &x);
	
	while(x != 0){
		
		while(constantson != x){
			for(i = constantson; i < x - constantson; i++){
				for(j = constantson; j < x - constantson; j++){
					vet[i][j] += 1;
				}
			}
			constantson++;
		}
		
		for(i = 0; i < x; i++){
			for(j = 0; j < x; j++){
				printf("%*i", j == 0 ? 3 : 4, vet[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
		for(i = 0; i < x; i++){
			for(j = 0; j < x; j++){
					vet[i][j] = 0;
			}
		}
		
		constantson = 0;
		scanf("%i", &x);
	}
}

//Solved