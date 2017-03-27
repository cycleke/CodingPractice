#include <cstdio>
#include <cstring>

const int maxn(1e7 + 9), mod(1000000007);

bool flag;
int mu[maxn], p[maxn / 10], tot, cnt, a;
long long n, m, _m, ans, b[99], e[99], P;

inline void make_table() {
	static bool v[maxn];
	mu[1] = 1;
	for (register int i = 2; i < maxn; ++i) {
		if (!v[i]) mu[p[tot++] = i] = -1;
		for (register int j = 0, t; (t = i * p[j]) < maxn; ++j)
			if (v[t] = true, i % p[j])
				mu[t] = -mu[i];
			else
				break;
	}
	for (register int i = 2; i < maxn; ++i)
		mu[i] += mu[i - 1];
}

void exgcd(long long a, long long b, long long &x, long long &y) {
	if (b) {
		exgcd(b, a % b, y, x);
		y -= a / b * x;
	} else
		x = 1, y = 0;
}

inline long long inv(long long a, long long p) {
	static long long x, y;
	for (exgcd(a, p, x, y); x < 0; x += p);
	return x;
}

inline long long mul(long long a, long long b) {
	a %= P, b %= P;
	return (a * b - (long long)((long double)a / P * b + 1e-3) * P + P) % P;
}

inline void divide(long long x) {
	for (register int i = cnt = 0; i < tot; ++i) {
		if ((long long)p[i] * p[i] > x)
			break;
		if (x % p[i] == 0) {
			++cnt;
			e[cnt] = 0;
			b[cnt] = p[i];
			while (x % p[i] == 0)
				x /= p[i], ++e[cnt];
		}
	}
	if (x > 1) b[++cnt] = x, e[cnt] = 1;
}

inline long long calc(long long n) {
	static long long a, b, t;
	a = _m, b = n - 1, t = 1;
	if (!flag) {
		for (; b; b >>= 1, a = a * a % mod)
			if (b & 1) t = t * a % mod;
		if (n & 1)
			t += mod - 1;
		else
			++t;
		return t * _m % mod;
	}
	for (; b; b >>= 1, a = mul(a, a))
		if (b & 1) t = mul(t, a);
	if (n & 1)
		t += mod - 1;
	else
		++t;
	return mul(t, _m);
}

void dfs(int x, long long d, long long phi) {
	if (x > cnt) {
		phi %= P;
		if (flag)
			ans = (ans + mul(phi, calc(n / d))) % P;
		else
			ans = (ans + phi * calc(n / d)) % mod;
		return;
	}
	dfs(x + 1, d, phi);
	d *= b[x], phi *= b[x] - 1;
	dfs(x + 1, d, phi);
	for (int i = 2; i <= e[x]; ++i)
		dfs(x + 1, d *= b[x], phi *= b[x]);
}

int main() {
	make_table();
	int o_o;
	long long s1, s2;
	scanf("%d", &o_o);
	while (o_o--) {
		ans = s1 = s2 = 0;
		scanf("%lld%d", &n, &a);
		divide(n);
		if (n % mod) {
			flag = false;
			P = mod;
			for (register int i = 1, j, _a; i <= a; i = j + 1) {
				j = a / (_a = a / i);
				s1 = ((long long)(mu[j] - mu[i - 1]) * _a % mod * _a % mod * _a + s1) % mod;
				s2 = ((long long)(mu[j] - mu[i - 1]) * _a % mod * _a % mod + s2) % mod;
			}
			m = (((s1 - (s2 - 1) * 3 - 1) % mod * inv(6, mod) + s2) % mod + mod) % mod;
			_m = (m - 1 + mod) % mod;
		} else {
			flag = true;
			P = (long long)mod * mod;
			for (register int i = 1, j, _a; i <= a; i = j + 1) {
				j = a / (_a = a / i);
				s1 = (mul(mul(mul(mu[j] - mu[i - 1], _a), _a), _a) + s1) % P;
				s2 = (mul(mul(mu[j] - mu[i - 1], _a), _a) + s2) % P;
			}
			m = ((mul((s1 - (s2 - 1) * 3 - 1) % P, inv(6, P)) + s2) % P + P) % P;
			_m = (m - 1 + P) % P;
		}
		if (n == 1) {
			printf("%d\n", (int)m);
			continue;
		}
		dfs(1, 1, 1);
		if (flag)
			ans = ans / mod * inv(n / mod, mod) % mod;
		else
			ans = ans * inv(n, mod) % mod;
		printf("%d\n", (int)ans);
	}
	return 0;
}
