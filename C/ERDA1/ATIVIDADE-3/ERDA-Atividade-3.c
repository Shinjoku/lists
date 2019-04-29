#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct la_t{

	int ra;
	float nota;
	char nome[51];
	struct la_t *prox;
}la; //Definiçao do tipo Lista de Alunos


la *pegaAluno(){ // FUNCIONANDO
     la *No = (la *) malloc(sizeof(la));

    printf("Digite o RA do Aluno: ");
	scanf("%i", &No->ra);

	//fflush(stdin); // Para windows
	__fpurge(stdin); // Para linux

	printf("Digite o Nome do Aluno: ");
	fgets(No->nome, 51, stdin);

	printf("Nota do aluno: ");
	scanf("%f", &No->nota);
	return No;

} //Pegar informações:

void listAlunos(la **inicio){ // FUNCIONANDO

	la *aux;
	aux = *inicio;
	la *No = pegaAluno();

        if(aux == NULL){
            (*inicio) = No;
	    No->prox = NULL;
            printf("Cadastro realizado com sucesso\n\n");
        }
        else if(aux->ra >= No->ra){
            No->prox = aux;
            (*inicio) = No;
            printf("Cadastro realizado com sucesso\n\n");
        }
        else
            listAlunos(&(aux->prox));

}  //Cria um item na lista de alunos e obtem suas informações;

void printAlunos(la *inicio){ //FUNCIONANDO


	while (inicio != NULL){

		__fpurge(stdout);

		printf("==============================\n");
		printf("Nome do aluno: %s", inicio->nome);
		printf("Ra do aluno: %i\n", inicio->ra);
		printf("Nota do aluno: %.2f\n", inicio->nota);
		printf("==============================\n");
		inicio = inicio->prox;
        	
	}
} //Printa os alunos cadastrados

int busca_por_ra(la *inicio){ //FUNCIONANDO

	int ra;

	puts("Digite o RA que deseja procurar:");
	scanf("%i", &ra);

	while (inicio != 0)
	{
		if (ra == inicio->ra)
		{
            printf("==============================\n");
			printf("Nome: %sRA: %i\nNota: %.2f\n", inicio->nome, inicio->ra, inicio->nota);
			printf("==============================\n");
			return 1;
		}

		inicio = inicio->prox;
	}
	return 0;
} // Busca o aluno sugerido de acordo com o RA

int busca_por_nome(la *inicio) //FUNCIONANDO
{
	char aux[51];

	puts("Digite o nome que deseja procurar:");
	//fflush(stdin); // Para Windows
	__fpurge(stdin);// Para Linux
	fgets(aux, 51, stdin);


	while (inicio != NULL)
	{

		if (strcmp(aux, inicio->nome) == 0)
		{
            printf("==============================\n");
			printf("Nome: %sRA: %i\nNota: %.2f\n", inicio->nome, inicio->ra, inicio->nota);
			printf("==============================\n");
			return 1;
		}

		inicio = inicio->prox;
	}
	return 0;
} // Busca o aluno sugerido de acordo com o nome

int removeAluno(la **inicio, int ra){

    la *aux;
    aux = *inicio;

    if(aux != NULL){
        if(aux->ra == ra){
            (*inicio) = aux->prox;
            free(aux);
            return 1;
        }else
            removeAluno(&(aux->prox), ra);
    }
} // Remove um aluno do sistema

void menu() //FUNCIONANDO
{
	printf("Digite o numero referente à escolha:\n");
	printf("1 - Cadastrar aluno;\n");
	printf("2 - Exibir dados dos alunos;\n");
	printf("3 - Buscar aluno por RA;\n");
	printf("4 - Buscar aluno por nome;\n");
	printf("5 - Remover cadastro de aluno;\n");
	printf("0 - Sair;\n");
} // printa o menu

int main(){

	//inicialização das variáveis:
	la *iniAlunos;
    la *No;
	int escolha, escolhaSelecao, ra;

	iniAlunos = NULL;



	menu ();
	scanf("%i", &escolha);

	while (escolha != 0){

        switch (escolha){

            case 1:
                listAlunos(&iniAlunos);
            break;

            case 2:
                printAlunos(iniAlunos);
            break;

            case 3:
                if(busca_por_ra(iniAlunos) == 0)
                    puts("Aluno nao cadastrado!");
            break;

            case 4:
                if(busca_por_nome(iniAlunos) == 0)
                    puts("Aluno nao cadastrado!");
            break;

            case 5:
                puts("Digite o RA do aluno que deseja remover:");
                scanf("%i", &ra);
                if(removeAluno(&iniAlunos, ra) == 1)
                    puts("Aluno removido com sucesso!");
                else
                    puts("A operação falhou!");
            break;

        }

            //system("pause"); // Para windows
            //system("cls"); // Para windows
            __fpurge(stdin);
            getchar();
            system("clear");
            menu ();
            
            scanf("%i", &escolha);
	}

	return 0;
}

