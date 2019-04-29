#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "matriz.h"

int main()
{

    mor matriz[50];
    int numeroDeMatrizes = 0, numeroDeValores = 0;
    char comando[3] = "", nome[20], nome2[20], nome3[20];  ///comando e nome da matriz
    char controle;
    int x, y, i;
    float valor, valores[50];


    do
    {
        numeroDeValores = 0;
        controle = ' ';
        scanf("%s", comando);
        upper(comando);

        if(strcmp(comando, "CM") == 0)
        {
            scanf("%s %i %i", nome, &x, &y);
            if(criarMatriz(nome, x, y, matriz, numeroDeMatrizes)) printf("ERRO");
            else
            {
                printf("OK");
                numeroDeMatrizes++;
            }
        }
        else
        if(strcmp(comando, "DM") == 0)
        {
            scanf("%s", nome);
            if(destruirMatriz(nome, matriz, numeroDeMatrizes)) printf("\nERRO!");
            else printf("OK!");
        }
        else
        if(strcmp(comando, "IM") == 0)
        {
            scanf("%s", nome);
            if(imprimirMatriz(nome, matriz, numeroDeMatrizes)) printf("ERRO");
        }
        else
        if(strcmp(comando, "AE") == 0)
        {
            scanf("%s %i %i %f", nome, &x, &y, &valor);
            adicionarElemento(x, y, nome, matriz, valor, numeroDeMatrizes);

        }
        else
        if(strcmp(comando, "AL") == 0)
        {
            scanf("%s %i", nome, &y);
            while(controle != '#')
            {
                scanf("%f", &valores[numeroDeValores]);
                scanf("%c", &controle);
                numeroDeValores++;
            }
            if(adicionarLinha(y, nome, matriz, valores, numeroDeValores, numeroDeMatrizes)) printf("ERRO");
            else printf("OK");

        }
        else
        if(strcmp(comando, "AC") == 0)
        {
            scanf("%s %i", nome, &x);
            while(controle != '#')
            {
                scanf("%f", &valores[numeroDeValores]);
                scanf("%c", &controle);
                numeroDeValores++;
            }
            if(adicionarColuna(x, nome, matriz, valores, numeroDeValores, numeroDeMatrizes)) printf("ERRO");
            else printf("OK");

        }
        else
        if(strcmp(comando, "TM") == 0)
        {
            scanf("%s %s", nome, nome2);
            if(transporMatriz(nome, nome2, matriz, numeroDeMatrizes)) printf("ERRO");
            else
            {
                numeroDeMatrizes++;
                imprimirMatriz(nome2, matriz, numeroDeMatrizes);
            }

        }
        else
        if(strcmp(comando, "SM") == 0)
        {
            scanf("%s %s %s", nome, nome2, nome3);
            if(somarMatrizes(nome, nome2, nome3, matriz, numeroDeMatrizes)) printf("ERRO");
            else
            {
                numeroDeMatrizes++;
                imprimirMatriz(nome3, matriz, numeroDeMatrizes);
            }

        }
        else
        if(strcmp(comando, "DV") == 0)
        {
            scanf("%s %s %s", nome, nome2, nome3);
            if(dividirMatrizes(nome, nome2, nome3, matriz, numeroDeMatrizes)) printf("ERRO");
            else
            {
                numeroDeMatrizes++;
                imprimirMatriz(nome3, matriz, numeroDeMatrizes);
            }

        }
        if(strcmp(comando, "ME") == 0)
        {
            scanf("%s %s %s", nome, nome2, nome3);
            if(multiplicarMatrizes(nome, nome2, nome3, matriz, numeroDeMatrizes)) printf("ERRO");
            else
            {
                numeroDeMatrizes++;
                imprimirMatriz(nome3, matriz, numeroDeMatrizes);
            }

        }
        if(strcmp(comando, "MM") == 0)
        {
            scanf("%s %s %s", nome, nome2, nome3);
            if(multiplicarMatrizes2(nome, nome2, nome3, matriz, numeroDeMatrizes)) printf("ERRO");
            else
            {
                numeroDeMatrizes++;
                imprimirMatriz(nome3, matriz, numeroDeMatrizes);
            }

        }

        if(strcmp(comando, "DB") == 0)
        {
            scanf("%s %i %i", nome, &x, &y);
            printf("%f", elemento(x, y, nome, matriz, numeroDeMatrizes));

        }
        printf("\n");
    }while(strcmp(comando, "FE"));
}
