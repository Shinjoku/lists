#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE_ALUNOS 49
#define RANGE_DISC	 29

typedef struct {
	long int ra;
	long int disc;
} aluno;

// x => chave | v[] => vetor ordenado | e => Limite inferior (esquerda) | d => Limite Superior (direita)
int binSearch (long int ra, long int disc, aluno v[], int e, int d){
 
	int i = (e + d) / 2;
	
	if (v[i].ra == ra && disc == v[i].disc)
	   return i;
	if (e >= d)
	   return -1; // Não foi encontrado
	else
	    if (v[i].ra < ra)
	       return binSearch(ra, disc, v, i + 1, d);
	    else
	       return binSearch(ra, disc, v, e, i - 1);
}

void bubble(aluno v[], int n) {
	
	int i, j;
	aluno tmp;
	
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (v[i].ra < v[j].ra) {
            	//Swap RA e DISC
				tmp.ra = v[i].ra;
				tmp.disc = v[i].disc;
				v[i].ra = v[j].ra;
				v[i].disc = v[j].disc;
				v[j].ra = tmp.ra;
				v[j].disc = tmp.disc;
            }
        }
    }
}

int getRa(int range){
	
	int number;
	
	number = (rand() % range) + 1;
	
	return number;
}

int main(){
	
	srand(time(NULL));
	
	FILE *file = fopen("Matriculas.txt", "w");
	int i;
	long int ra, disc;
	aluno vet[70];
	
	for(i = 0; i < 70; i++){
		
		bubble(vet, 70);
		
		ra = getRa(RANGE_ALUNOS) + 20170100;
		
		disc = getRa(RANGE_DISC) + 1000;
	
		if(binSearch(ra, disc, vet, 0, 69) == -1){
			vet[i].ra = ra; 
			vet[i].disc = disc;
			fprintf(file, "insert into matricula values ('%li', '%li');\n", ra, disc);
		}else
			i--;
	}
	
	fclose(file);
}