#include <bits/stdc++.h>
#define N 4005
#define Mod 1000000007
#define rep(i, l, r) for (register int i = l; i < r; ++i)
#define rrp(i, l, r) for (register int i = l; i >= r; --i)
typedef long long i64;
typedef int arr[N];
arr base, p0, p1, initv;
int n;
const size_t SINT = sizeof (int);

inline void mov(int &x, long long b) {
	x = (x + b) % Mod;
}

inline void sub(int *x, int pos) {
	static i64 v;
	if (!(v = x[pos]))
	  return;
	rep(i, 0, n)
		mov(x[pos - i - 1], v * base[i]);
}

inline void mul(int *dest, int *x, int *y) {
	static arr t;
	memset(t, 0, n * 2 * SINT);
	rep(i, 0, n)
		rep(j, 0, n)
		mov(t[i + j], (long long)x[i] * y[j]);
	rrp(i, 2 * (n - 1), n)
		sub(t, i);
	memcpy(dest, t, n * SINT);
}
inline void shift(int *x, int z) {
	rrp(i, 2 * (n - 1), z)
		x[i] = x[i - z];
	memset(x, 0, z * SINT);
	rrp(i, 2 * (n - 1), n)
		sub(x, i);
}

inline void _pow(int *v, int *x, int p) {
	memset(v, 0, n * SINT);
	v[0] = 1;
	while (p) {
		if (p & 1) mul(v, x, v);
		if (p >>= 1) mul(x, x, x);
	}
}

int main() {
	int p;
	scanf("%d%d", &p, &n);
	rep(i, 0, n) {
		scanf("%d", base + i);
		if (base[i] < 0) base[i] += Mod;
	}
	rep(i, 0, n) {
		scanf("%d", initv + i);
		if (initv[i] < 0) initv[i] += Mod;
	}
	if (p <= n) 
	  return printf("%d\n", initv[p - 1]), 0;

	rep(i, 0, n)
		p1[i] = base[n - 1 - i];

	_pow(p0, p1, p / n);
	shift(p0, p % n);
	int ans = 0;
	rep(i, 0, n)
		mov(ans, (i64)initv[i] * p0[i]);

	printf("%d\n", ans);

	return 0;
}
