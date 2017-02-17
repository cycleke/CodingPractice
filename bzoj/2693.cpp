#include <cstdio>

#define mod 100000009
#define N 10000005
#define Prime_Num 700001

long long g[N];

void Init() {
	g[1] = 1LL;
	static int p[Prime_Num], *ep = p, *it, t;
	static bool vis[N];
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) 
		  for (g[*ep++ = i] = 1 - i; g[i] < 0; g[i] += mod);
		for (it = p; (t = i * *it) < N; ++it) {
			vis[t] = true;
			if (i % *it)
			  g[t] = (long long)g[i] * g[*it] % mod;
			else {
				g[t] = g[i];
				break;
			}
		}
	}
	for (int i = 2; i < N; ++i)
	  g[i] = ((long long)g[i] * i + g[i - 1]) % mod;
}

long long sum(int x, int y) {
	x = ((long long)x * (x + 1LL) >> 1) % mod;
	y = ((long long)y * (y + 1LL) >> 1) % mod;
	return (long long)x * y % mod;
}

int min(const int &a, const int &b) {
	return a < b ? a : b;
}

int main() {
	int _, n, m, i, j, _n, _m, ans;
	Init();
	scanf("%d", &_);
	while (_--) {
		scanf("%d%d", &n, &m);
		ans = 0;
		if (m < n)
		  n ^= m ^= n ^= m;
		for (i = 1; i <= n; i = j + 1) {
			_n = n / i;
			_m = m / i;
			j = min(n / _n, m / _m);
			ans = (ans + sum(_n, _m) * (g[j] - g[i - 1] + mod)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
