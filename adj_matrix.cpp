#include <cstdio>
#include <vector>

using namespace std;

#define N 100

int main(){
	int adj_matrix[N][N];
	int V;
	scanf("%d", &V);
	for(int i = 0; i < V; i++){
		for (int j = 0; j < V; j++)
			scanf("%d", &adj_matrix[i][j]);
	}
	printf("Neighbors of vertex 0:\n");
	for(int j = 0; j < V; j++)
		if (adj_matrix[0][j])
			printf("Edge 0-%d (weight = %d)\n", j, adj_matrix[0][j]);
	return 0;
}