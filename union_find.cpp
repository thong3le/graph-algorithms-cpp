#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

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
  printf("Assume that there are 5 disjoint sets initially\n");
  UnionFind UF(5); // create 5 disjoint sets
  printf("%d\n", UF.num_disjoint_sets()); // 5
  UF.union_set(0, 1);
  printf("%d\n", UF.num_disjoint_sets()); // 4
  UF.union_set(2, 3);
  printf("%d\n", UF.num_disjoint_sets()); // 3
  UF.union_set(4, 3);
  printf("%d\n", UF.num_disjoint_sets()); // 2
  printf("isSameSet(0, 3) = %d\n", UF.is_same_set(0, 3)); // will return 0 (false)
  printf("isSameSet(4, 3) = %d\n", UF.is_same_set(4, 3)); // will return 1 (true)
  for (int i = 0; i < 5; i++) // findSet will return 1 for {0, 1} and 3 for {2, 3, 4}
    printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, UF.find_set(i), i, UF.size_of_set(i));
  UF.union_set(0, 3);
  printf("%d\n", UF.num_disjoint_sets()); // 1
  for (int i = 0; i < 5; i++) // findSet will return 3 for {0, 1, 2, 3, 4}
    printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, UF.find_set(i), i, UF.size_of_set(i));
  return 0;
}