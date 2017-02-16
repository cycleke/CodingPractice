#include <cstdio>
#define N 10000007
typedef int arr[N];
arr a, pa, g;

void Init() {
	static int p[1001001], *ep = p;
	static bool vis[N];
	int i, *j, t, _t;
	for (i = 2; i < N; ++i) {
		if (!vis[i]) {
			a[i] = 1;
			pa[i] = i;
			g[i] = 1;
			*ep++ = i;
		}
		for (j = p; (t = *j * i) < N; ++j) {
			vis[t] = true;
			if (!(i % *j)) {
				a[t] = a[i] + 1;
				pa[t] = pa[i] * *j;
				_t = i / pa[i];
				if (_t == 1)
				  g[t] = 1;
				else 
				  g[t] = ((a[t] ^ a[_t]) ? 0 : -g[_t]);
				break;
			}
			a[t] = 1;
			pa[t] = *j;
			g[t] = ((a[i] ^ 1) ? 0 : -g[i]);
		}
	}
	for (i = 1; i < N; ++i)
	  g[i] += g[i - 1];
}

int min(const int &a, const int &b) {
	return a < b ? a : b;
}

#define swap(a, b) (a ^= b ^= a ^= b)

long long Query(int n, int m) {
	static int i, j, _n, _m;
	static long long ans;
	if (n > m)
	  swap(n, m);
	for (ans = 0LL, i = 1; i <= n; i = j + 1) {
		_n = n / i, _m = m / i;
		j = min(n / _n, m / _m);
		ans += (long long)_n * _m * (g[j] - g[i - 1]);
	}
	return ans;
}

int main() {
	int _, a, b;
	Init();
	for (scanf("%d", &_); _; _--) {
		scanf("%d%d", &a, &b);
		printf("%lld\n", Query(a, b));
	}
	return 0;
}

