#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

//------------------------------
#define MAXN 100100

int n; // número de vértices
int m; // número de arestas

//Vetor de listas
vector<int> grafo[MAXN];

// Listagem de Graus para cada vértice
int grau[MAXN];

// Lista os vértices de grau 0
vector<int> lista; // dos vértices de grau zero
//------------------------------

int main(){
	
	int x, y;   // Dependência/Tarefa
	int ini, v;
	int i;      // Iterador
	
	
	cout << "Digite o número de vértices e arestas: ";
	scanf("%d %d", &n, &m);
	
	// Obtenção das dependencias/tarefa
	cout << "Digite as dependencias/tarefas: ";
	for(i = 1; i <= m; i++){
		scanf("%d %d", &x, &y);
		
		// tarefa X tem que ser executada antes da tarefa Y
		grau[y]++;
		grafo[x].push_back(y);
	}
	
	for(int i=0; i < MAXN; i++)
		for(int j=0; j < grafo[i].size(); j++)
			cout << "i :" << i << "  j: " << j << "  Valor: " << grafo[i][j] << " " << endl;
			
	
	for(i = 1; i <= n; i++){
		if(grau[i] == 0)
			lista.push_back(i);
	}
	
	
	// o procedimento a ser feito é semelhante a uma BFS
	
	ini = 0;
	while(ini < (int) lista.size()){
		
		int atual = lista[ini];
		ini++;
		
		for(int i = 0; i < (int) grafo[atual].size(); i++){
			
			v = grafo[atual][i];
			
			grau[v]--;
			if(grau[v] == 0)
				lista.push_back(v); // se o grau se tornar zero, acrescenta-se a lista
		}
	}
	
	// agora, se na lista não houver N vértices,
	// sabemos que é impossível realizar o procedimento
	
	if((int) lista.size() < n)
		printf("impossivel\n");
	else{
		for(i = 0; i < (int) lista.size(); i++)
			printf("%d ", lista[i]);
		printf("\n");
	}
	
	return 0;
}