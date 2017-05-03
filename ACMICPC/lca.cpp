using namespace std;
const int N = 100000 + 5;
#define D 20
vector<int>tree[N];
int dep[N], shortcut[D][N];

int get_lca(int a, int b) {
	if (dep[a] < dep[b]) {
		swap(a, b);
	}
	for (int i = D - 1; ~i; i --) {
		if (dep[a] - dep[b] >> i & 1) {
			a = shortcut[i][a];
		}
	}

	if (a == b) return a;
	for (int i = D - 1; ~i; i --) {
		if (shortcut[i][a] != shortcut[i][b]) {
			a = shortcut[i][a];
			b = shortcut[i][b];
		}
	}

	return shortcut[0][a];
}

void initial(int n) {
	vector<int> Q;
	int *parent = shortcut[0];
	parent[0] = -1;
	dep[0] = 0;
	Q.push_back(0);
	for (int head = 0; head < int(Q.size()); head ++) {
		int u = Q[head];
		for (int i = 0; i < int(tree[u].size()); i ++) {
			int v = tree[u][i];
			if (v != parent[u]) {
				parent[v] = u;
				dep[v] = dep[u] + 1;
				Q.push_back(v);
			}
		}
	}
	for (int i = 1; i < D; i ++) {
		for (int j = 0; j < n; j ++) {
			int &res = shortcut[i][j];
			res = shortcut[i-1][j];
			if (~res) {
				res = shortcut[i-1][res];
			}
		}
	}
}
