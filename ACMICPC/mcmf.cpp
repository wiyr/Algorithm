const int inf = 1e9;
template<int N, typename T> struct CostFlow {
	int src, sink, list[N], tot, Q[N], p[N], inq[N];
	T d[N];
	struct Edge { int v, x, cap; T w; } E[555555];
	void init() {
		memset(list, -1, sizeof list);
		tot = 0;
	}
	void addedge(int u, int v, int cap, T w) {
		E[tot] = (Edge) {v, list[u], cap, w};
		list[u] = tot ++;
		E[tot] = (Edge) {u, list[v], 0, -w};
		list[v] = tot ++;
	}
	void mcmf(int s, int t, int &flow, T &cost) {
		cost = flow = 0; src = s, sink = t;
		while(true) {
			std::fill(d, d + N, (T)inf);
			memset(inq, 0, sizeof inq);
			d[src] = 0;
			s = t = 0;
			Q[t ++] = src;
			while(s != t) {
				int u = Q[s ++];
				inq[u] = 0;
				if(s == N)	s = 0;
				for(int i = list[u]; ~i; i = E[i].x) {
					Edge &e = E[i];
					if(e.cap && d[e.v] > d[u] + e.w) {
						d[e.v] = d[u] + e.w;
						p[e.v] = i;
						if(!inq[e.v]) {
							Q[t ++] = e.v;
							if(t == N)	t = 0;
							inq[e.v] = 1;
						}
					}
				}
			}
			if(d[sink] == inf)	break;
			//	if(d[sink] >= 0)	break;
			int c = inf;
			for(int v = sink; v != src; v = E[p[v] ^ 1].v) 
				c = std::min(c, E[p[v]].cap);
			cost += c * d[sink];
			flow += c;
			for(int v = sink; v != src; v = E[p[v] ^ 1].v) {
				E[p[v]].cap -= c;
				E[p[v] ^ 1].cap += c;
			}
		}
	}
};
CostFlow<1024, int> F;
