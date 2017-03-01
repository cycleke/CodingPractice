#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 3e5 + 5;
const int mod = 7 * 17 * (1 << 23) + 1, e = 3;
typedef int arr[MaxN];
inline int pw(int a, int b) {
	static int r;
	for (r = 1; b; (b >>= 1) ? a = 1LL * a * a % mod : 0)
	  if (b & 1) r = 1LL * r * a % mod;
	return r;
}

arr a, b, rev, fac, inv;
#define rep(i, l, r) for (int i = l; i < r; ++i)
#define Rep(i, l, r) for (int i = l; i <= r; ++i)

inline void ntt(int *a, int n, int flg) {
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int m = 2; m <= n; m <<= 1) {
		int mid = m >> 1, wn = pw(e, ((mod - 1) / m * flg + mod - 1) % (mod - 1));
		for (int i = 0; i < n; i += m) {
			int w = 1, t1, t2;
			rep(j, 0, mid) {
				t1 = a[i + j], t2 = 1LL * a[i + j + mid] * w % mod;
				for (a[i + j] = t1 + t2; a[i + j] >= mod; a[i + j] -= mod);
				for (a[i + j + mid] = t1 - t2 + mod; a[i + j + mid] >= mod; a[i + j + mid] -= mod);
				w = 1LL * w * wn % mod;
				//printf("%d ", w);
			}	
			//puts("");
		}
	}
	if (flg < 0) {
		int inv = pw(n, mod - 2);
		rep(i, 0, n) {
			a[i] = 1LL * a[i] * inv % mod;
			//printf("%d\n", a[i]);
		}
	}
}

int main() {
	int n, len = 1, m, ans = 0;
	scanf("%d", &n);
	fac[0] = inv[0] = 1;
	Rep(i, 1, n) fac[i] = (long long)fac[i - 1] * i % mod;
	inv[n] = pw(fac[n], mod - 2);
	for (int i = n - 1; i; --i) inv[i] = (long long)inv[i + 1] * (i + 1) % mod;
	Rep(i, 0, n) {
		if (i & 1) a[i] = mod - inv[i];
		else a[i] = inv[i];
		if (i ^ 1) b[i] = (pw(i, n + 1) - 1LL + mod) * (long long)pw(i - 1 + mod, mod - 2) % mod * inv[i] % mod;
		else b[i] = n + 1;
	}
	m = n << 1;
	while ((1 << len) <= m) ++len;
	n = 1 << len;
	rep(i, 0, n) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	ntt(a, n, 1);
	ntt(b, n, 1);
	rep(i, 0, n) a[i] = (long long)a[i] * b[i] % mod;
	ntt(a, n, -1);
	m >>= 1;
	n = 1;
	Rep(i, 0, m) {
		ans = (ans + (long long)n * fac[i] % mod * a[i]) % mod;
		n <<= 1;
		if (n >= mod) n -= mod;
		//printf("%d\n", ans);
	}
	printf("%d\n", ans);
	return 0;
}
