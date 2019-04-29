#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct Tipo_Alunos{
    char nome[MAX];
    int ra;
}aln;

typedef struct Tipo_Disciplinas{
    char nome[MAX];
    int codigo;
}dsp;

typedef struct Tipo_prof{
    
    int ru;
    char nomeProf[MAX];
}prof;

typedef struct Tipo_Matricula{
    
    aln aluno;
    dsp disciplina;
}matricula;

typedef struct Tipo_Vinculo{
    
    prof professor;
    dsp disciplina;
}vinc;

void cadastraAluno(aln vetAluno[], int *nda){
    
    puts("Digite o nome do aluno:");
    fflush(stdin);
    __fpurge(stdin);
    fgets(vetAluno[*nda].nome, MAX, stdin);

    puts("Digite o ra do aluno:");
    scanf("%i", &vetAluno[*nda].ra);

    *nda += 1;
}

void cadastraDisciplina(dsp vetdis[], int *ndd){

    fflush(stdin);
    __fpurge(stdin);
    puts("Digite o nome da disciplina:");
    fgets(vetdis[*ndd].nome, MAX, stdin);

    puts("Digite o código da disciplina:");
    scanf("%i", &vetdis[*ndd].codigo);

    *ndd += 1;
}

void cadastraProf(aln vetProf[], int *ndp){
    
    puts("Digite o nome do professor:");
    fflush(stdin);
    __fpurge(stdin);
    fgets(vetProf[*ndp].nome, MAX, stdin);

    puts("Digite o ra do aluno:");
    scanf("%i", &vetProf[*ndp].ra);

    *ndp += 1;
}

void fazerMatriculaAlunos (matricula vmat[], int *ndm, aln vetalunos[], int nda, dsp vetdis[], int ndd){
    
    int raAux, codigoAux;       //Auxiliares
    int verA = 0, verD = 0;     //Verificadores
    int i, j;                   //Controladores
    char escolha;               //Controlador do loop primário

    do{
        do{
            
            puts("Digite o RA do aluno que deseja cadastrar:");
            scanf("%i", &raAux);
            
            puts("Digite o codigo da disciplina que deseja cadastrar o aluno:");
            scanf("%i", &codigoAux);
            
            for(i = 0; i < nda; i++){
                
                if(raAux == vetalunos[i].ra){
                    verA = 1;
                    
                    for(j = 0; j < ndd; j++){
                        
                        if(codigoAux == vetdis[j].codigo){
                            
                            verD = 1;
                            
                            strcpy(vmat[*ndm].aluno.nome, vetalunos[i].nome);
                            vmat[*ndm].aluno.ra = vetalunos[i].ra;
                            vmat[*ndm].disciplina.codigo = vetdis[j].codigo;
                            strcpy(vmat[*ndm].disciplina.nome, vetdis[j].nome);
                            *ndm += 1;
                            break;
                            
                        }
                    }
                }
            }
            
            if(verA == 0)
                puts("Aluno nao cadastrado! Digite um RA valido.");
            if(verD == 0)
                puts("Disciplina não cadastrada! Digite um codigo valido.");
        }while(verA == 0 || verD == 0);
    
        fflush(stdin);
        __fpurge(stdin);
        printf("Deseja cadastrar mais um aluno? S/N\n");
        scanf(" %c", &escolha);
        
    }while(escolha == 's' || escolha == 'S');

    
}

void fazerMatriculaProfs (vinc vmatP[], int *ndmp, prof vetProf[], int ndp, dsp vetdis[], int ndd){
    
    int ruAux, codigoAux;       //Auxiliares
    int verP = 0, verD = 0;     //Verificadores
    int i, j;                   //Controladores
    char escolha;               //Controlador do loop primário

    do{
        do{
            
            puts("Digite o RA do aluno que deseja cadastrar:");
            scanf("%i", &ruAux);
            
            puts("Digite o codigo da disciplina que deseja cadastrar o aluno:");
            scanf("%i", &codigoAux);
            
            for(i = 0; i < ndp; i++){
                
                if(ruAux == vetProf[i].ru){
                    verP = 1;
                    
                    for(j = 0; j < ndd; j++){
                        
                        if(codigoAux == vetdis[j].codigo){
                            
                            verD = 1;
                            
                            strcpy(vmatP[*ndmp].professor.nomeProf, vetProf[i].nomeProf);
                            vmatP[*ndmp].professor.ru = vetProf[i].ru;
                            vmatP[*ndmp].disciplina.codigo = vetdis[j].codigo;
                            strcpy(vmatP[*ndmp].disciplina.nome, vetdis[j].nome);
                            *ndmp += 1;
                            break;
                            
                        }
                    }
                }
            }
            
            if(verP == 0)
                puts("Professor nao cadastrado! Digite um RU valido.");
            if(verD == 0)
                puts("Disciplina não cadastrada! Digite um codigo valido.");
        }while(verP == 0 || verD == 0);
    
        fflush(stdin);
        __fpurge(stdin);
        printf("Deseja cadastrar mais um professor? S/N\n");
        scanf(" %c", &escolha);
        
    }while(escolha == 's' || escolha == 'S');

    
}

