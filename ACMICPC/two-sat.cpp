const int N = 50000 + 1;

int pos[N + N], color[N], rev[N + N], id[N + N];
int scc[N + N], pre[N + N], dfs_clock, sccno;
bool choose[N + N];
int ans[N];
vector<int> G[N + N];
stack<int> S;

int dfs(int u) {
	int lowu = pre[u] = ++ dfs_clock;
	S.push(u);
	for(int v: G[u]) {
		if(!pre[v]) {
			lowu = min(lowu, dfs(v));
		} else if(!scc[v]) {
			lowu = min(lowu, pre[v]);
		}
	}
	if(pre[u] == lowu) {
		sccno ++;
		for(int v = -1; v != u;) {
			v = S.top();
			S.pop();
			scc[v] = sccno;
		}
	}
	return lowu;
}

bool solve(int n) {
	for(int u = 1; u <= n + n; u ++) if(!pre[u]) {
		dfs(u);
	}
	for(int u = 1; u <= n + n; u ++) {
		if(scc[u] == scc[rev[u]]) {
			return false;
		} else {
			choose[u] = scc[u] < scc[rev[u]];
		}
	}
	return true;
}
