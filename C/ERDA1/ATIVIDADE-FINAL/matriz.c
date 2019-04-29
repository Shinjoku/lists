#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matriz.h"
#include "lista.h"

//Funções:--------------------------------------------------------------------------------------------------
int criarMatriz(char nome[20], int x, int y, mor m[], int numeroDeMatrizes)
{

	cabeca *aux_C = NULL;
	no *aux_N = NULL;
	int i, j;

	if(x > 50 || y > 50 || x < 1 || y < 1)
		return 1;

	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
			return 1;
	}


	strcpy(m[numeroDeMatrizes].nome, nome);

	aux_C = (cabeca*)malloc(sizeof(cabeca));
	m[numeroDeMatrizes].proxCabeca = aux_C;
	m[numeroDeMatrizes].x = x;
	m[numeroDeMatrizes].y = y;


	for(j = 0; j < y; j++)
	{
		aux_C->y = j;
		aux_C->valor = 0;
		aux_N = (no*)malloc(sizeof(no));
		aux_C->prox = aux_N;
		for(i = 0; i < x - 1; i++)
		{
			aux_N->x = i+1;
			aux_N->valor = 0;
			aux_N->prox = NULL;
			if(i != x - 1)
			{
				aux_N->prox = (no*)malloc(sizeof(no));
				aux_N = aux_N->prox;
			}



		}
		aux_C->proxCabeca = NULL;
		if(j != y)
		{
			aux_C->proxCabeca = (cabeca*)malloc(sizeof(cabeca));
			aux_C = aux_C->proxCabeca;
		}

	}
	return 0;

}

float elemento(int x, int y, char nome[], mor m[], int numeroDeMatrizes)
{
	int i, j, k;

	cabeca *aux_C;
	no *aux_N;

	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
		{
			aux_C = m[i].proxCabeca;
			for(k = 0; k < y-1; k++)
			{
				aux_C = aux_C->proxCabeca;
			}
			aux_N = aux_C->prox;
			for(j = 0; j < x-1; j++)
			{
				aux_N = aux_N->prox;
			}
			if(x == 0)
				return aux_C->valor;
			return aux_N ->valor;
		}
	}

}

int imprimirMatriz(char nome[], mor m[], int numeroDeMatrizes)
{
	int x, y;
	no *aux_N;
	cabeca *aux_C;
	int i, j, k;

	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
		{
			x = m[i].x;
			y = m[i].y;
			aux_C = m[i].proxCabeca;
			for(j = 0; j < y; j++)
			{

				aux_N = aux_C->prox;
				printf("\n%6.2f", aux_C->valor);
				for(k = 0; k < x - 1; k++)
				{

					printf("%6.2f", aux_N->valor);
					aux_N = aux_N->prox;

				}
				aux_C = aux_C->proxCabeca;
			}
			return 0;
		}

	}
	return 1;
}

no* no_retornaPonteiro(int x, int y, char nome[], mor m[], int numeroDeMatrizes)
{
	int i, j, k;

	cabeca *aux_C;
	no *aux_N;

	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
		{
			aux_C = m[i].proxCabeca;
			for(k = 0; k < y; k++)
			{
				aux_C = aux_C->proxCabeca;
			}
			aux_N = aux_C->prox;
			for(j = 0; j < x-1; j++)
			{
				aux_N = aux_N->prox;
			}
			return aux_N;
		}
	}
	return NULL;                                                                //Zé colocou
}

cabeca* cabeca_retornaPonteiro(int y, char nome[], mor m[], int numeroDeMatrizes)
{
	int i, j, k;

	cabeca *aux_C;


	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
		{
			aux_C = m[i].proxCabeca;
			for(k = 0; k < y; k++)
			{
				aux_C = aux_C->proxCabeca;
			}


			return aux_C;
		}
	}
	return NULL;                                                                //Zé colocou
}

int adicionarElemento(int x, int y, char nome[], mor m[], float valor, int numeroDeMatrizes)
{
	if(x == 0)
		cabeca_retornaPonteiro(y, nome, m, numeroDeMatrizes)->valor = valor;
	else
		no_retornaPonteiro(x, y, nome, m, numeroDeMatrizes)->valor = valor;
}

int adicionarLinha(int y, char nome[], mor m[], float valores[], int numeroDeValores, int numeroDeMatrizes)
{
	int xMax, i;
	
	
	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
		{
			xMax = m[i].x;
			if(xMax != numeroDeValores)
				return 1;

			for(i = 0; i < xMax; i++)
			{
				adicionarElemento(i, y, nome, m, valores[i], numeroDeMatrizes);
			}
			return 0;
		}

	}
	return 1;
}

