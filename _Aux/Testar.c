void RemoverNo(Arvore **raiz, int n)
{
	Arvore *aux;

	//verifica se não é algum dos finais da arvore
	if (*raiz != NULL)
	{
		//verifica se a posição atual é a buscada
		if (n != (*raiz)->valor)
		{
			//verifica como percorrer a arvore em busca do numero
			if (n > (*raiz)->valor)
			{
				//vai para a direita
				RemoverNo(&(*raiz)->dir,n);
			}
			else
			{
				//vai para a esquerda
				RemoverNo(&(*raiz)->esq,n);
			}
		}
		else
		{
			//verifica se a posição encontrada é uma folha (não possui filhos)
			if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
			{
				//salva a posição que sera removida em uma auxiliar
				aux = (*raiz);
				//remenda a arvore/remove a posição da arvore
				*raiz = NULL;
				//desaloca a posição removida
				free(*raiz);
			}
			else
			{
				//verifica se a posição possui 1 filho na esquerda
				if ((*raiz)->esq != NULL && (*raiz)->dir == NULL)
				{
					//salva a posição que sera removida em uma auxiliar
					aux = (*raiz);
					//remenda a arvore/remove a posição da arvore
					(*raiz) = (*raiz)->esq;
					//desaloca a posição removida
					free(aux);
				}
				else
				{
					//verifica se a posição possui 1 filho na direita
					if((*raiz)->esq == NULL && (*raiz)->dir != NULL)
					{
						//salva a posição que sera removida em uma auxiliar
						aux = (*raiz);
						//remenda a arvore/remove a posição da arvore
						(*raiz) = (*raiz)->dir;
						//desaloca a posição removida
						free(aux);
					}
					else//posição possui filhos tanto na direita quanto na esquerda
					{
						//remenda a matriz setando o valor da posição que sera removida com o maior valor do lado esquero da matriz ou menor valor do lado direito
						(*raiz)->valor = MaiorValor((*raiz)->esq);
						//chamada recursiva da função RemoveNó para remover a posição que serviu de remendo
						RemoverNo(&(*raiz)->esq, (*raiz)->valor);
					}
				}
			}
		}
	}
}