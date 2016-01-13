template<int N, typename T> struct MaxFlow {
	int src, sink, list[N], tot, Q[N], s, t, d[N], cur[N];
	struct Edge { int v, x; T cap; } E[555555];
	void init() {
		memset(list, -1, sizeof list);
		tot = 0;
	}
	void addedge(int u, int v, T cap) {
		E[tot] = (Edge) {v, list[u], cap};
		list[u] = tot ++;
		E[tot] = (Edge) {u, list[v], 0};
		list[v] = tot ++;
	}
	bool bfs() {
		memset(d, -1, sizeof d);
		memcpy(cur, list, sizeof cur);
		d[src] = 0;
		s = t = 0;
		Q[t ++] = src;
		while(s < t) {
			int u = Q[s ++];
			for(int i = list[u]; ~i; i = E[i].x) {
				Edge &e = E[i];
				if(d[e.v] == -1 && E[i].cap > 0) {
					d[Q[t ++] = e.v] = d[u] + 1;
				}
			}
		}
		return d[sink] != -1;
	}
	T dfs(int u, T in) {
		if(u == sink)	return in;
		T flow = 0, f;
		for(int &i = cur[u]; ~i; i = E[i].x) {
			Edge &e = E[i];
			if(e.cap > 0 && d[e.v] == d[u] + 1) {
				if(f = dfs(e.v, std::min(in - flow, e.cap))) {
					flow += f;
					e.cap -= f;
					E[i^1].cap += f;
					if(flow == in)	break;
				}
			}
		}
		if(flow < in)	d[u] = -1;
		return flow;
	}
	T dinic(int _src, int _sink) {
		src = _src;
		sink = _sink;
		T flow = 0;
		while(bfs())	flow += dfs(src, inf);
		return flow;
	}
};
MaxFlow<105, int> F;

