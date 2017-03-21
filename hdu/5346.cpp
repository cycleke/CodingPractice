#include <cstdio>
#include <cstring>
#define FUCK
#define You Jire
#define Gay int
#define mod jire_is_a_gay
const int mod = 258280327;

inline int pw(int a, int b = mod - 2) {
	static int r;
	for (r = 1; b; b >>= 1, a = (long long)a * a % mod)
		if (b & 1) r = (long long)r * a % mod;
	return r; 
}

inline void work() {
	static int n, x, y, p, _p[2003] = {1}, dp[2003][2003];
	scanf("%d%d%d", &n, &x, &y);
	p = (long long)(y - x) * pw(y) % mod;
	for (register int i = 1; i < n; ++i)
		_p[i] = (long long)_p[i - 1] * p % mod;
	dp[1][0] = 1;
	for (register int i = 2; i <= n; ++i)
		for (register int j = 0; j < i; ++j) {
			if (j) 
				dp[i][j] = (long long)dp[i - 1][j - 1] * _p[j - 1] % mod;
			else 
				dp[i][j] = 0;
				
			if (j ^ (i - 1)) 
				dp[i][j] = (dp[i][j] + (long long)dp[i - 1][j] * (1 + mod - _p[j])) % mod;
		}
	Gay _n = pw(n);
	for (register Gay k = 0, ans; k < n; ++k) {
		ans = 0;
		for (register Gay i = 1; i <= n; ++i)
			if ((ans += dp[i][k]) >= mod)
				ans -= mod;
		ans = (long long)ans * _p[k] % mod * _n % mod;
		printf("%d%c", ans, "\n "[k < (n - 1)]);
	}
}
#ifdef FUCK
int main() {
	int _;
	scanf("%d", &_);
	while (_--)
		work();
	return 0;
}
#endif
