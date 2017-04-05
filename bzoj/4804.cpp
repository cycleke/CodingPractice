#include <cstdio>

const int maxn(1e7 + 7);

long long g[maxn];

inline void silver() {
	static int p[maxn], cnt = 0;
	g[1] = 1ll;
	for (int i = 2; i < maxn; ++i) {
		if (!p[i]) {
			p[cnt++] = i;
			g[i] = i - 2;
		}
		for (int j = 0, t; (t = i * p[j]) < maxn; ++j) {
			p[t] = 1;
			if (i % p[j])
				g[t] = g[i] * g[p[j]];
			else {
				if (i / p[j] % p[j] == 0)
					g[t] = g[i] * p[j];
				else
					g[t] = g[i / p[j]] * (p[j] - 1ll) * (p[j] - 1ll);
				break;
			}
		}
	}

	for (int i = 2; i < maxn; ++i) g[i] += g[i - 1];

}

int main() {

	silver();

	int o_o;
	scanf("%d", &o_o);

	while (o_o--) {
		static int n, _n, i, j;
		static long long ans;

		ans = 0ll;
		scanf("%d", &n);

		for (i = 1; i <= n; i = j + 1) {
			j = n / (_n = n / i);
			ans += 1ll * _n * _n * (g[j] - g[i - 1]);
		}

		printf("%lld\n", ans);
	}

}
