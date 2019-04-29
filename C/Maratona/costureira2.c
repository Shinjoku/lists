#include <stdio.h>

int main(){
	
	// Variáveis de controle
	
	int testes, encomendas, encomendasW, dia, multa;
	int i, j, k, l;
	int indiceMaiorMedia, nDias;
	double maiorMedia;
	
	// Pega o número de testes
	scanf("%d", &testes);
	
	// Inicialização de vetores
	double media[1000];
	int dias[1000], result[1000];
	
	for(i = 0; i < testes; i++){
		
		k = 0;
		
		scanf("%d", &encomendas);
		
		for(j = 0; j < encomendas; j++){				// Pega informações e já as armazena nos vetores respectivos
			
			scanf("%d %d", &dia, &multa);
			
			dias[j] = dia;
			media[j] = (double) multa / dia;
		}
		
		puts("");
		
		for(j = 0; j < encomendas; j++)
			printf("Media[%d] = %.2lf\n", j + 1, media[j]);
		
		encomendasW = encomendas;						// Reutilização do valor de encomendas
		
		while(1){
		    
			if(encomendasW == 0) break; 				// Encerra o programa
			
			// Zera variáveis
			maiorMedia = 0;
			indiceMaiorMedia = 0;
			nDias = 1001;
			if(encomendasW != 1)
				if(encomendasW == media[j])
					
			// Obtenção da maior média, do menor número de dias 
			// e do índice da maior média
			
			for(j = 0; j < encomendas; j++){
				
				if(dias[j] != 0){ // Se houver trabalho
				
					if((media[j] == maiorMedia && dias[j] < nDias) || media[j] > maiorMedia){
						maiorMedia = media[j];      // Maior média
						nDias = dias[j];            // Menor número de dias
						indiceMaiorMedia = j;       // Índice
					}
				}
				
				
				
			}
			
			// Org. array // Inviabiliza valores inválidos
			
			result[k] = indiceMaiorMedia + 1;
			dias[indiceMaiorMedia] = 0;
			k++;
			
			encomendasW--;
		}
		
		for(l = 0; l < k; l++){
			printf("%d", result[l]);
			if(l != k-1)
				printf(" ");
			else
				printf("\n");
		}
		
		
	}
		   
	return 0;
}