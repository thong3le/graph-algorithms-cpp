#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define WHITE -1
#define BLACK 1

vector<vii> adj_list;

vi dfs_num;
int num_cc;

void print_message(string m){
	printf("==============================================\n");
	printf("%s\n", m.c_str());
	printf("==============================================\n");
}

void dfs(int s) {
	printf(" %d\n", s);
	dfs_num[s] = BLACK;
	for(int j = 0; j < (int)adj_list[s].size(); j++){
		ii v = adj_list[s][j];
		if (dfs_num[v.first] == WHITE) 
			dfs(v.first);
	}
}

vi topo_sort;

void topological_order(int s){
	dfs_num[s] = BLACK;
	for (int j = 0; j < (int)adj_list[s].size(); j++){
		ii v = adj_list[s][j];
		if (dfs_num[s] == WHITE)
			topological_order(v.first);
	}
	topo_sort.push_back(s);
}

#define GRAY 2
vi dfs_parent;
void graph_check(int s){
	dfs_num[s] = GRAY;
	for(int j = 0; j < (int)adj_list[s].size(); j++){
		ii v = adj_list[s][j];
		if (dfs_num[v.first] == WHITE){
			dfs_parent[v.first] = s;
			graph_check(v.first);
		}
		else if (dfs_num[v.first] == GRAY){
			if (v.first == dfs_parent[s])
				printf(" Bidirectional (%d, %d) - (%d, %d)\n", s, v.first, v.first, s);
			else 
				printf(" Back Edge (%d, %d) (Cycle)\n", s, v.first);
		}
		else if (dfs_num[v.first] == BLACK)
			printf(" Forward/Cross Edge (%d, %d)\n", s, v.first);
	}
	dfs_num[s] = BLACK;
}

vi dfs_low;
vi articulation_vertex;
int dfs_number_counter, dfs_root, root_children;

void articulation_point_and_bridge(int s){
	dfs_low[s] = dfs_num[s] = dfs_number_counter++;
	for(int j = 0; j < (int)adj_list[s].size(); j++){
		ii v = adj_list[s][j];
		if (dfs_num[v.first] == WHITE) {
			dfs_parent[v.first] = s;
			if (s == dfs_root) root_children++;

			articulation_point_and_bridge(v.first);

			if (dfs_low[v.first] >= dfs_num[s])
				articulation_vertex[s] = true;
			if (dfs_low[v.first] > dfs_num[s])
				printf(" Edge (%d, %d) is a bridge\n", s, v.first);
			dfs_low[s] = min(dfs_low[s], dfs_low[v.first]);
		}
		else if (v.first != dfs_parent[s])
			dfs_low[s] = min(dfs_low[s], dfs_low[v.first]);
	}
}

vi S, visited;
int num_scc;
void tarjan_scc(int s){
	dfs_low[s] = dfs_num[s] = dfs_number_counter++;
	S.push_back(s);
	visited[s] = 1;
	for (int j = 0; j < (int)adj_list[s].size(); j++){
		ii v = adj_list[s][j];
		if (dfs_num[v.first] == WHITE)
			tarjan_scc(v.first);
		if (visited[v.first])
			dfs_low[s] = min(dfs_low[s], dfs_low[v.first]);
	}

	if (dfs_low[s] == dfs_num[s]) {
		printf("SCC %d\n", ++num_scc);
		while (1) {
			int v = S.back(); S.pop_back(); visited[v] = 0;
			printf(" %d", v);
			if (s == v) break;
		}
		printf("\n");
	}
}

int main(){
	int V, neighbors, id, weight;
	scanf("%d", &V);
	adj_list.assign(V, vii());
	for(int i = 0; i < V; i++){
		scanf("%d", &neighbors);
		for(int j = 0; j < neighbors; j++) {
			scanf("%d %d", &id, &weight);
			adj_list[i].push_back(ii(id, weight));
		}
	}

	print_message("Standard DFS Demo");
	num_cc = 0;
	dfs_num.assign(V, WHITE);
	for (int i = 0; i < V; i++)
		if (dfs_num[i] == WHITE)
			printf("Component %d:\n", ++num_cc), dfs(i), printf("\n");
	printf("There are %d connected components\n", num_cc);

	print_message("Topological Sort (input must be a DAG)");
	topo_sort.clear();
	dfs_num.assign(V, WHITE);
	for(int i = 0; i < V; i++)
		if (dfs_num[i] == WHITE)
			topological_order(i);
	reverse(topo_sort.begin(), topo_sort.end());
	for(int i = 0; i < (int)topo_sort.size(); i++)
		printf(" %d\n", topo_sort[i]);
	printf("\n");

	print_message("Articulation Points & Bridges (the input graph must be UNDIRECTED)");
  	dfs_number_counter = 0;
  	dfs_num.assign(V, WHITE);
  	dfs_low.assign(V, 0);
  	dfs_parent.assign(V, -1);
  	articulation_vertex.assign(V, 0);
  	printf("Brigdes:\n");
  	for(int i = 0; i < V; i++)
  		if (dfs_num[i] == WHITE){
  			dfs_root = i; 
  			root_children = 0;
  			articulation_point_and_bridge(i);
  			articulation_vertex[dfs_root] = (root_children > 1);
  		}
  	printf("Articulation Points:\n");
  	for (int i = 0; i < V; i++)
  		if (articulation_vertex[i])
  			printf(" Vertex %d\n", i);

	print_message("Strongly Connected Components (the input graph must be DIRECTED)");
  	dfs_num.assign(V, WHITE); dfs_low.assign(V, 0); visited.assign(V, 0);
  	dfs_number_counter = num_scc = 0;
  	for (int i = 0; i < V; i++)
    	if (dfs_num[i] == WHITE)
      		tarjan_scc(i);
		
	return 0;
}