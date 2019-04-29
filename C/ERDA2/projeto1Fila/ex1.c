/* Nome: Bruno Pereira Bannwart		R.A: 15171572
   Nome: Vitor Borela				R.A:

   Opcionais Funcionando: 1, 4

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <windows.h>

typedef struct servidor
{
	struct cliente *fila;
	time_t delay_atendimento;
	int tamanho;
}servidor;

typedef struct cliente
{
	time_t entrada, saida;
	struct cliente *prox;
}cliente;

typedef struct info
{
	time_t tempo_minimo, tempo_maximo;
}info;

//setando valores iniciais do sistema
void inicio(servidor s[], int *quantidade_servidores, time_t *t_atendimento, time_t *t_cliente, info *relatorio)
{
	*quantidade_servidores = 1;
	*t_atendimento = 50;
	*t_cliente = 2;

	s[0].delay_atendimento = 4;
	s[0].tamanho = 0;
	s[0].fila = NULL;
	
	relatorio->tempo_minimo = 1000;
	relatorio->tempo_maximo = 0;
}

void exibir_info(int quantidade_servidores, time_t t_atendimento, time_t t_cliente)
{
    printf("\nNumero de servidores: %i\n", quantidade_servidores);
    printf("Tempo de simulacao: %is\n", t_atendimento);
    printf("Tempo para entrada de novos clientes: %is\n", t_cliente);
}

//função para exibir o menu
void menu()
{
	printf("\nMENU\n");
	printf("1 - Criar servidores\n");
	printf("2 - Definir periodo de simulacao\n");
	printf("3 - Definir periodo de entrada de clientes\n");
	printf("4 - Exibir Relatorio\n");
	printf("5 - Iniciar atendimento\n");
	printf("6- Sair\n");
	printf("Digite a opcao desejada: ");
}

//criar servidores de acordo com a preferencia do usuario (quantidade e tempo de atendimento)
void criar_servidores(servidor s[], int *quantidade_servidores)
{
	int tempo_atendimento, quant, i;

	//quantidade de servidores
	do
	{
		printf("Digite a quantidade de servidores: ");
		scanf("%i", &quant);

	}while(quant < 1 || quant > 100);

	*quantidade_servidores = quant;

	//inserir tempo de atendimento para cada servidor
    for(i = 0; i < quant; i++)
	{
		printf("Digite a duracao do atendimento do servidor %i: ", i+1);
		scanf("%i", &tempo_atendimento);

		s[i].delay_atendimento = tempo_atendimento;
		s[i].tamanho = 0;
		s[i].fila = NULL;
	}
}

//setar periodo do atendimento
void periodo_atendimento(time_t *t_atendimento)
{
	int p_at;

	printf("Defina o tempo de simulacao: ");
	scanf("%i", &p_at);

	*t_atendimento = p_at;
}

//setar periodo de entrada de clientes
void periodo_cliente(time_t *t_cliente)
{
	int p_cl;

	printf("Defina o tempo de entrada de clientes: ");
	scanf("%i", &p_cl);

	*t_cliente = p_cl;
}

//inicio do atendimento
void atendimento(servidor s[], int quantidade_servidores, time_t t_atendimento, time_t t_cliente, info *relatorio)
{
	time_t inicio, atual = 0, simulacao;

	//inicio do atendimento
	time(&inicio);

	do
	{
		time(&atual);
		
		//clientes entram na fila apos um periodo de tempo determinado
		if((int) difftime(atual,inicio) % t_cliente == 0)
		{
			menor_fila(s, quantidade_servidores);
		}

		//remover cliente da fila
		cliente_atendido(s, quantidade_servidores, relatorio);
		sleep(1);
		
		simulacao = difftime(atual,inicio);
	}while(difftime(simulacao, t_atendimento) != 0);
}

//inserir novo cliente na menor fila
void menor_fila(servidor s[], int quantidade_servidores)
{
	int menor_tamanho, indice, posicao, quantidade_clientes;

	printf("Digite a quantidade de clintes a serem inseridos: ");
	scanf("%i", &quantidade_clientes);

	//enquanto tiver cliente para entrar nas filas
	while(quantidade_clientes > 0)
	{
		menor_tamanho = 1000;

		//procura fila com menor quantidade de clientes
		for(indice = 0; indice < quantidade_servidores; indice++)
		{
			if (s[indice].tamanho < menor_tamanho)
			{
				menor_tamanho = s[indice].tamanho;

				//salva a posicao da menor fila
				posicao = indice;
			}
		}

		inserir_fila(&s[posicao].fila);
		s[posicao].tamanho++;

		quantidade_clientes--;
	}
}

//inserir cliente na fila
void inserir_fila(cliente **fila)
{
    cliente *novo;
    novo = (*fila);

	//inserir cliente em uma fila vazia ou no fim da fila
	if(novo == NULL)
	{
		novo = (struct cliente *) malloc(sizeof(cliente));

		time(&novo->entrada);
		novo->prox = NULL;
		(*fila) = novo;
	}

	else
	{
		inserir_fila(&novo->prox);
	}
}

//cliente sendo atendido e gerar relatorio do sistema
void cliente_atendido(servidor s[], int quantidade_servidores, info *relatorio)
{
	time_t tempo_cliente, atual;
    int i;

    atual = time(NULL);

	for(i = 0; i < quantidade_servidores; i++)
	{
		if((int)difftime(s[i].fila->entrada, atual) % s[i].delay_atendimento == 0)
		{
			time(&s[i].fila->saida);
			s[i].tamanho--;
			tempo_cliente = difftime(s[i].fila->entrada,s[i].fila->saida);
			atualizar_relatorio(tempo_cliente,relatorio);
			remover_fila(&s[i].fila);
		}
	}
}

//remover cliente da fila
void remover_fila(cliente **fila)
{
	//remover cliente no inicio da fila
	cliente *auxiliar;

	auxiliar = (*fila);

	(*fila) = auxiliar->prox;
	free(auxiliar);
}

void atualizar_relatorio(time_t tempo_cliente, info *relatorio)
{
	if(relatorio->tempo_minimo > tempo_cliente)
	{
		relatorio->tempo_minimo = tempo_cliente;
	}

	if(relatorio->tempo_maximo < tempo_cliente)
	{
		relatorio->tempo_maximo = tempo_cliente;
	}
}

//função para exibir o relatorio do sistema
void exibir_relatorio(info relatorio)
{
	printf("Tempo minimo de atendimento dos servidores: %i\n", relatorio.tempo_minimo);
	printf("Tempo maximo de atendimento dos servidores: %i\n", relatorio.tempo_maximo);
}

int main()
{
	servidor s[100];
	info relatorio;

	int quantidade_servidores, opc;
	time_t t_atendimento, t_cliente;

	inicio(s, &quantidade_servidores, &t_atendimento, &t_cliente, &relatorio);

	do
	{
	    exibir_info(quantidade_servidores,t_atendimento,t_cliente);
		menu();
		scanf("%i", &opc);

		switch(opc)
		{
			case 1:	criar_servidores(s, &quantidade_servidores);
					break;

			case 2:	periodo_atendimento(&t_atendimento);
					break;

			case 3:	periodo_cliente(&t_cliente);
					break;

			case 4:	exibir_relatorio(relatorio);
					break;

			case 5:	atendimento(s, quantidade_servidores, t_atendimento, t_cliente, &relatorio);
					break;

			case 6:	break;
		}

	} while(opc != 6);

	return 0;
}