const int MAX_N = 100000 + 2;
const int MAX_M = 100000 + 2;
typedef pair<int, int> P;

struct Edge {
	int v, x;
} E[MAX_M * 10];
// 8->3
int tot; // clear in each case
template <int N> 
struct AdjList {
	int l[N];
	inline void addEdge(int u, int v) {
		E[tot] = (Edge) {v, l[u]};
		l[u] = tot ++;
	}

	void init() {
		memset(l, -1, sizeof l);
	}
};

namespace BCC {
	const int N = MAX_N;
	const int M = MAX_M;
	set<int> p2c[N]; // node to bcc
	set<P> c2e[N]; // bcc to node 
	map<P, int> e2c; // edge to bcc
	P S[M], tmp;
	int cut[N], dep[N], low[N], ori[N + N];
	// cut: newID of cut node, ori: original graph id 
	int *l;
	Edge *E;
	int n, bcc_cnt, top;

	void Pop(P y) {
		do {
			tmp = S[-- top];
			p2c[tmp.first].insert(bcc_cnt);
			p2c[tmp.second].insert(bcc_cnt);
			if(tmp.first > tmp.second)	swap(tmp.first, tmp.second);
			c2e[bcc_cnt].insert(tmp);
			e2c[tmp] = bcc_cnt;
		} while(top && S[top] != y);
		bcc_cnt ++;
	}

	void dfs(int u, int D, int ind) {
		dep[u] = low[u] = D;
		int child = 0;
		for(int i = l[u]; ~i; i = E[i].x) {
			if(ind == (i^1))	continue;
			int v = E[i].v;
			S[top ++] = {u, v};
			if(dep[v] >= 0) {
				if(dep[v] > dep[u])	top --;
				low[u] = min(low[u], dep[v]);
				continue;
			}
			child ++;
			dfs(v, D+1, i);
			low[u] = min(low[u], low[v]);
			if(low[v] >= dep[u]) {
				cut[u] = 1;
				Pop(P(u, v)); // find a bcc
			}
		}
		if(child == 1 && ind < 0)	cut[u] = -1;
	}

	int rebuild(AdjList<N + N> &adj) {
		int c = bcc_cnt;
		rep(i, n) if(cut[i] != -1) {
			cut[i] = c ++;
			ori[c-1] = i;
		}
		adj.init();
		set<int>::iterator it;
		rep(u, n) {
			if(cut[u] == -1)	continue;
			for(it = p2c[u].begin(); it != p2c[u].end(); it ++) {
				adj.addEdge(cut[u], *it);
				adj.addEdge(*it, cut[u]);
			}
		}
		return c;
	}

	void init(int _n, int *_l, Edge *_E) {
		n = _n; l = _l; E = _E;
		rep(i, n)	dep[i] = cut[i] = -1;
		rep(i, n)	p2c[i].clear(), c2e[i].clear();
		e2c.clear();
		bcc_cnt = top = 0;
		rep(i, n) if(dep[i] == -1) {
			dfs(i, 0, -1);
		}
	}
};