int adicionarColuna(int x, char nome[], mor m[], float valores[], int numeroDeValores, int numeroDeMatrizes)
{
	int yMax, i;
	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome) == 0)
		{
			yMax = m[i].y;
			printf("%i %i", yMax, numeroDeValores);
			if(yMax != numeroDeValores)
				return 1;

			for(i = 0; i < yMax; i++)
			{
				adicionarElemento(x, i, nome, m, valores[i], numeroDeMatrizes);
			}
			return 0;
		}

	}
	return 1;
}

int transporMatriz(char nome1[], char nome2[], mor m[], int numeroDeMatrizes)
{
	int i, j, k;
	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome2) == 0)
			return 1;
	}
	for(i = 0; i < numeroDeMatrizes; i++)
	{
		if(strcmp(m[i].nome, nome1) == 0)
		{
			if (criarMatriz(nome2, m[i].x, m[i].y, m, numeroDeMatrizes)) return 1;
			numeroDeMatrizes++;

			for(j = 0; j < m[i].y; j++)
			{

				adicionarElemento(j, 0, nome2, m,  cabeca_retornaPonteiro(j, nome1, m, numeroDeMatrizes)->valor, numeroDeMatrizes);

				for(k = 1; k < m[i].x; k++)
				{
					adicionarElemento(j, k, nome2, m,  no_retornaPonteiro(k, j, nome1, m, numeroDeMatrizes)->valor, numeroDeMatrizes);
				}
			}
			return 0;
		}

	}

}

int somarMatrizes(char nome1[], char nome2[], char nome3[], mor m[], int numeroDeMatrizes)
{
    int i, j, k;
    mor aux1, aux2;
    int um = 0, dois = 0, tres = 3;
    for(i = 0; i < numeroDeMatrizes; i++)
    {
        if(strcmp(m[i].nome, nome1) == 0)
        {
            aux1 = m[i];
            um = 1;
        }

            if(strcmp(m[i].nome, nome2) == 0)
        {
            aux2 = m[i];
            dois = 1;
        }

        if(strcmp(m[i].nome, nome3) == 0)
        {
            aux2 = m[i];
            tres = 1;
        }
    }

    if(um == 0|| dois == 0 || aux1.x != aux2.x || aux1.y != aux2.y || tres == 1)
        return 1;

    criarMatriz(nome3, aux1.x, aux1.y, m, numeroDeMatrizes);

    numeroDeMatrizes++;
    for(j = 0; j < aux1.y; j++)
    {
        adicionarElemento(0, j, nome3, m, (cabeca_retornaPonteiro(j, nome1, m, numeroDeMatrizes)->valor + cabeca_retornaPonteiro(j, nome2, m, numeroDeMatrizes)->valor), numeroDeMatrizes);
        for(k = 1; k < aux1.x; k++)
        {
            adicionarElemento(k, j, nome3, m,  (no_retornaPonteiro(k, j, nome1, m, numeroDeMatrizes)->valor + no_retornaPonteiro(k, j, nome2, m, numeroDeMatrizes)->valor), numeroDeMatrizes);

        }
    }
    return 0;

}

int dividirMatrizes(char nome1[], char nome2[], char nome3[], mor m[], int numeroDeMatrizes)
{
    int i, j, k;
    mor aux1, aux2;
    int um = 0, dois = 0, tres = 0;
    for(i = 0; i < numeroDeMatrizes; i++)
    {
        if(strcmp(m[i].nome, nome1) == 0)
        {
            aux1 = m[i];
            um = 1;
        }

        if(strcmp(m[i].nome, nome2) == 0)
        {
            aux2 = m[i];
            dois = 1;
        }

        if(strcmp(m[i].nome, nome3) == 0)
        {
            aux2 = m[i];
            tres = 1;
        }
    }



    if(um == 0|| dois == 0 || aux1.x != aux2.x || aux1.y != aux2.y || tres == 1)
        return 1;

    criarMatriz(nome3, aux1.x, aux1.y, m, numeroDeMatrizes);

    numeroDeMatrizes++;
    for(j = 0; j < aux1.y; j++)
    {
        if (cabeca_retornaPonteiro(j, nome2, m, numeroDeMatrizes)->valor == 0) return 1;
        adicionarElemento(0, j, nome3, m, (cabeca_retornaPonteiro(j, nome1, m, numeroDeMatrizes)->valor / cabeca_retornaPonteiro(j, nome2, m, numeroDeMatrizes)->valor), numeroDeMatrizes);
        for(k = 1; k < aux1.x; k++)
        {
            if (no_retornaPonteiro(k, j, nome2, m, numeroDeMatrizes)->valor == 0) return 1;
            adicionarElemento(k, j, nome3, m,  (no_retornaPonteiro(k, j, nome1, m, numeroDeMatrizes)->valor / no_retornaPonteiro(k, j, nome2, m, numeroDeMatrizes)->valor), numeroDeMatrizes);
        }
    }
    return 0;

}

