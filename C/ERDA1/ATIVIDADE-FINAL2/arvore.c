#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"

//Entradas: raiz da árvore;
//Saídas: 0 Sucesso || -1 Falha;
int cadastraNaArvore(no **raiz, long long int cpf){															
	
	if(!(*raiz)){																//Verificar se existe raiz;
	
		*raiz = pegaDados(cpf);													//Aloca um espaço de memória;
		if(!(*raiz)) return -1;														//Verificar se malloc funcionou;
		return 0;
	}
	
	else if(cpf > (*raiz)->cpf)													//Procurar lugar certo para colocar as informações;
			return cadastraNaArvore(&(*raiz)->dir, cpf);										//Se CPF maior -> vai pra direita;
		else																	
			return cadastraNaArvore(&(*raiz)->esq, cpf);										//Se CPF menor -> vai pra esquerda;
	
	return -1;	
}							//Working

//Entradas: Void;
//Saídas: Struct árvore com os dados que serão inseridos;
no* pegaDados(long long int cpf){

	no *dados = (no *) malloc(sizeof(no));
	lista *aux = NULL;
	long long int telefone;
	
	if(!dados){
		
		puts("ERRO\n");
		return NULL;
	}
	
	puts("Digite o nome:");
	__fpurge(stdin);
	fgets(dados->nome, MAXNOME, stdin);
	
	dados->cpf = cpf;
	
	puts("Digite os telefones (-1 para parar):");
	
	scanf("%lli", &telefone);
	
	while(telefone > 0){
		
			insereFimLista(&dados->proxtel, telefone);
			scanf("%lli", &telefone);
			
	}
	
	dados->esq = NULL;
	dados->dir = NULL;
	
	return dados;
}											//Working

//Entradas: Raiz da árvore;
//Saídas: Nó que será o substituto do que foi selecionado para ser removido;
long long int rem2(no **raiz){
	
	long long int x;
	no *aux;
	
	if(!(*raiz)->dir){							//Ao conseguir achar;
		aux = (*raiz);
		(*raiz) = (*raiz)->esq;
		return aux;
	}
	return rem2(&(*raiz)->dir);			//Vai buscar sempre o maior dos menores;
}												//Working

//Entradas: raiz da árvore e o CPF que será removido;
//Saídas: Nada. Simplesmente executa a ação e atualiza a raiz primária;
void rem(no **raiz, long long int n){
	
	no *aux;
	
	//Verifica se a raiz não é nula;
	if((*raiz)){
		
		if((*raiz)->cpf == n){					//É o que eu procuro?
			
			if(!(*raiz)->dir){					//Dir dele é null?
				
				aux = (*raiz);
				
				while((*raiz)->proxtel){
				  
					excluiLista(&(*raiz)->proxtel);
				}
				(*raiz) = (*raiz)->esq;
				free(aux);
			}
			else if(!(*raiz)->esq){				//Esq dele é null?
				
				aux = (*raiz);
				 
				while((*raiz)->proxtel){
				  
					excluiLista(&(*raiz)->proxtel);
				}
				(*raiz) = (*raiz)->dir;
				free(aux);
			}
												//Se não for folha:
			else{
				aux = (*raiz);
				
				while((*raiz)->proxtel){
				  
					excluiLista(&(*raiz)->proxtel);
				}
				(*raiz) = rem2(&(*raiz)->esq);
				(*raiz)->dir = aux->dir;
				(*raiz)->esq = aux->esq;
				free(aux);
			}
		}
		else if(n > (*raiz)->cpf)				//Se não, continuar procurando;
				rem(&(*raiz)->dir, n);
			else
				rem(&(*raiz)->esq, n);
	}
}										//Working

///Entradas: Raiz da árvore e CPF que serão alterados;
//Saídas: Nada. Simplesmente executa a ação e atualiza a raiz primária;
int verifica(no *raiz, long long int n){
	
	if(!raiz)
		return 0;
	else if(raiz->cpf == n){
		
		return 1;
	}
	else{
		if(n > raiz->cpf)
			return verifica(raiz->dir, n);
		else
			return verifica(raiz->esq, n);
	}
}									//Working

//Entradas: Raiz da árvore;
//Saídas: Printa a árvore em ordem de CPF;
void emOrdem(no *raiz){
    
    int i = 1;
    
    if(raiz){
    	
        emOrdem(raiz->esq);    
        
    	lista *aux = raiz->proxtel;
    	puts("-------------------------");
    	printf("CPF: %lli\n", raiz->cpf);
    	printf("Nome: %s", raiz->nome);
    	puts("Telefones:");
    	
    	while(aux){
    		printf("%i: %lli\n", i, aux->tel);
    		i++;
    		aux = aux->prox;
    	}
		puts("-------------------------");
    	emOrdem(raiz->dir);
    }
}														//Working