void alunosEmDisciplinas(aln vetaln[], int nda, dsp vetDis[], int ndd, matricula vmat[], int *ndm){
    
    int x, i, j, verA = 0, verD = 0, auxA = 0, AuxVetA[50], auxD = 0, AuxVetD[50], auxM = 0;
    
    puts("Digite os RAs dos alunos (-1 p/ parar): ");
    
    do{
        
        scanf("%i", &x);
        
        for(i = 0; i < nda; i++){ // Verificar se o aluno esta cadastrado
            
            if(x == vetaln[i].ra){
                verA = 1;
                AuxVetA[auxA] = x;
                auxA++;
            }
        }
        
        if(verA == 0)
            puts("Aluno não existente!");
            
            
    }while(x != -1);
    
    puts("Digite os codigos das disciplinas (-1 p/ parar): ");
    
    do{
        
        scanf("%i", &x);
        
        for(i = 0; i < ndd; i++){ // Verificar se a disciplina esta cadastrada
            
            if(x == vetDis[i].codigo){
                verD = 1;
                AuxVetD[auxD] = x;
                auxD++;
            }
        }
        
        if(verD == 0)
            puts("Disciplina não existente!");
        
    }while(x != -1);
    
    for(i = 0; i < auxA; i++){
        
        for(j = 0; j < auxD; j++){
            
            vmat[auxM].aluno = vetaln[i];
		    vmat[auxM].disciplina = vetDis[j];
	    	auxM++;
	    	*ndm += 1;
        }
    }
}

void professoresEmDisciplinas(prof vetProf[], int ndp, dsp vetDis[], int ndd, vinc vmatP[], int *ndmp){
    
    int x, i, j, verP = 0, verD = 0, auxP = 0, AuxVetP[50], auxD = 0, AuxVetD[50], auxM = 0;
    
    puts("Digite os RUs dos professores (-1 p/ parar): ");
    
    do{
        
        scanf("%i", &x);
        
        for(i = 0; i < ndp; i++){ // Verificar se o aluno esta cadastrado
            
            if(x == vetProf[i].ru){
                verP = 1;
                AuxVetP[auxP] = x;
                auxP++;
            }
        }
        
        if(verP == 0)
            puts("Professor não existente!");
            
            
    }while(x != -1);
    
    puts("Digite os codigos das disciplinas (-1 p/ parar): ");
    
    do{
        
        scanf("%i", &x);
        
        for(i = 0; i < ndd; i++){ // Verificar se a disciplina esta cadastrada
            
            if(x == vetDis[i].codigo){
                verD = 1;
                AuxVetD[auxD] = x;
                auxD++;
            }
        }
        
        if(verD == 0)
            puts("Disciplina não existente!");
        
    }while(x != -1);
    
    for(i = 0; i < auxP; i++){
        
        for(j = 0; j < auxD; j++){
            
            vmatP[auxM].professor = vetProf[i];
		    vmatP[auxM].disciplina = vetDis[j];
	    	auxM++;
	    	*ndmp += 1;
        }
    }
}

void menu(){
    
    puts("Digite o numero referente a sua escolha (-1 para sair):");
    puts("1 - Cadastrar aluno");
    puts("2 - Cadastrar disciplina");
    puts("3 - Cadastrar professores");
    puts("4 - Fazer matricula de alunos em disciplinas");
    puts("5 - Fazer matricula de professores em disciplinas");
    puts("6 - Cadastrar uma lista de alunos em uma lista de disciplinas");
    puts("7 - Imprimir disciplinas de um aluno");
    puts("8 - Imprimir alunos de uma disciplina");
    puts("9 - Vincular professores a disciplinas");
}

