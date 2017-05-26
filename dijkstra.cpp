#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define INF 1000000000

int main(){
	int V, E, s, u, v, w;
	vector<vii> adj_list;
	scanf("%d %d %d", &V, &E, &s);

	adj_list.assign(V, vii());
	for(int i = 0; i < E; i++){
		scanf("%d %d %d", &u, &v, &w);
		adj_list[u].push_back(ii(v, w));  //directed graph
	}

	vi dist(V, INF); dist[s] = 0;
	priority_queue< ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0, s));

	while (!pq.empty()) {
		ii front = pq.top(); pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;
		for (int j = 0; j < (int)adj_list[u].size(); j++){
			ii v = adj_list[u][j];
			if (dist[u] + v.second < dist[v.first]) {
				dist[v.first] = dist[u] + v.second;
				pq.push(ii(dist[v.first], v.first));
			}
		}
	}

	for (int i = 0; i < V; i++)
		printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

	return 0;
}