//Entradas: Raiz da árvore, CPF;
//Saídas: Printa o assinante;
int printaUm(no *raiz, long long int cpf){
	lista *aux;
	int i=1;
	
	if(!raiz) return 0;//ERRO
	
	aux = raiz->proxtel;
	
	//verifica se encontrou a posição
	if(cpf == raiz->cpf)
	{
	    puts("-------------------------");
	    printf("CPF: %lli\n", raiz->cpf);
	    printf("Nome: %s", raiz->nome);
	    puts("Telefones:");
	    
	    while(aux){
		    printf("%i: %lli\n", i, aux->tel);
		    i++;
		    aux = aux->prox;
	     }
	    puts("-------------------------");
	    return 1;//sucesso
	} else
	  //verifica como prosseguir a busca
	if(cpf > raiz->cpf)	
												
		return printaUm(raiz->dir, cpf);										
	else																	
		return printaUm(raiz->esq, cpf);

		
}									//Working

//Entradas: arvore; sua altura atual (0 como padrão) 
//saida: void; mas mostra na tela a arvore bonita
void printaBonito(no *raiz, int alt){
    
    int i; //contador

    printf("\n");
    for(i = 0; i < alt - 1; i++) printf("       ");  //printa espaços necessários para encaixar
    if (alt != 0) printf("    |-  "); // antes dos numeros mostra os " |- "
    
    if(!raiz) {  //se chegou ao fim desse galho -> printa ----- e retorna (relacionado com ***)
        printf("-----  ");
        return;
    } 
    else printf("%.5lld  ",raiz->cpf); //printa a raiz atual
    
    if(raiz->dir || raiz->esq) { //SE TIVER RAIZ DIREITA OU ESQUERDA -> printa elas | CASO CONTRARIO -> printa nennhuma (***)
    printaBonito(raiz->dir, alt+1); //printa direita

    printaBonito(raiz->esq, alt+1); //printa esquerda
    }

}										//Working

//Entradas: Árvore, nome;
//Saídas: Printa o assinante correspondente;
void printaPorNome(no *raiz, char nome[]){
	
	if(!raiz) return;
	if(strcmp(raiz->nome, nome) == 0)
	{
		printaUm(raiz, raiz->cpf);
	}
	printaPorNome(raiz->esq, nome);  
	printaPorNome(raiz->dir, nome);  
	
}									//Working

//Entradas: Árvore, telefone;
//Saídas: Printa o assinante correspondente;
void printaPorTelefone(no *raiz, long long int tel){
	
	if(!raiz) return;
	lista *aux = raiz->proxtel;
	if(existeTel(aux, tel))
	{
		printaUm(raiz, raiz->cpf);
	}
	printaPorTelefone(raiz->esq, tel);  
	printaPorTelefone(raiz->dir, tel);  
	
}						//Working

//Entradas: Raiz, Início, cpf;
//Saídas: -1 se CPF não encontrado; 0 para Sucesso;
int alteraCadastro(no ** raizz,no **inicioArvore, long long int cpf){
	long long int tel;
	int escolhaAltera, escolhaTel, i, cpfNaoExiste;
	no *auxNo;
	lista *aux;
	no *raizr = *raizz; // gamb para manter **raizz
	no **raiz = &raizr; // gamb para manter **raizz - caso contrario alterar definição de **raizz para *raiz e todos os lugares do codigo *raiz para raiz
	

	if(*raiz == NULL)
	{
		return -1;//cpf não encontrado
	}
	else{
		if(cpf == (*raiz)->cpf)
		{
			do{
				
				aux = (*raiz)->proxtel;
				
				//printa cadastro
				puts("Cadastro que foi atualizado:");
				puts("-------------------------");
				printf("CPF: %lli\n", (*raiz)->cpf);
				printf("Nome: %s", (*raiz)->nome);
				puts("Telefones:");
				
				i=1;
				while(aux){
				   printf("%i: %lli\n", i, aux->tel);
				    i++;
				     aux = aux->prox;
				}
				puts("-------------------------");
				//printa menu de escolha
				puts("0)Sair\n1)Atualizar cpf\n2Atualizar Nome\n3)Atualizar lista de telefones");
				scanf("%d",&escolhaAltera);
				
				switch(escolhaAltera)
				{
					case 0://fim de alterações
						return 0;//alterações feitas com sucesso
					case 1://mudar cpf
						auxNo = (*raiz);			
						remEspecialAltera(inicioArvore,auxNo->cpf);
						auxNo->dir = auxNo->esq = NULL; 
						
						do{
							printf("Digite o novo cpf do cadastro: ");
							scanf("%lli",&auxNo->cpf);			//atualiza cpf
							if((cpfNaoExiste = CadastraEspecialAltera(inicioArvore,auxNo)) == 0)
							  printf("CPF ja existente na arvore!!!\n");
							
						}while(cpfNaoExiste == 0);
						(*raiz) = auxNo;
						break;
					case 2://mudar nome
							puts("Digite o novo nome do cadastro");
							__fpurge(stdin);
							fgets((*raiz)->nome, MAXNOME, stdin);
						break;
					case 3://mudar telefones
						do{
							puts("0)Sair\n1)Inserir novo numero de telefone\n2)Remover numero de telefone");
							scanf("%d",&escolhaTel);
							switch(escolhaTel)
							{
								case 1:
								  printf("Digite o numero do telefone que sera inserido: ");
								  scanf("%lli",&tel);
								  insereFimLista(&(*raiz)->proxtel,tel);
									break;
								case 2:
								  printf("Digite o numero do telefone que sera removido: ");
								  scanf("%lli",&tel);
								  removeNo(&(*raiz)->proxtel,tel);
									break;
								case 0://sair
									break;
								default:
									puts("Opcao invalida!!!");
							}		
						}while(escolhaTel != 0);
						break;
					default:
						puts("Opcao invalida!!!");		
				}
			}while(escolhaAltera != 0);
		}
		else
		{
			if(cpf > (*raiz)->cpf)
			{
				return alteraCadastro(&(*raiz)->dir,inicioArvore,cpf);
			}
			else
			{
				return alteraCadastro(&(*raiz)->esq,inicioArvore,cpf);
			}
			
		}
	}
	
}		//Working

