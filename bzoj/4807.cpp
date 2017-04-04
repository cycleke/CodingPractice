#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(1e6 + 7);
int p[maxn / 10], e[maxn / 10], tot;
inline void silver() {
	static bool v[maxn];
	for (int i = 2; i < maxn; ++i) {
		if (!v[i])
			p[tot++] = i;
		for (int j = 0, t; (t = i * p[j]) < maxn; ++j) {
			v[t] = true;
			if (i % p[j] == 0) break;
		}
	}
}

inline void fac(const int &n, const int &delta) {
	for (int i = 0; i < tot && p[i] <= n; ++i) {
		for (long long t = p[i]; t <= n; t *= p[i])
			e[i] += delta * n / t;
	}
}

int ans[55];

int main() {

	int n, m;

	silver();

	scanf("%d%d", &n, &m);
	if (n < m)
		std::swap(n, m);

	fac(n, 1);
	fac(m, -1);
	fac(n - m, -1);

	ans[0] = 1;

	for (int i = 0; i < tot; ++i)
		while (e[i]--) {
			for (int j = 0; j < 50; ++j)
				ans[j] *= p[i];
			for (int j = 0; j < 50; ++j) {
				ans[j + 1] += ans[j] / 10;
				ans[j] %= 10;
			}
		}

	for (n = 49; ~n && !ans[n]; --n);

	if (~n) while (~n) putchar(ans[n--] + '0');
	else putchar('0');

	puts("");

	return 0;
}
