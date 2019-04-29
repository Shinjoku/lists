#include <stdio.h>
#include <stdlib.h>

typedef struct no_t{

	int info;
	struct no_t *esq, *dir;
}no;


int insere(no **raiz, int n){
	
	
	if(!(*raiz)){
		
		(*raiz) = (no *)malloc(sizeof(no));
		(*raiz)->info = n;
		(*raiz)->dir = NULL;
		(*raiz)->esq = NULL;
		return 0;
	}
	
	else if(n > (*raiz)->info)
		return insere(&(*raiz)->dir, n);
	
	else if(n < (*raiz)->info)
	    return insere(&(*raiz)->esq, n);
	
	return -1;	
}												//Working

void emOrdem(no *raiz){
    
    if(raiz){
        
        emOrdem(raiz->esq);    
    	printf("%i\n", raiz->info);
    	emOrdem(raiz->dir);
    }
}														//Working

void posOrdem(no *raiz){
    
    if(raiz){
        
        emOrdem(raiz->esq);    
    	emOrdem(raiz->dir);
    	printf("%i\n", raiz->info);
    }
}													//Working

void preOrdem(no *raiz){
    
    if(raiz){
        
    	printf("%i\n", raiz->info);
        emOrdem(raiz->esq);    
    	emOrdem(raiz->dir);
    }
}													//Working

int menorValor(no *raiz){
	
	int r;
	
	if(raiz->esq == NULL){
		r = raiz->info;
		return r;
	}
	else
		return menorValor(raiz->esq);
}													//Working

int maiorValor(no *raiz){
	
	int r;
	
	if(raiz->dir == NULL){
		r = raiz->info;
		return r;
	}
	else
		return maiorValor(raiz->dir);
}													//Working

float media(no *raiz, int contador){
	
	static int soma = 0;
	
	if(raiz){
		
		media(raiz->esq, contador);
		soma += raiz->info;
		media(raiz->dir, contador);
	}
	
	return (float) soma/contador;
}										//Working

int verifica(no *raiz, int n){
	
	if(!raiz)
		return 0;
	else if(raiz->info == n)
		return 1;
	else{
		if(n > raiz->info)
			return verifica(raiz->dir, n);
		else
			return verifica(raiz->esq, n);
	}
}												//Working

int altura(no *raiz){
	
	int he = 0, hd = 0;
	
	if(!raiz)
		return -1;
	else {
		
		he = altura(raiz->esq);
		hd = altura(raiz->dir);
		if(he < hd) return hd+1;
		else return he+1;
	}
}														//Working

int nulls(no *raiz){
    
    static int count = 0;
    
    if(!raiz)
        count++;
    else{
        
        nulls(raiz->esq);
        nulls(raiz->dir);
    }
    
    return count;
}														//Working

int multiplosDeTres(no *raiz){
    
    static int count = 0;
    
    if(!raiz)
    	return 0;
    else{
        multiplosDeTres(raiz->esq);
        if(raiz->info % 3 ==0)
        	count++;
        multiplosDeTres(raiz->dir);
    }
    
    return count;
}												//Working

int folhas(no *raiz){
    
    static int count = 0;
    
    if(!raiz)
    	return 0;
    else{
        folhas(raiz->esq);
        if(raiz->esq == NULL && raiz->dir == NULL)
        	count++;
        folhas(raiz->dir);
    }
    
    return count;
}														//Working

int rem2(no **raiz){
	
	int x;
	no *aux;
	
	if(!(*raiz)->dir){							//Ao conseguir achar;
		
		x = (*raiz)->info;
		aux = (*raiz);
		(*raiz) = (*raiz)->esq;
		free(aux);
		return x;
	}
	return rem2(&(*raiz)->dir);			//Vai buscar sempre o maior dos menores;
}

void rem(no **raiz, int n){
	
	no *aux;
	
	//Verifica se existe
	if((*raiz)){
		
		if((*raiz)->info == n){					//É o que eu procuro?
			
			if(!(*raiz)->dir){					//Dir dele é null?
				
				aux = (*raiz);
				(*raiz) = (*raiz)->esq;
				free(aux);
			}
			else if(!(*raiz)->esq){				//Esq dele é null?
				
				aux = (*raiz);
				(*raiz) = (*raiz)->dir;
				free(aux);
			}
												//Se não for folha:
			else
				(*raiz)->info = rem2(&(*raiz)->esq);
		}
		
		
		else if(n > (*raiz)->info)				//Se não, continuar procurando
				rem(&(*raiz)->dir, n);
			else
				rem(&(*raiz)->esq, n);
	}
}

int main(){
	
	no *raiz = NULL;
	int num, elementos = 0, somaDosElementos = 0, mv, Mv;
	
	scanf("%i", &num);
	
	while(num != 0){
		
		if(insere(&raiz, num)) puts("ERRO");
		else {
			puts("SUCESSO");
			elementos++;
			somaDosElementos += num;
		}
		scanf("%i", &num);
	}
	puts("Em Ordem:");
	emOrdem(raiz);
	puts("");
	puts("Pre Ordem:");
	preOrdem(raiz);
	puts("");
	puts("Pos Ordem:");
	posOrdem(raiz);
	puts("");
	
	printf("Menor Valor: %i\n", menorValor(raiz));
	printf("Maior Valor: %i\n", maiorValor(raiz));
	
	printf("Numero de elementos: %i\n", elementos);
	printf("Soma dos Elementos: %i\n", somaDosElementos);
	printf("Media: %g\n", media(raiz, elementos));
	
	puts("Digite o numero q quer procurar");
	scanf("%i", &num);
	if(verifica(raiz, num)) puts("O numero existe na arvore");
	else puts("O numero não existe na arvore");
	
	printf("Altura da Arvore: %i\n", altura(raiz));
	
	printf("Numero de NULLs na arvore: %i\n", nulls(raiz));
	
	printf("Numero de nós multiplos de tres na arvore: %i\n", multiplosDeTres(raiz));
	
	printf("Numero de folhas na arvore: %i\n", folhas(raiz));
	
	puts("digite o numero q deseja remover:");
	scanf("%i", &num);
	rem(&raiz, num);
	
	preOrdem(raiz);

}