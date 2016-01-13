const int N = 100000 + 1;

struct Edge {
	int v, x, w;
} E[N << 1];

int l[N], tot;

void add(int u, int v, int w) {
	E[tot] = (Edge) {v, l[u], w};
	l[u] = tot ++;
}

int dep[N], heavy[N], top[N], fa[N], siz[N];
int m;

void dfs(int u) {
	siz[u] = 1;
	heavy[u] = -1;
	for(int i = l[u], v; ~i; i = E[i].x) {
		v = E[i].v;
		if(v != fa[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			siz[u] += siz[v];
			if(heavy[u] == -1 || siz[heavy[u]] < siz[v]) {
				heavy[u] = v;
			}
		}
	}
}

int ID[N];
void Label(int u, int tp) {
	ID[u] = ++ m;
	top[u] = tp;
	if(~heavy[u])	Label(heavy[u], tp);
	for(int i = l[u], v; ~i; i = E[i].x) {
		v = E[i].v;
		if(v != fa[u] && heavy[u] != v) {
			Label(v, v);
		}
	}
}

int query(int a, int b) {  // or update
	while(top[a] != top[b]) {
		if(dep[top[a]] > dep[top[b]]) {
			//segTree [ID[top[a]], ID[a]];
			a = fa[top[a]];
		} else {
			//segTree [ID[top[b]], ID[b]];
			b = fa[top[b]];
		}
	}
	if(a == b) {
		// return answer if weight is on edge
	}
	if(dep[a] > dep[b]) {
		// segTree [ID[b] + 1, ID[a]]
	} else {
		// segTree [ID[a] + 1, ID[b]]
	}
	// return answer
}

void init() {
	dep[0] = m = tot = 0;
	memset(l, -1, sizeof l);
	fa[0] = -1;
	dfs(0);
	Label(0, 0);
}
