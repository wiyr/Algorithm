int sa[N], t[N], t2[N], c[N], xy[N];

bool cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

void build_sa(int *s, int n, int m) {
	int p = 1, *x = t, *y = t2;
	rep(i, m)	c[i] = 0;
	rep(i, n)	c[x[i]=s[i]]  ++;
	for(int i = 1; i < m; i ++)	c[i] += c[i-1];
	for(int i = n-1; ~i; i --)	sa[-- c[x[i]]] = i;
	for(int j = 1; p < n; j <<= 1, m=p) {
		p = 0;
		for(int i = n - j; i < n; i ++)	y[p ++] = i;
		rep(i, n) if(sa[i] >= j) {
			y[p ++] = sa[i] - j;
		}
		rep(i, m)	c[i] = 0;
		rep(i, n)	xy[i] = x[y[i]];
		rep(i, n)	c[xy[i]] ++;
		for(int i = 1; i < m; i ++)	c[i] += c[i-1];
		for(int i = n - 1; i >= 0; i --)	sa[-- c[xy[i]]] = y[i];
		swap(x, y);
		p = 1, x[sa[0]] = 0;
		for(int i = 1; i < n; i ++)
			x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1: p ++;
	}
}

int rnk[N], H[N];

void getheight(int *s, int n) {
	int i, j, k = 0;
	for(i = 1; i <= n; i ++)	rnk[sa[i]] = i;
	for(i = 0; i < n; H[rnk[i ++]] = k)
		for(k?k--:0,j=sa[rnk[i]-1];s[i+k]==s[j+k];k++);
}

int LOG[N], lcp[N][20];

void rmq_init(int n) {
	for(int i = 2; i <= n; i ++)	lcp[i][0] = H[i];
	for(int j = 1; j <= LOG[n]; j ++) {
		for(int i = 1; i + (1<<j) - 1 <= n; i ++)
			lcp[i][j] = min(lcp[i][j-1], lcp[i+(1<<j-1)][j-1]);
	}
}

int LCP(int a, int b) {
	if(a > b)	swap(a, b);
	int k = LOG[b-a+1];
	return min(lcp[a][k], lcp[b-(1<<k)+1][k]);
}

