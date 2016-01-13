int len[N<<1]; // len[i<<1]/2+1:  以原串i为中心的半径
// len[i<<1|1]/2: 以原串i与i+1之间为中心的半径
// 下标1开始
char S[N << 1], buf[N];
int m;
void prepare() {
	int j, k = 0, l;
	for(int i = 1; i <= m; i ++) {
		l = i < k ? std::min(k - i, len[2*j - i]): 0;
		int a = i - l - 1;
		int b = i + l + 1;
		while(a >= 1 && b <= m && S[a] == S[b]) {
			a --;
			b ++;
			l ++;
		}
		len[i] = l;
		if(i + l > k) {
			k = i + l;
			j = i;
		}
	}
}

int main() {
	for(int i = 1; i <= n; i ++) {
		S[++ m] = '#';
		S[++ m] = buf[i];
	}
	S[++ m] = '#';
	prepare();
	return 0;
}

