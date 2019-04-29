#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE_ALUNOS 49
#define RANGE_DISC	 29

int getRand(int range){
	
	int number;

	number = (rand() % range);

	return number;
}

int main(){
	
	srand(time(NULL));
	
	FILE *file = fopen("Cursadas.txt", "w");
	int i;
	long int ra, disc, sem, ano, status, freq, nota;
	
	for(i = 0; i < 80; i++){
		
		ra = (getRand(RANGE_ALUNOS) + 1) + 20170100;
		disc = (getRand(RANGE_DISC) + 1) + 1000;
		sem = (getRand(2) + 1) * 3;
		ano = getRand(15) + 2000;
		status = getRand(2);
		freq = getRand(100);
		nota = getRand(10);
		
		
		fprintf(file, "insert into cursadas values ('%li', '%li', to_date('0%ld/%ld', 'mm/yyyy'), %ld, %ld, %ld); \n", ra, disc, sem, ano, nota, freq, status);
	}
	
	fclose(file);
}