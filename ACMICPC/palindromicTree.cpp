const int N = 1e5 + 2, sigma = 26;

int fail[N], len[N], to[N][sigma];
int S[N];
int last, sz, n;

int _alloc(int Length) {
	len[sz] = Length;
	rep(c, sigma)	to[sz][c] = 0;
	return sz ++;
}
void initial() {
	last = sz = n = 0;
	S[n ++] = -1;
	_alloc(0);
	_alloc(-1);
	fail[0] = 1;
}

int get_fail(int v) {
	while(S[n - len[v] - 2] != S[n - 1])
		v = fail[v];
	return v;
}

void add(int c) {
	S[n ++] = c;
	last = get_fail(last);
	if(!to[last][c]) {
		fail[sz] = to[get_fail(fail[last])][c];
		to[last][c] = _alloc(len[last] + 2);
	}
	last = to[last][c];
}
