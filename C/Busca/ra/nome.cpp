int busca_por_ra(int ra, la inicio)
{
    while(inicio->prox != 0)
    {
        if(ra == inicio->ra)
        {
            printf("Nome: %s\nRA: %i\nNota:%.2f\n", inicio->nome, inicio->ra, inicio->nota);
            return 1;
        }

        inicio = inicio->prox;
    }
    return 0;
}

int busca_por_nome(char nome[], la inicio)
{
    while(inicio->prox != 0)
    {

        if(strcmp(nome, inicio->nome) == 0)
        {
            printf("Nome: %s\nRA: %i\nNota:%.2f\n", inicio->nome, inicio->ra, inicio->nota);
            return 1;
        }

        inicio = inicio->prox;
    }
    return 0;
}