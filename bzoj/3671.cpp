#include <bits/stdc++.h>
using namespace std;

const int BufferSize = 1 << 16 | 1;
inline char gc() {
	static char buffer[BufferSize], *s(buffer), *t(buffer);
	if(s == t) {
		t = (s = buffer) + fread(buffer, 1, BufferSize, stdin);
		if (s == t) return EOF;
	}
	return *s++;
}
inline int gi() {
	static int a;
	static char c, f;
	f = 0;
	while (!isdigit(c = gc())) f |= c == '-';
	a = c ^ 48;
	while (isdigit(c = gc())) a = (a << 3) + (a << 1) + (c ^ 48);
	return f ? -a : a;
}

static const int maxn(5007), maxm(25000007);
int n, m, q, x[maxm], T[maxm], tl[maxn], tr[maxn], high[maxn], low[maxn];
int ans[maxn<<1], cnt;
short idy[maxm];
int main() {
	x[0] = gi(); int a = gi(), b = gi(), c = gi(), d = gi();
	n = gi(); m = gi(); q = gi();
	for(int i = 1; i <= n * m; ++i) {
		x[i] = ((1ll * a * x[i-1] * x[i-1]) % d + (1ll * b * x[i-1]) % d + c) % d;
		T[i] = i;
	}
	for(int i = 1; i <= n * m; ++i) swap(T[i], T[x[i] % i + 1]);
	while(q--) {
		int x = gi(), y = gi();
		if(x != y) swap(T[x], T[y]);
	}
	for(int i = 1; i <= n * m; ++i)
		x[T[i]] = (i - 1) / m + 1, idy[T[i]] = (i - 1) % m + 1;
	for(int i = 1; i <= m; ++i) tl[i] = 1, tr[i] = m, high[i] = n + 1, low[i] = 0;
	high[1] = low[1] = 1; high[m] = low[m] = n;
	for(int i = 1; i <= n * m; ++i) if(i != T[1] && i != T[n * m]) {
			int X = x[i], y = idy[i];
			if((y == 1 || low[tl[y]] <= X) && (y == m || X <= high[tr[y]])) {
				ans[++cnt] = i;
				for(int j = tl[y]; j < y; ++j) tr[j] = y;
				for(int j = y + 1; j <= tr[y]; j++) tl[j] = y;
				low[y] = max(low[y], X);
				high[y] = min(high[y], X);
			}
		} else ans[++cnt] = i;

	for(int i = 1; i < cnt; ++i) printf("%d ", ans[i]);
	printf("%d\n", ans[cnt]);

	return 0;
}

