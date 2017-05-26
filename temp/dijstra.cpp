#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

#define sz(a) int((a).size())
#define pb push_back
#define all(c) c.begin(), c.end()
#define tr(c, i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())


int N;
vvii G;
vi D;

void dijstra_pq(int s){
	D = vi(N, 987654321);
	priority_queue< ii, vector<ii>, greater<ii> > Q;
	D[s] = 0;
	Q.push(ii(s, 0));
	while (!Q.empty()) {
		ii top = Q.top();
		Q.pop();
		int v = top.second, d = top.first;
		if (d <= D[v]) {
			tr(G[v], it) {
				int v2 = it->first, cost = it->second;
				if (D[v2] > D[v] + cost) {
					D[v2] = D[v] + cost
					Q.push(ii(D[v2], v2));
				}
			}
		}
	}
}

void dijstra_set(int s) {
	D = vi(N, 987654321);
	set<ii> Q;
	D[s] = 0;
	Q.insert(ii(s, 0));
	while (!Q.empty()) {
		ii top = *Q.begin();
		Q.erase(Q.begin());
		int v = top.second, d = top.first;

		tr(G[v], it) {
			int v2 = it->first, cost = it->second;
			if (D[v2] > D[v] + cost) {
				if (D[v2] ! = 987654321) {
					Q.erase(Q.find(ii(D[v2], v2)));
				}
				D[v2] = D[v] + cost;
				Q.insert(ii(D[v2], v2));
			}
		}
	}
}

int main(){

	return 0;
}