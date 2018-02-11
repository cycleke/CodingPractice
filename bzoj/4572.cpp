#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = int(1e9 + 7);
const int StateSize = (1 << 12) + 5;

int n, m, c, q, r1[10], r2[10], f1[10], f2[10];
int f[StateSize][6][6], g[StateSize][6][6], t1[10][10], t2[10][10];
char c1[10], c2[10];

inline int Change(int s, int t, int mask) {
	if (t < 0)
		return s;
	else
		return s ^ ((mask ^ ((s >> t) & 1)) << t);
}

inline int FastPow(int a, int b) {
	register int r = 1;
	for (; b > 0; a = 1ll * a * a % MOD, b >>= 1)
		if (b & 1) r = 1ll * r * a % MOD;
	return r;
}

inline int GetType(char c) {
	if (c == 'W')
		return 1;
	else if (c == 'B')
		return 2;
	else
		return 0;
}

inline void KMP(int *r, int *f) {
	register int p = 0;
	for (register int i = 2; i <= ::c; ++i) {
		while (p != 0 && r[p + 1] != r[i])
			p = f[p];
		f[i] = (r[p + 1] == r[i]) ? ++p : 0;
	}
}

inline void ModAdd(int &x, const int &y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
}

int main() {
	scanf("%d %d %d %d", &n, &m, &c, &q);
	int ans_max = FastPow(3, n * m);

	while (q--) {
		scanf("%s %s", c1 + 1, c2 + 1);
		for (register int i = 1; i <= c; ++i)
			r1[i] = GetType(c1[i]);
		for (register int i = 1; i <= c; ++i)
			r2[i] = GetType(c2[i]);
	  KMP(r1, f1);
	  KMP(r2, f2);

		for (register int i = 0; i < c; ++i)
			for (register int j = 0; j < 3; ++j) {
				register int p;
				for (p = i; p != 0 && r1[p + 1] != j; p = f1[p]);
				t1[i][j] = (r1[p + 1] == j) ? p + 1 : 0;
				for (p = i; p != 0 && r2[p + 1] != j; p = f2[p]);
				t2[i][j] = (r2[p + 1] == j) ? p + 1 : 0;
			}

		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		g[0][0][0] = 1;
		int base = (1 << (m - c + 1)) - 1;
		for (register int i = 1; i <= n; ++i) {
			for (register int j = 1; j <= m; ++j) {
				if (j != 1)
					memcpy(f, g, sizeof(f));
				else {
					memset(f, 0, sizeof(f));
					for (register int s = 0; s <= base; ++s)
						for (register int x = 0; x < c; ++x)
							for (register int y = 0; y < c; ++y)
								if (g[s][x][y] != 0)
									ModAdd(f[s][0][0], g[s][x][y]);
				}
				memset(g, 0, sizeof(g));

				for (register int s = 0; s <= base; ++s)
					for (register int x = 0; x < c; ++x)
						for (register int y = 0; y < c; ++y)
							if (f[s][x][y] != 0) {
								for (register int now = 0; now < 3; ++now) {
									int nx = t1[x][now], ny = t2[y][now], T;
									if (ny == c && j - c >= 0 && ((s >> (j - c)) & 1) != 0)
										continue;
									if (nx == c)
										T = Change(s, j - c, 1);
									else
										T = Change(s, j - c, 0);
									if (nx == c)
										nx = f1[c];
									if (ny == c)
										ny = f2[c];
									ModAdd(g[T][nx][ny], f[s][x][y]);
								}
							}
			}
		}

		int ans = ans_max;
		for (register int s = 0; s <= base; ++s)
			for (register int x = 0; x < c; ++x)
				for (register int y = 0; y < c; ++y)
					ModAdd(ans, MOD - g[s][x][y]);
		printf("%d\n", ans);

	}

	return 0;
}