void printaDisciplinas (matricula vmat[], int ndm){
    
    int ra, i, verA = 0;
    
    puts("Digite o RA do aluno q deseja consultar:");
    scanf("%i", &ra);
    
    
    printf("========================\n");
    
    for(i = 0; i < ndm; i++){
        
        if(ra == vmat[i].aluno.ra){

            verA = 1;
            printf("Nome do aluno: ");
            printf("%s", vmat[i].aluno.nome);
            printf("RA do aluno: ");
            printf("%i\n\n", vmat[i].aluno.ra);
            break;
        }
    }
    
    for(i = 0; i < ndm; i++){
        
        if(ra == vmat[i].aluno.ra){

            printf("Nome da disciplina: ");
            printf("%s", vmat[i].disciplina.nome);
            printf("Codigo da disciplina: ");
            printf("%i\n\n", vmat[i].disciplina.codigo);
        }
    }
    
    printf("========================\n\n");
    
    if(verA == 0)
        printf("Aluno nao cadastrado!\n");
}

void printaAlunos (matricula vmat[], int ndm){
    
    int codigo, i, verD = 0;
    
    puts("Digite o codigo da disciplina q deseja consultar:");
    scanf("%i", &codigo);
    
    
    printf("========================\n");
    
    for(i = 0; i < ndm; i++){
        
        if(codigo == vmat[i].disciplina.codigo){

            verD = 1;
            printf("Nome da disciplina: ");
            printf("%s", vmat[i].disciplina.nome);
            printf("Codigo da Disciplina: ");
            printf("%i\n\n", vmat[i].disciplina.codigo);
            break;
        }
    }
    
    for(i = 0; i < ndm; i++){
        
        if(codigo == vmat[i].disciplina.codigo){

            printf("Nome do aluno: ");
            printf("%s", vmat[i].aluno.nome);
            printf("RA do aluno: ");
            printf("%i\n\n", vmat[i].aluno.ra);
        }
    }
    
    printf("========================\n\n");
    
    if(verD == 0)
        printf("Aluno nao cadastrado!\n");
}

void printaProfs (vinc vmatP[], int ndmp){
    
    int ru, i, verP = 0;
    
    puts("Digite o RU do aluno q deseja consultar:");
    scanf("%i", &ru);
    
    
    printf("========================\n");
    
    for(i = 0; i < ndmp; i++){
        
        if(ru == vmatP[i].professor.ru){

            verP = 1;
            printf("Nome do professor: ");
            printf("%s", vmatP[i].professor.nomeProf);
            printf("RU do professor: ");
            printf("%i\n\n", vmatP[i].professor.ru);
            break;
        }
    }
    
    for(i = 0; i < ndmp; i++){
        
        if(ru == vmatP[i].professor.ru){

            printf("Nome da disciplina: ");
            printf("%s", vmatP[i].disciplina.nome);
            printf("Codigo da disciplina: ");
            printf("%i\n\n", vmatP[i].disciplina.codigo);
        }
    }
    
    printf("========================\n\n");
    
    if(verP == 0)
        printf("Professor nao cadastrado!\n");
}

void cancelAlunDisc (matricula vmat[], int *ndm, aln vetalunos[], int nda, dsp vetdis[], int ndd){
    
    int raAux, codigoAux;       //Auxiliares
    int verA = 0, verD = 0;     //Verificadores
    int i, j;                   //Controladores
    char escolha;               //Controlador do loop primário

    do{
        do{
            
            puts("Digite o RA do aluno que deseja cadastrar:");
            scanf("%i", &raAux);
            
            puts("Digite o codigo da disciplina que deseja cadastrar o aluno:");
            scanf("%i", &codigoAux);
            
            for(i = 0; i < nda; i++){
                
                if(raAux == vetalunos[i].ra){
                    verA = 1;
                    
                    for(j = 0; j < ndd; j++){
                        
                        if(codigoAux == vetdis[j].codigo){
                            
                            verD = 1;
                            
                            strcpy(vmat[*ndm].aluno.nome, vetalunos[i+1].nome);
                            vmat[*ndm].aluno.ra = vetalunos[i+1].ra;
                            vmat[*ndm].disciplina.codigo = vetdis[j+1].codigo;
                            strcpy(vmat[*ndm].disciplina.nome, vetdis[j+1].nome);
                            *ndm -= 1;
                            break;
                            
                        }
                    }
                }
            }
            
            if(verA == 0)
                puts("Aluno nao cadastrado! Digite um RA valido.");
            if(verD == 0)
                puts("Disciplina não cadastrada! Digite um codigo valido.");
        }while(verA == 0 || verD == 0);
    
        fflush(stdin);
        __fpurge(stdin);
        printf("Deseja cadastrar mais um aluno? S/N\n");
        scanf(" %c", &escolha);
        
    }while(escolha == 's' || escolha == 'S');
}

