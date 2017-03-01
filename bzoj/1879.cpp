#include <cstdio>
#include <cstring>

const int mod = 1e6 + 3;
const int MaxN = 16, MaxL = 55, MaxS = (1 << 16) | 1;

int f[MaxL][MaxS], g[MaxL][26], cnt[MaxS];
char s[MaxN][MaxL];

#define rep(i, l, r) for (i = l; i < r; ++i)

inline void inc(int &a, const int &b) {
	a += b;
	if (a >= mod) a -= mod;
	//printf("%d\n", a);
}

int main() {
	//freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	int _, n, K, len, i, j, k, all, ans;
	rep(i, 1, MaxS) cnt[i] = cnt[i & (i - 1)] + 1;
	scanf("%d", &_);
	while (_--) {
		scanf("%d%d", &n, &K);
		rep(i, 0, n) scanf("%s", s[i]);
		len = strlen(s[0]);
		rep(i, 0, len) rep(j, 0, n) {
			if (s[j][i] ^ '?')
			  g[i][s[j][i] - 'a'] ^= 1 << j;
			else
			  rep(k, 0, 26) g[i][k] ^= 1 << j;
		}
		all = 1 << n;
		f[0][all - 1] = 1;
		rep(i, 0, len) rep(j, 0, all) if (f[i][j]) 
			rep(k, 0, 26) inc(f[i + 1][j & g[i][k]], f[i][j]);
		ans = 0;
		rep(j, 0, all) if (cnt[j] == K) inc(ans, f[len][j]);
		printf("%d\n", ans);
		if (_) {
			memset(f, 0, sizeof f);
			memset(g, 0, sizeof g);
		}
	}
	return 0;
}
