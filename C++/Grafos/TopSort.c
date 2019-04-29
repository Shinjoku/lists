#include <stdio.h>
#include <stdlib.h>

// Constantes:
#define MAXN 41
//------------------------------

int main(){
    
// Variáveis:
    int n;          // número de vértices
    int m;          // número de arestas
    int index = 0;  // Índice do vetor grau
    int x, y;       // Dependência/Tarefa
    int ini, v;
    int fimGrafo = 0, fimGrau = 0, fimGrauZ = 0;
    int i, j;          // Iterador
    
    // Matriz q contém o grafo
    int grafo[MAXN][2] = {0};
    
    // Vetor que fala quantos graus cada vértice tem;
    int grau[MAXN] = {0};
    
    // Lista que contém os vértices com grau 0
    int grauZero[MAXN] = {0}; // dos vértices de grau zero
//---------------

    printf("Digite o número de vértices e arestas: ");
    scanf("%d %d", &n, &m);
    
    // Obtenção das dependencias/tarefas
    puts("Digite as dependencias/tarefas: ");
    
    // Custo: 4 * m
    for(i = 0; i < m; i++){
        scanf("%d %d", &x, &y);
        
        // tarefa X tem que ser executada antes da tarefa Y
        // Aumenta grau de Y (Tarefa)
        grau[y]++;
        //grafo[x].push_back(y);
        for(j = 0; j < 2; j++)
            if(grafo[x][j] == 0){
                grafo[x][j] = y;
                break;
            }
    }
    //--------------
    
    // Custo: 2 * n
    for(i = 1; i <= n; i++){
        if(grau[i] == 0){
            grauZero[fimGrauZ] = i;
            fimGrauZ++;
        }
    }
    //------------

    
    // o procedimento a ser feito é semelhante a uma BFS
    
    // Custo: 10 * fimGrauZ
    ini = 0;
    while(ini < fimGrauZ){
        
        int atual = grauZero[ini];
        ini++;
        
        for(i = 0; i < 2; i++){
            
            v = grafo[atual][i];
            
            grau[v]--;
            if(grau[v] == 0){
                grauZero[fimGrauZ] = v; // se o grau se tornar zero, acrescenta-se a lista
                fimGrauZ++;
            }
        }
    }
    
    // agora, se na lista não houver N vértices,
    // sabemos que é impossível realizar o procedimento
    
    // Custo: MAXN
    if(fimGrauZ < n){
        printf("Este grafo não tem ordenação topológica possivel.\n");
    }
    else {
        printf("Ordenação topológica possivel:\n");
        for(i = 0; i < MAXN; i++)
            printf("%d ", grauZero[i]);
        printf("\n");
    }
    
    return 0;
}
/* Comentários:
    Este código utiliza de uma representação computacional do grafo para analisar e ordenar
    o mesmo.
    Complexidade: O(|E| + |V|);
    Função: 4m + 2n + 10fimGrauZ + MAXN;