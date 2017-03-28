#include <cstdio>

const int maxm(10), maxs(1e5 + 7);
typedef long long ll;


inline void exgcd(ll a, ll b, ll &x, ll &y) {
	if (b) {
		exgcd(b, a % b, y, x);
		y -= a / b * x;
	} else
		x = 1, y = 0;
}

inline ll fast_pow(ll a, int b, int mod) {
	static ll r;
	for (r = 1; b; b >>= 1, a = a * a % mod)
		if (b & 1) r = r * a % mod;
	return r;
}

inline ll inv(ll a, ll p) {
	static ll x, y;
	exgcd(a, p, x, y);
	while (x < 0) x += p;
	return x;
}

inline ll china(int n, int *a, int *m) {
	ll M = 1, t, ans = 0;
	for (register int i = 0; i < n; ++i) M *= m[i];
	for (register int i = 0; i < n; ++i) {
		t = M / m[i];
		ans += t * inv(t, m[i]) * a[i];
		ans %= M;
	}
	return ans;
}

int a[maxm], _m[maxm], fac[maxs], w[maxm], p, n, m;

inline ll mod_fac(int n, const int &P, const int &p, int &e) {
	if (n < p) return fac[n];
	e += n / p;
	return fast_pow(fac[P - 1], n / P, P) * fac[n % P] % P * mod_fac(n / p, P, p, e) % P;
}

inline int calc(int P, int p) {
	static ll m1, m2;
	static int e1, e2;
	m2 = fac[0] = fac[1] = 1;
	for (register int i = 2; i < P; ++i) fac[i] = (ll)fac[i - 1] * (i % p ? i : 1) % P;
	e1 = e2 = 0;
	m1 = mod_fac(::n, P, p, e1);
	for (register int i = 0; i < ::m; ++i)
		m2 = m2 * mod_fac(::w[i], P, p, e2) % P;
	return m1 * inv(m2, P) % P * fast_pow(p, e1 - e2, P) % P;
}

int main() {
	int cnt = 0, sum = 0;
	scanf("%d%d%d", &p, &n, &m);
	for (register int i = 0; i < m; ++i) {
		scanf("%d", w + i);
		sum += w[i];
	}
	if (sum > n)
		return puts("Impossible"), 0;
	if (sum < n)
		w[m++] = n - sum;
	for (register int i = 2; i * i <= p; ++i)
		if (p % i == 0) {
			static int t;
			for (t = 1; p % i == 0; p /= i)
				t *= i;
			_m[cnt] = t;
			a[cnt] = calc(t, i);
			++cnt;
		}
	if (p > 1)
		_m[cnt] = p, a[cnt++] = calc(p, p);
	//for (register int i = 0; i < cnt; ++i)
	//	printf("%d %d\n", _m[i], a[i]);
	printf("%d\n", (int)china(cnt, a, _m));
	return 0;
}