//Entradas: Raiz da árvore e o CPF que será removido;
//Saídas: Nada. Simplesmente executa a ação e atualiza a raiz primária;
void remEspecialAltera(no **raiz, long long int n){
	
      no *aux;

	//Verifica se a raiz não é nula;
	if((*raiz)){
		
		if((*raiz)->cpf == n){					//É o que eu procuro?
			
			if(!(*raiz)->dir){					//Dir dele é null?
				
									
				(*raiz) = (*raiz)->esq;			//remove a posição sem dar free nela
			}
			else if(!(*raiz)->esq){				//Esq dele é null?
				
									
				(*raiz) = (*raiz)->dir;			//remove a posição sem dar free nela
			}
												//Se não for folha:
			else {
				aux = (*raiz);
				
				(*raiz) = remEspecialAltera2(&(*raiz)->esq); 
				(*raiz)->dir = aux->dir;
				(*raiz)->esq = aux->esq;
			} 
		}
		else if(n > (*raiz)->cpf) {				//Se não, continuar procurando;
				 remEspecialAltera(&(*raiz)->dir, n);
		}else{
				 remEspecialAltera(&(*raiz)->esq, n);
		}
	}
}							//Working

//Entradas: Raiz da árvore;
//Saídas: Nó que será o substituto do que foi selecionado para ser removido;
no *remEspecialAltera2(no **raiz){					// remove e retorna o ultimo a direita e coloca em seu lugar ultimo->esq
	
	long long int x;
	no *aux;
	
	if(!(*raiz)->dir){							//Ao conseguir achar;
		aux = (*raiz);
		(*raiz) = (*raiz)->esq;
		return aux;
	}
	return remEspecialAltera2(&(*raiz)->dir);			//Vai buscar sempre o maior dos menores;
}											//Working

///Entradas: Início da árvore, raiz;
//Saídas: 1 para sucesso;
int CadastraEspecialAltera(no **inicioArvore, no *raiz){
 
 if(*inicioArvore == NULL) {
 	*inicioArvore = raiz;
 	printf("cn");
 	return 1;
 	
 } // sucesso
 
 if(raiz->cpf == (*inicioArvore)->cpf) 
	return 0;			//cpf ja existente
 
    if(raiz->cpf > (*inicioArvore)->cpf)				//verifica se deve percorrer a arvore para a direita
    {
		if((*inicioArvore)->dir == NULL)					//verifica se ao percorrer pra direita encontraria uma posição vazia
		{
		   (*inicioArvore)->dir = raiz;				 //cadastra
		  return 1;			//sucesso
		
		}
		else
		{
		  return CadastraEspecialAltera(&(*inicioArvore)->dir,raiz);//vai para a direita da arvore
		}
    } 
    else	//percorre a arvore para esquerda
    {
	      
		if((*inicioArvore)->esq == NULL)					//verifica se ao percorrer para a esquerda encontratia uma posição vazia
		{
		  (*inicioArvore)->esq = raiz;				//cadastra
		  return 1;			//sucesso
		}
		else
		{
		  return CadastraEspecialAltera(&(*inicioArvore)->esq,raiz);//vai para a esquerda
		}
    }
}					//Working
