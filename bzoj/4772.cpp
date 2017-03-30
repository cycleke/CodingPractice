#include <cstdio>
#include <cstring>
#include <algorithm>

const int mod(1e9 + 7), maxn(2007), maxk(1e5 + 7), maxa(1e7 + 7);

inline int gcd(int a, int b) {
	for (static int t; b; t = a % b, a = b, b = t);
	return a;
}

bool vis[maxa];
int a[maxk], n, k, type, d[maxa], phi[maxa], g[maxa], p[maxn], pri[maxa / 10], tot, e[maxa];

inline int fast_pow(int a, int b) {
	static int r;
	for (r = 1; b; b >>= 1, a = (long long)a * a % k)
		if (b & 1) r = (long long)r * a % k;
	return r;
}
inline int F(int x, int y) {
	if (type == 1)
		return 1;
	if (type == 2)
		return gcd(x, y) % k;
	return (fast_pow(x, y) + fast_pow(y, x) + (x xor y)) % k;
}

inline void calc_p(const int &n) {
	p[0] = 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = i; j <= n; ++j)
			for (p[j] += p[j - i]; p[j] >= mod; p[j] -= mod);
}

inline void silver(const int &maxa) {
	g[1] = 1;
	for (register int i = 2; i < maxa; ++i) {
		if (!vis[i]) {
			pri[tot++] = i;
			d[i] = 2;
			e[i] = 1;
			phi[i] = i - 1;
		}
		for (register int j = 0, t; (t = pri[j] * i) < maxa; ++j) {
			vis[t] = true;
			if (i % pri[j]) {
				d[t] = d[i] * d[pri[j]];
				e[t] = 1;
				phi[t] = phi[i] * (pri[j] - 1);
			} else {
				d[t] = d[i] / (e[i] + 1) * (e[i] + 2);
				e[t] = e[i] + 1;
				phi[t] = phi[i] * pri[j];
				break;
			}
		}
		g[i] = (long long)d[i] * phi[i] % mod;
	}
}

int main() {

	scanf("%d%d%d", &type, &n, &k);
	int _maxa = -1;
	for (register int i = 0; i < k; ++i) {
		scanf("%d", a + i);
		if (_maxa < a[i])
			_maxa = a[i];
	}

	silver(_maxa);
	calc_p(n);
	int ans = 0, cnt;
	long long f;
	for (register int x = 1; x <= n; ++x)
		for (register int y = x; y <= n; ++y) {
			f = g[a[F(x, y)]];
			cnt = 0;
			if (f) for (register int i = 1, _i = x; _i < n; ++i, _i += x)
					   for (register int j = 1, _j = _i + y; _j <= n; _j += y)
						   for (cnt += p[n - _j]; cnt >= mod; cnt -= mod);
			ans = (f * cnt + ans) % mod;
		}
	printf("%d\n", ans);
	return 0;
}
