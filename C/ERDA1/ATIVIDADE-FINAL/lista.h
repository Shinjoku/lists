#ifndef LISTA_H
#define LISTA_H

//Structs:-----------------------
typedef struct _mor
{
    char nome[51];
    struct _mor *proxCabeca;
    int x, y;
}mor;

typedef struct _cabeca
{
    int y;
    float valor;
    struct _cabeca *proxCabeca;
    struct _no *prox;
}cabeca;

typedef struct _no
{
    int x;
    float valor;
    struct _no *prox;
}no;
//-------------------------------

//Funções:---------
void upper(char *);
//-----------------

#endif