#ifndef ARQUIVOS_H
#define ARQUIVOS_H


//Funções:
void gravaArquivo(no *, FILE *);                     //Entradas: Raiz da árvore;Saídas: Printa a árvore em ordem de CPF no arquivo "Assinantes.txt";

int cadastraNaArvoreArq(no **, long long int, FILE*);

no* pegaDadosArq(long long int, FILE*);

void insereFimListaArq(lista **, long long int);

#endif