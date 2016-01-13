int dep[N], num[N], Q[N], fa[N];
int balance[N];
bool isroot[N];
std::vector<int> G[N];

int bfs(int src) {
	int head = 0, tail = 0;
	Q[tail ++] = src;
	fa[src] = -1;	
	dep[src] = 1;
	while(head < tail) {
		int u = Q[head ++]; 
		num[u] = 1;
		balance[u] = 0;
		for(int v: G[u]) {
			if(v != fa[u] && !isroot[v]) {
				dep[v] = dep[u] + 1;
				fa[v] = u;
				Q[tail ++] = v;
			}
		}
	}
	for(int i = tail - 1; i > 0; i --) {
		int u = Q[i];
		num[fa[u]] += num[u]; 
		balance[fa[u]] = std::max(balance[fa[u]], num[u]);
	}
	return tail;
}

void _path(int u, int f) {
}

void divide(int u) {
	int n = bfs(u), s = u;
	rep(i, n) {
		u = Q[i];
		balance[u] = std::max(balance[u], n - num[u]);
		if(balance[u] < balance[s]) {
			s = u;
		}
	}
//	bfs(s);
	for(int v: G[s]) {
		if(isroot[v])	continue;
		_path(v, s);
	}
	isroot[s] = true;
	for(int v: G[s]) {
		if(!isroot[v]) {
			divide(v);
		}
	}
	isroot[s] = false;
}
