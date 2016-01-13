//Manhattan距离最小生成树 POJ3241
// 边数O(n), 时间nlogn
struct BITnode {
	int w, p;
}C[N];
struct Point {
	int x, y, id;
	bool operator<(const Point &A)const{
		if(x != A.x)
			return x < A.x;
		return y < A.y;
	}
}P[N];
struct Edge{
	int u, v, w;
	bool operator<(const Edge & A)const{
		return w < A.w;
	}
}E[N * 10];
int n, tot;
int fa[N];
bool cmp(int *a, int *b) {
	return *a < *b;
}
void update(int x, int w, int p) {
	for(; x > 0; x -= (x & -x)) {
		if(C[x].w > w) {
			C[x].w = w;
			C[x].p = p;
		}
	}
}
int find(int x) {
	int ret = inf, p = -1;
	for(; x <= n; x += (x & -x)) {
		if(ret > C[x].w) {
			ret = C[x].w;
			p = C[x].p;
		}
	}
	return p;
}
int findfa(int x) {
	return x == fa[x] ? x : fa[x] = findfa(fa[x]);
}
void addedge(int u, int v, int w) {
	E[tot].u = u; E[tot].v = v;     E[tot].w = w;
	tot ++;
}
int dist(Point A, Point B) {
	return abs(A.x - B.x)+ abs(A.y - B.y);
}
int *l[N], dd[N];
// 离线处理不带修改的区间询问问题，按Manhattan距离顺序处理
/*void dfs(int x, int l, int r)  // Modui Algorithm
  { 
  v[x] = true; 
//Process right bound 
if (r < P[x].y) 
add(r + 1, [x].y); 
else if (r > P[x].y) 
remove(P[x].y + 1, r); 
//Process left bound 
if (l < P[x].x) 
remove(l, P[x].x - 1); 
else if (l > P[x].x) 
add(P[x].x, l - 1); 
ans[x] = cur; 
//Moving on to next query 
for (int i = head[x]; i; i = E[i].x) 
{ 
if (v[e[i].node]) continue; 
dfs(P[i].id, P[x].x, P[x].y); 
} 
//Revert changes 
//Process right bound 
if (r < P[x].y) 
remove(r + 1, P[x].y); 
else if (r > P[x].y) 
add(P[x].y + 1, r); 
//Process left bound 
if (l < P[x].x) 
add(l, P[x].x - 1); 
else if (l > P[x].x) 
remove(P[x].x, l - 1); 
} */
int main()
{
	int K, ans, pos;
	while(~scanf("%d%d", &n, &K)) {
		//Initialize
		tot = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%d%d", &P[i].x, &P[i].y);
			P[i].id = i;
		}
		//Solve
		for(int dir = 1; dir <= 4; dir ++) { // each point connect other just one point for every 45 degrees.
			//Coordinate transform - reflect by y=x and reflect by x=0
			if(dir == 2 || dir == 4) {
				for(int i = 1; i <= n; i ++)     swap(P[i].x, P[i].y);
			} else if(dir == 3) {
				for(int i = 1; i <= n; i ++)     P[i].x *= -1;
			}
			//Sort points according to x-coordinate
			sort(P + 1, P + n + 1);
			//Discretize
			for(int i = 1; i <= n; i ++)     dd[i] = P[i].y - P[i].x, l[i] = &dd[i];
			sort(l + 1, l + n + 1, cmp);
			/*
			   int cnt = 1;
			   for (int i = 2; i <= n; ++i)
			   if (*l[i] != *l[i - 1]) *l[i - 1] = cnt++;
			   else *l[i - 1] = cnt;
			 *l[n] = cnt;
			 */
			for(int i = 1; i <= n; i ++)     *l[i] = i;
			//Initialize BIT
			for(int i = 1; i <= n; i ++)     C[i].w = inf, C[i].p = -1;
			//Find points and add edges
			for(int i = n; i >= 1; i --) { // from x of most large
				pos = find(dd[i]); // find position which x + y small started at dd[i]
				if(pos != -1) {
					addedge(P[i].id, P[pos].id, dist(P[i], P[pos]));
				}
				update(dd[i], P[i].x + P[i].y, i); // is i not P[i].id !
			}
		}
		//Kruskal
		for(int i = 1; i <= n; i ++)     fa[i] = i;
		sort(E, E + tot);
		for(int i = 0, ct = n; i < tot && ct > K; i ++) {
			if(findfa(E[i].u) != findfa(E[i].v)) {
				fa[findfa(E[i].u)] = findfa(E[i].v);
				if(-- ct == K)
					ans = E[i].w;
			}
		}
		printf("%d\n", ans);
		// dfs(1, 1, 1)
	}
	return 0;
}
