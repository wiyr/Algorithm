const int N = 100000;

struct Edge { 
	int u, v;
}E[N];
struct ADJ {
	vector<pair<int, int>> G[N];

	void init(int n) {
		rep(u, n)	G[u].clear();
	}

	void addedge(int u, int v, int w) {
		G[u].push_back({v, w});
	}

}adj, adj2;

struct bidirGraph {
	int pre[N], dfs_clock;
	bool qiao[N];
	queue<int> Q;
	vector<pair<int, int>> *G;

	int dfs(int u, int e) {
		int lowu = pre[u] = ++ dfs_clock;
		for(auto &t: G[u]) {
			int v = t.first, w = t.second;
			if(w == (e^1))	continue;
			if(!pre[v]) {
				int lowv = dfs(v, w);
				lowu = min(lowu, lowv);
				if(lowv > pre[u]) {
					qiao[w>>1] = true;
				}
			} else if(pre[v] < pre[u]) {
				lowu = min(lowu, pre[v]);
			}
		}
		return lowu;
	}

	int Main(int n, vector<pair<int, int>> *_G, int *label) {
		G = _G;
		dfs_clock = 0;
		memset(qiao, false, sizeof qiao);
		rep(u, n) {
			label[u] = -1;
			pre[u] = 0;
		}
		rep(u, n) if(!pre[u]) {
			dfs(u, -1);
		}
		int c = 0;
		rep(i, n) {
			if(label[i] >= 0)	continue;
			Q.push(i);
			label[i] = c;
			while(!Q.empty()) {
				int u = Q.front(), v, w;
				Q.pop();
				for(auto &t: G[u]) {
					v = t.first, w = t.second;
					if(qiao[w>>1] || label[v] >= 0)	continue;
					Q.push(v);
					label[v] = c;
				}
			}
			c ++;
		}
		return c;
	}
}ins;

int label[N];

void rebuild(int m) {
	int u, v;
	rep(i, m) {
		if(ins.qiao[i]) {
			u = label[E[i].u];
			v = label[E[i].v];
			adj2.G[u].push_back({v, i});
			adj2.G[v].push_back({u, i});
		}
	}
}
