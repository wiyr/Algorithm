const int N = 100000;
const int sigma = 26;
int ch[N][sigma], tot, len[N], fail[N];
int tail, root;	

void init() {
	tot = root = tail = 0;
	fail[root] = -1;
	rep(c, sigma)
		ch[root][c] = root;
}

void _alloc(int l) {
	len[++ tot] = l;
	rep(c, sigma)
		ch[tot][c] = 0;
}

void extend(int c) {
	int p = tail;
	_alloc(len[p] + 1);
	tail = tot;
	while(~p && !ch[p][c])
		ch[p][c] = tail, p=fail[p];
	if(p == -1) {
		fail[tail] = root;
	} else if(len[p]+1==len[ch[p][c]]) {
		fail[tail] = ch[p][c];
	} else {
		_alloc(len[p] + 1);
		int tmp = ch[p][c];
		memcpy(ch[tot], ch[tmp], sizeof ch[tot]);
		fail[tot] = fail[tmp];
		fail[tmp] = fail[tail] = tot;
		for(;~p && ch[p][c]==tmp; p=fail[p])
			ch[p][c] = tot;
	}
}
