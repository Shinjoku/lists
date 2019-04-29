#include <stdio.h>

typedef struct batata_t{
    int esq;
    int dir;
} sequencia;


void QuickSort(double vet[][1000], int Esq, int Dir){
	
    int i, j;
    double pivo, aux;
    i = Esq; j = Dir;
    pivo = vet[1][(i+j)/2];
    
    do{
        while (vet[1][i] < pivo) i++;
        while (vet[1][j] > pivo) j--;
        if (i <= j){
            aux = vet[0][i];
            vet[0][i] = vet[0][j];
            vet[0][j] = aux;
            aux = vet[1][i];
            vet[1][i] = vet[1][j];
            vet[1][j] = aux;
            aux = vet[2][i];
            vet[2][i] = vet[2][j];
            vet[2][j] = aux;
            i++;
            j--;
        } 
    } while (i < j);
    
    if (Esq < j) QuickSort (vet, Esq, j);
    if (Dir > i) QuickSort (vet, i, Dir);
}

void QuickSortI(double vet[][1000], int Esq, int Dir){
	
    int i, j;
    double pivo, aux;
    i = Esq; j = Dir;
    pivo = vet[2][(i+j)/2];
    
    do{
        while (vet[2][i] < pivo) i++;
        while (vet[2][j] > pivo) j--;
        if (i <= j){
            aux = vet[0][i];
            vet[0][i] = vet[0][j];
            vet[0][j] = aux;
            aux = vet[1][i];
            vet[1][i] = vet[1][j];
            vet[1][j] = aux;
            aux = vet[2][i];
            vet[2][i] = vet[2][j];
            vet[2][j] = aux;
            i++;
            j--;
        } 
    } while (i < j);
    
    if (Esq < j) QuickSortI (vet, Esq, j);
    if (Dir > i) QuickSortI (vet, i, Dir);
}

sequencia searchSequence(double vet[], int tam){
    
    int i, count = 1;
    sequencia ind;
    
    for(i = 1; i <= tam; i++){
        
        if(vet[i] == vet[i-1])
            count++;
        else {
            
            if(count > 1){
                ind.esq = i - count;
                ind.dir = i - 1;
                break;
            }
            
            count = 1;
            
        }
        
    }
    
    return ind;
}

int main(){
	
	// Variáveis de controle
	
	int testes, encomendas, encomendasW, dia, multa;
	int i, j, k, l;
	int indiceMaiorMedia, nDias;
	double maiorMedia;
	sequencia seq;
	
	// Pega o número de testes
	scanf("%d", &testes);
	
	// Inicialização de vetores
	double diasEMedias[3][1000];
	int result[1000];
	
	for(i = 0; i < testes; i++){
		
		k = 0;
		
		scanf("%d", &encomendas);
		
		for(j = 0; j < encomendas; j++){				// Pega informações e já as armazena nos vetores respectivos
			
			scanf("%d %d", &dia, &multa);
			
			diasEMedias[0][j] = dia;
			diasEMedias[1][j] = (double) multa / dia;
			diasEMedias[2][j] = j;
		}
		
		puts("");
		
		QuickSort(diasEMedias, 0, encomendas-1);
		
		puts("");
			
		encomendasW = encomendas;						// Reutilização do valor de encomendas
		
		while(1){
		    
			if(encomendasW == 0) break; 				// Encerra o programa
			
			// Zera variáveis
			maiorMedia = 0;
			indiceMaiorMedia = 0;
			nDias = 1001;
			
			// Obtenção da maior média, do menor número de dias 
			// e do índice da maior média
			
			for(j = 0; j < encomendas; j++){
				
				if(diasEMedias[0][j] != 0){ // Se houver trabalho
				
					if((diasEMedias[1][j] == maiorMedia && diasEMedias[0][j] < nDias) ||
					
					(diasEMedias[1][j] > maiorMedia) ||
					
					(diasEMedias[1][j] == maiorMedia && diasEMedias[0][j] <= nDias && diasEMedias[2][j] < indiceMaiorMedia)){
						maiorMedia = diasEMedias[1][j];     		// Maior média
						nDias = diasEMedias[0][j];          		// Menor número de dias
						indiceMaiorMedia = (int) diasEMedias[2][j];	// Índice
					}
				}
			}
			
			// Org. array // Inviabiliza valores inválidos
			
			result[k] = indiceMaiorMedia + 1;
			for(j = 0; j < encomendas; j++){
				if(diasEMedias[2][j] == indiceMaiorMedia)
					diasEMedias[0][j] = 0;
			}
			k++;
			
			encomendasW--;
		}
		
		seq = searchSequence(diasEMedias[1], encomendas - 1);
		
		QuickSortI(diasEMedias[2], seq.esq, seq.dir);
		
		for(l = 0; l < seq.dir; l++){
			printf("%d", diasEMedias[l]);
			if(l != k-1)
				printf(" ");
			else
				printf("\n");
		}
		
		for(l = seq.dir + 1; l < k; l++){
			printf("%d", result[l]);
			if(l != k-1)
				printf(" ");
			else
				printf("\n");
		}
	}
	
	return 0;
}