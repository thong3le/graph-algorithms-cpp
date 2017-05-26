#include <iostream>
#include <vector>
#include <fstring>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int V, E, total_neighbors, id, weight, a, b;
int AdjMat[100][100];
priority_queue< pair<int, ii> > EdgeList;

void adjacency_matrix(){
	scanf("%d", &V);
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			scanf("%d", &AdjMat[i][j]);
	for (int i = 0; i < V; i++){
		printf("Neighbors of vertex %d:\n", i);
		for (int j = 0; j < V; j++)
			if (AdjMat[i][j])
				printf("	Edge %d-%d (weight = %d)\n", i, j, AdjMat[i][j]);
	}
	
}

void adjacency_list(){
	scanf("%d", &V);
	AdjList.assign(V, vii());
	for (int i = 0; i < V; i++){
		scanf("%d", &total_neighbors);
		for (int j = 0; j < total_neighbors; j++){
			scanf("%d %d", &id, &weight);
			AdjList[i].push_back(ii(id-1, weight));
		}
	}

	for (int i = 0; i < V; i++){
		printf("Neighbors of vertex %d:\n", i);
		for (vii::iterator j = AdjList[i].begin(); j != AdjList[i].end(); j++)
			printf("	Edge %d-%d (weight = %d)\n", i, j->first, j->second);
	}
}

void edges_list(){
	scanf("%d", &E);
	for (int i = 0; i < E; i++){
		scanf("%d %d %d", &a, &b, &weight);
		EdgeList.push(make_pair(-weight, ii(a, b)));
	}

	for (int i = 0; i < E; i++){
		pair<int, ii> edge = EdgeList.top(); EdgeList.pop();
		printf("weight: %d (%d-%d)\n", -edge.first, edge.second.first, edge.second.second);
	}
}



vector< vector<int> > sample() {
	vector< vector<int> > graph;
	vector<int> a;
	a.push_back(2);
	graph.push_back(a);
	vector<int> b;
	b.push_back(2);
	b.push_back(3);
	graph.push_back(b);
	vector<int> c;
	c.push_back(0);
	c.push_back(1);
	c.push_back(3);
	graph.push_back(c);
	vector<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(4);
	graph.push_back(d);
	vector<int> e;
	e.push_back(3);
	graph.push_back(e);

	cout << "vertices that are adjacent to 3" << ':';
	for (int i = 0; i < graph[3].size(); i++)
		cout << graph[3][i] << ' ';
	cout << endl;
}


int main() {
	adjacency_list();
	return 0;
}