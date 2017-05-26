#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
	int V, neighbors, id, weight;
	vector<vii> adj_list;

	scanf("%d", &V);
	adj_list.assign(V, vii());
	for (int i = 0; i < V; i++){
		scanf("%d", &neighbors);
		for(int j = 0; j < neighbors; j++){
			scanf("%d %d", &id, &weight);
			adj_list[i].push_back(ii(id-1, weight));
		}
	}

	printf("Neighbors of vertex 0:\n");
	for(vii::iterator j = adj_list[0].begin(); j != adj_list[0].end(); j++)
		printf("Edge 0-%d (weight = %d)\n", j->first, j->second);

	return 0;
}