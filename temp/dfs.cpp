#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define sz(a) int((a).size())
#define pb push_back
#define all(c) c.begin(), c.end()
#define tr(c, i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())


int N;
vvi G;
vi visited;

void dfs(int i){
	if (!visited[i]){
		visited[i] = true;
		cout << i << endl;
		//for_each(begin, end, f) call f on each element in range
		for_each(all(G[i]), dfs);
	}
}



bool check_connected_dfs(){
	int s = 0;
	visited = vi(N, false);
	dfs(s);
	return (find(all(visited), 0) == visited.end());
}

bool check_connected_bfs(){
	int s = 0;
	visited = vi(N, false);
	queue<int> Q;
	Q.push(s);
	visited[s] = true;
	while (!Q.empty()){
		int i = Q.front();
		Q.pop();
		tr(G[i], it) {
			if (!visited[*it]) {
				visited[*it] = true;
				Q.push(*it);
			}
		}
	}
	return (find(all(visited), 0) == visited.end());
}

int main(){
	N = 5;
	int data[5][3] = {{2, 4},{2, 3, 4},{0, 1, 3},{1, 2, 4}, {0, 1, 3}};
	for (int i = 0; i < N; i++){
		G.push_back(vi(data[i], data[i] + sizeof(data[i])/sizeof(data[i][0])));
	}
	visited.assign(N, false);
	dfs(0);



	return 0;
}

