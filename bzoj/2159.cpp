#include <cstdio>

#define mod 20101009
#define N 10000007
int mu[N], prime[N], s[N];
bool vis[N];

inline long long mmo(long long x) {
	x %= mod;
	if (x < 0) x += mod;
	return x;
}

inline long long mi(long long a, long long b) {
	return a < b ? a : b;
}

void Init(int n) {
	int *ep = prime, i, *j, t;
	mu[1] = 1;
	for (i = 2; i <= n; ++i) {
		if (!vis[i])
			mu[*ep++ = i] = -1;
		for (j = prime; j < ep; ++j) {
			if ((long long)i * (*j) > n)
				break;
			t = i * (*j);
			vis[t] = true;
			if (i % *j)
				mu[t] = -mu[i];
			else {
				mu[t] = 0;
				break;
			}
		}
	}
	for (i = 1; i <= n; ++i)
		s[i] = mmo(s[i - 1] + (long long)i * i * mu[i] % mod);
}

long long Sum(long long x, long long y) {
	return ( (x * ( x + 1 ) / 2) % mod ) *( ( y * ( y + 1 ) / 2 ) % mod ) % mod;
}

long long F(long long x, long long y) {
	static long long ret, i, j;
	static long long _x, _y;
	if (y < x)
		x ^= y ^= x ^= y;
	for (i = 1, ret = 0; i <= x; i = j + 1) {
		_x = x / i, _y = y / i;
		j = mi(x / _x, y / _y);
		ret = mmo(ret + (s[j] - s[i - 1]) * Sum(_x, _y) % mod);
	}
	return ret;
}

int main() {
	long long _n, _m;
	long long i, j, ans = 0, n, m;
	scanf("%lld%lld", &n, &m);
	if (m < n) n ^= m ^= n ^= m;
	Init(n);
	for (i = 1; i <= n; i = j + 1) {
		_n = n / i, _m = m / i;
		j = mi(n / _n, m / _m);
		ans = mmo(ans + (i + j) * (j - i + 1LL) / 2 % mod * F(_n, _m) % mod);
	}
	printf("%lld\n", ans);
	return 0;
}
