#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;

int main(){
	priority_queue< pair<int, ii> > edge_list;
	int E, a, b, weight;

	scanf("%d", &E);
	for(int i = 0; i < E; i++){
		scanf("%d %d %d", &a, &b, &weight);
		edge_list.push(make_pair(-weight, ii(a, b)));
	}

	for(int i = 0; i < E; i++){
		pair<int, ii> edge = edge_list.top(); edge_list.pop();
		printf("Weight: %d (%d-%d)\n", -edge.first, edge.second.first, edge.second.second);
	}

	return 0;
}