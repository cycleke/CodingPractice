#include <cstdio>
const int MaxN = 50005;
int mu[MaxN], pri[MaxN];
bool vis[MaxN];
long long f[MaxN];
inline void silver() {
	int *end = pri;
	mu[1] = 1;
	for (int i = 2, *j, t; i < MaxN; ++i) {
		if (!vis[i])
		  mu[*end++ = i] = -1;
		for (j = pri; (t = i * *j) <  MaxN; ++j) {
			vis[t] = true;
			if (i % *j)
				mu[t] = -mu[i];
			else {
				mu[t] = 0;
				break;
			}
		}
	}
	for (int x = 1, t, i, last; x <= MaxN; mu[x] += mu[x - 1], ++x)
		for (i = 1; i <= x; i = last + 1) {
			t = x / i;
			last = x / t;
			f[x] += (long long)(last - i + 1) * t;
		}
}
inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}
inline void solve() {
	int n, m, _n, _m;
	long long ans = 0LL;
	scanf("%d%d", &n, &m);
	if (n < m)
		n ^= m ^= n ^= m;
	for (int i = 1, last; i <= m; i = last + 1) {
		_n = n / i;
		_m = m / i;
		last = min(n / _n, m / _m);
		ans += (mu[last] - mu[i - 1]) * f[_n] * f[_m];
	}
	printf("%lld\n", ans);
}
int main() {
	silver();
	int _;
	scanf("%d", &_);
	while (_--)
		solve();
	return 0;
}
