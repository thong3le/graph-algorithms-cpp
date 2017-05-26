#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class UnionFind {
private:
	vi p, rank, set_size;
	int num_sets;
public:
	UnionFind(int N) {
		set_size.assign(N, 1); num_sets = N; rank.assign(N, 0);
		p.assign(N, 0); for(int i = 0; i < N; i++) p[i] = i;
	}
	bool is_same_set(int i, int j) { return find_set(i) == find_set(j);}
	int find_set(int i) { return (p[i] == i) ? i : (p[i] = find_set(p[i])); }
	void union_set(int i, int j) {
		if (!is_same_set(i, j)){
			num_sets--;
			int x = find_set(i), y = find_set(j);
			if (rank[x] > rank[y]) { p[y] = x; set_size[x] += set_size[y];}
			else { p[x] = y; set_size[y] += set_size[x]; if (rank[x] == rank[y]) rank[y]++;}
		}
	}
	int num_disjoint_sets() { return num_sets;}
	int size_of_set(int i) { return set_size[find_set(i)];}
};

int main() {
	int V, E, u, v, w;
	scanf("%d %d", &V, &E);
	vector< pair<int, ii> > edge_list;
	for(int i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &w);
		edge_list.push_back(make_pair(w, ii(u, v)));
	}

	sort(edge_list.begin(), edge_list.end());

	int mst_cost = 0;
	UnionFind UF(V);
	for (int i = 0; i < E; i++) {
		pair<int, ii> front = edge_list[i];
		if (!UF.is_same_set(front.second.first, front.second.second)){
			mst_cost += front.first;
			UF.union_set(front.second.first, front.second.second);
		}
	}

	printf("MST cost = %d (Kruskal's)\n", mst_cost);

	return 0;
}