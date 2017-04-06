#include <cstdio>
#include <cstring>
#include <algorithm>

const int mod(20120427), maxl(20), maxs(6e4);

namespace Not_Zero {
	long long e[maxl], h[maxs];
	int cnt, c1[maxs][10], c2[maxs][10], f[maxl][maxs][2];

	inline int search(const long long &x) {
		return std::lower_bound(h, h + cnt, x) - h;
	}

	inline void init() {
		for (int i = *e = 1; i < maxl; ++i) e[i] = e[i - 1] * 10;
		const long long v = 16e16;
		for (long long x = 1; x < v; x *= 2)
			for (long long y = x; y < v; y *= 3)
				for (long long z = y; z < v; z *= 5)
					for (long long a = z; a < v; a *= 7)
						h[cnt++] = a;
		std::sort(h, h + cnt);
		memset(c1, -1, sizeof c1);
		memset(c2, -1, sizeof c2);
		for (int i = 0; i < cnt; ++i)
			for (int j = 9; j; --j)
				if (h[i] * j < v)
					c2[c1[i][j] = search(h[i] * j)][j] = i;

		f[0][0][0] = 1;

		for (int i = 0; i < 18; ++i)
			for (int j = 0; j < cnt; ++j) {
				int const *t = f[i][j];
				if (!*t) continue;
				for (int k = 9; k; --k)
					if (~c1[j][k]) {
						int * const g = f[i + 1][c1[j][k]];
						*g += *t;
						if (*g >= mod) *g -= mod;
						g[1] = (g[1] + t[1] + k * e[i] % mod * *t) % mod;
					}
			}
	}

	inline int calc(int p, long long x) {
		static int cnt, dig[maxl], res;
		cnt = res = 0;
		for (long long t = x; t; t /= 10) dig[cnt++] = t % 10;
		for (int i = 1; i < cnt; ++i) {
			res += f[i][p][1];
			if (res >= mod) res -= mod;
		}
		for (int i = cnt - 1; ~i; --i) {
			static long long t;
			t = x / e[i + 1] * 10;
			for (int j = 1; j < dig[i]; ++j)
				if (~c2[p][j]) {
					const int * const g = f[i][c2[p][j]];
					res = (res + g[1] + (t + j) * e[i] % mod * *g) % mod;
				}
			p = c2[p][dig[i]];
			if (p < 0) break;
		}
		return res;
	}

	inline void main(const long long &a, const long long &b, const long long &k) {
		int p = search(k);
		if (h[p] ^ k)
			puts("0");
		else {
			int t = calc(p, b + 1) - calc(p, a) + mod;
			if (t >= mod) t -= mod;
			printf("%d\n", t);
		}
	}

}

namespace Is_Zero {

	inline int S(int a, int b, int c, int d, int e) {
		return (a << 4) | (b << 3) | (c << 2) | (d << 1) | e;
	}

	inline void add(int &a, const int &b) {
		for (a += b; a >= mod; a -= mod);
	}

	inline void main(long long a, long long b) {
		static int cnt, d1[maxl], d2[maxl], f[maxl][33];
		for (--a, ++b, cnt = 0; b; a /= 10, b /= 10, ++cnt)
			d1[cnt] = a % 10, d2[cnt] = b % 10;
		for (int i = cnt; i < maxl; ++i) d1[i] = d2[i] = 0;

		memset(f, 0, sizeof f);
		f[cnt][S(1, 1, 0, 1, 0)] = 1;

		for (int a = cnt - 1; ~a; --a)
			for (int b = 1; ~b; --b)
				for (int c = 1; ~c; --c) {
					int s = b ? d1[a] : 0, t = c ? d2[a] : 9;
					for (int d = 1; ~d; --d)
						for (int e = s; e <= t; ++e) {
#define X(i, j) f[a + 1][S(b, c, d, i, j)]
#define Y(i, j, k) f[a][S(b && e == s, c && e == t, i, j, k)]
							add(Y(d | !e, 0, 0), X(0, 0));
							add(Y(d | !e, 0, 1), X(0, 1) * 10 + e * X(0, 0));
							add(Y(0, !e, 0), X(1, 0));
							add(Y(0, !e, 1), X(1, 0) * e);
						}
				}
		printf("%d\n", f[0][S(0, 0, 1, 0, 1)]);
	}

}

int main() {

	Not_Zero::init();
	//Is_Zero::init();

	int o_o;
	long long a, b, k;

	scanf("%d", &o_o);

	while (o_o--) {
		scanf("%lld%lld%lld", &a, &b, &k);

		if (k)
			Not_Zero::main(a, b, k);
		else
			Is_Zero::main(a, b);
	}

	return 0;
}