void cancelProfDisc(vinc vmatP[], int *ndmp, prof vetProf[], int ndp, dsp vetdis[], int ndd){
     int ruAux, codigoAux;      //Auxiliares
    int verP = 0, verD = 0;     //Verificadores
    int i, j;                   //Controladores
    char escolha;               //Controlador do loop primário

    do{
        do{
            
            puts("Digite o RA do aluno que deseja cadastrar:");
            scanf("%i", &ruAux);
            
            puts("Digite o codigo da disciplina que deseja cadastrar o aluno:");
            scanf("%i", &codigoAux);
            
            for(i = 0; i < ndp; i++){
                
                if(ruAux == vetProf[i].ru){
                    verP = 1;
                    
                    for(j = 0; j < ndd; j++){
                        
                        if(codigoAux == vetdis[j].codigo){
                            
                            verD = 1;
                            
                            strcpy(vmatP[*ndmp].professor.nomeProf, vetProf[i+1].nomeProf);
                            vmatP[*ndmp].professor.ru = vetProf[i+1].ru;
                            vmatP[*ndmp].disciplina.codigo = vetdis[j+1].codigo;
                            strcpy(vmatP[*ndmp].disciplina.nome, vetdis[j+1].nome);
                            *ndmp -= 1;
                            break;
                            
                        }
                    }
                }
            }
            
            if(verP == 0)
                puts("Professor nao cadastrado! Digite um RU valido.");
            if(verD == 0)
                puts("Disciplina não cadastrada! Digite um codigo valido.");
        }while(verP == 0 || verD == 0);
    
        fflush(stdin);
        __fpurge(stdin);
        printf("Deseja cadastrar mais um professor? S/N\n");
        scanf(" %c", &escolha);
        
    }while(escolha == 's' || escolha == 'S');
}


int main(){

    int escolha, *nda = 0, *ndd = 0, ndm = 0, *ndp = 0, *ndmp = 0, topoAlunosEmDisciplinas = 0;
    aln vetalunos[50];
    dsp vetdis[50];
    prof vetProf[50];
    matricula vmat[50];
    vinc vmatP[50];
    
    do{
        
        menu();
        scanf("%i", &escolha);
    
        switch(escolha){
    
            case 1: cadastraAluno(vetalunos, &nda);                                         break; // Cadastra um aluno e incrementa a variável "Numero de Alunos" para controlar quantos foram cadastrados
    
            case 2: cadastraDisciplina(vetdis, &ndd);                                       break; // Cadastra uma disciplina e incrementa a variável "Numero de Disciplinas" para controlar quantas foram cadastradas
            
            case 3: cadastraProf(vetProf, &ndp);                                            break; // Cadastra um professor e incrementa a variável "Numero de Professores" para controlar quantos foram cadastrados
            
            case 4: fazerMatriculaAlunos(vmat, &ndm, vetalunos, nda, vetdis, ndd);          break; // Matricula um aluno já cadastrado a uma ou mais disciplinas também já cadastradas
            
            case 5: fazerMatriculaProfs(vmatP, &ndmp, vetProf, ndp, vetdis, ndd);           break; // Matricula um professor já cadastrado a uma ou mais disciplinas também já cadastradas
            
            case 6: alunosEmDisciplinas(vetalunos, nda, vetdis, ndd, vmat, &ndm);           break; // Matricula uma lista de alunos a uma lista de materias
            
            case 7: professoresEmDisciplinas(vetProf, ndp, vetdis, ndd, vmatP, &ndmp);    break; // Matricula uma lista de professores a uma lista de materias
            
            case 8: printaDisciplinas(vmat, ndm);                                           break; // Printa todas as diciplinas cadastradas para o aluno selecionado
    
            case 9: printaAlunos(vmat, ndd);                                                break; // Printa todos os alunos cadastrados para a disciplina selecionada
            
            case 10: printaProfs(vmatP, ndmp);                                              break; // Printa todos os professores cadastrados para a disciplina selecionada
            
            case 11: cancelAlunDisc(vmat, &ndm, vetalunos, nda, vetdis, ndd);               break; // Desvincula um aluno já cadastrado a uma ou mais disciplinas também já cadastradas
            
            case 12: cancelProfDisc(vmatP, &ndmp, vetProf, ndp, vetdis, ndd);               break; // Desvincula um professor já cadastrado a uma ou mais disciplinas também já cadastradas
        }
        
    }while(escolha != -1);



}