int multiplicarMatrizes(char nome1[], char nome2[], char nome3[], mor m[], int numeroDeMatrizes)
{
    int i, j, k;
    mor aux1, aux2;
    int um = 0, dois = 0, tres = 0;
    for(i = 0; i < numeroDeMatrizes; i++)
    {
        if(strcmp(m[i].nome, nome1) == 0)
        {
            aux1 = m[i];
            um = 1;
        }

        if(strcmp(m[i].nome, nome2) == 0)
        {
            aux2 = m[i];
            dois = 1;
        }

        if(strcmp(m[i].nome, nome3) == 0)
        {
            aux2 = m[i];
            tres = 1;
        }
    }



    if(um == 0|| dois == 0 || aux1.x != aux2.x || aux1.y != aux2.y || tres == 1)
        return 1;

    criarMatriz(nome3, aux1.x, aux1.y, m, numeroDeMatrizes);

    numeroDeMatrizes++;
    for(j = 0; j < aux1.y; j++)
    {
        adicionarElemento(0, j, nome3, m, (cabeca_retornaPonteiro(j, nome1, m, numeroDeMatrizes)->valor * cabeca_retornaPonteiro(j, nome2, m, numeroDeMatrizes)->valor), numeroDeMatrizes);
        for(k = 1; k < aux1.x; k++)
        {
            adicionarElemento(k, j, nome3, m,  (no_retornaPonteiro(k, j, nome1, m, numeroDeMatrizes)->valor * no_retornaPonteiro(k, j, nome2, m, numeroDeMatrizes)->valor), numeroDeMatrizes);
        }
    }
    return 0;

}

int multiplicarMatrizes2(char nome2[], char nome1[], char nome3[], mor m[], int numeroDeMatrizes)
{
    int i, j, k;
    int tamX1, tamY1, tamX2, tamY2;
    float somador = 0;
    int um = 0, dois = 0, tres = 0;
    for(i = 0; i < numeroDeMatrizes; i++)
    {
        if(strcmp(m[i].nome, nome1) == 0)
        {
            tamX1 = m[i].x;
            tamY1 = m[i].y;
            um = 1;
        }

        if(strcmp(m[i].nome, nome2) == 0)
        {
            tamX2 = m[i].x;
            tamY2 = m[i].y;
            dois = 1;
        }

        if(strcmp(m[i].nome, nome3) == 0)
        {
            tres = 1;
        }
    }



    if(um == 0|| dois == 0 || tamY1 != tamX2 || tres == 1)
        return 1;

    criarMatriz(nome3, tamX1, tamY2, m, numeroDeMatrizes);

    numeroDeMatrizes++;

    for(i = 0; i < tamY2; i++)
    {

        for(j = 0; j < tamX1; j++)
        {
            somador = 0;
            for(k = 0; k < tamY2; k++)
                somador += (elemento(i, k, nome1, m, numeroDeMatrizes+1) * elemento(k, j, nome2, m, numeroDeMatrizes+1));


            adicionarElemento(i, j, nome3, m, somador, numeroDeMatrizes);
        }

    }
    return 0;

}

int destruirMatriz(char nome[], mor m[], int *numeroDeMatrizes){
	
	int i = 0, j, numLinhas, k;
	cabeca *auxCabeca;
	no *auxNo, *auxProx;
	
	while(strcmp(nome, m[i].nome) != 0){
		
		i++;
		if(i > *numeroDeMatrizes)
			return 1;
	}
	
	
	for(j = 0; j < m[i].y; j++){
		auxCabeca = cabeca_retornaPonteiro(m[i].y - (1 + j), m[i].nome, m, *numeroDeMatrizes);
		
		
		auxNo = auxCabeca->prox;
		for(k = 0; k < m[i].x - 1; k++){
			auxProx = auxNo->prox;
			free(auxNo);
			auxNo = auxProx;;
		}
	}

	*numeroDeMatrizes -=1;
	
	for(j = i; j < *numeroDeMatrizes; j++){
		
		m[j].x = m[j+1].x;
		m[j].y = m[j+1].y;
		strcpy(m[j].nome, m[j+1].nome);
		m[j].proxCabeca = m[j+1].proxCabeca;
	}
	
	return 0;
}
//----------------------------------------------------------------------------------------------------------