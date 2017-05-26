#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define INF 1000000000

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int V, E, a, b, s;
vector<vii> adj_list;
vi p;

void print_path(int u){
	if (u == s) {printf("%d", u); return;}
	print_path(p[u]);
	printf(" %d", u);
}

int main(){
	scanf("%d %d", &V, &E);
	adj_list.assign(V, vii());
	for (int i = 0; i < E; i++){
		scanf("%d %d", &a, &b);
		adj_list[a].push_back(ii(b, 0));
		adj_list[b].push_back(ii(a, 0));
	}

	s = 5;

	vi dist(V, INF); dist[s] = 0;
	queue<int> q; q.push(s);
	p.assign(V, -1);
	int layer = -1;
	bool is_bipartite = true;

	for(int i = 0; i < V; i++){
		printf("Vertex %d:", i);
		for(int j = 0; j < (int)adj_list[i].size(); j++){
			printf(" %d", adj_list[i][j].first);
		}
		printf("\n");
	}

	for(int i = 0; i < V; i++)
		printf("%d\n", dist[i]);

	while (!q.empty()){
		int u = q.front(); q.pop();
		if (dist[u] != layer) printf("\nLayer %d: ", dist[u]);
		layer = dist[u];
		printf("visit %d, ", u);
		for (int j = 0; j < (int)adj_list[u].size(); j++){
			ii v = adj_list[u][j];
			if (dist[v.first] == INF) {
				dist[v.first] = dist[u] + 1;
				p[v.first] = u;
				q.push(v.first);
			}
			else if (dist[v.first] % 2 == (dist[u] % 2))
				is_bipartite = false;
		}
	}

	printf("\nShortest path: ");
	print_path(7), printf("\n");
	printf("isBipartite? %d\n", is_bipartite);

	return 0;
}