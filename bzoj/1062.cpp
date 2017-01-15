#include <cstdio>
inline int gi() {
	static char c, f; static int a; f = 0;
	while (c = getchar(), c < '0') f |= c == '-'; a = c - '0';
	while (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
	return f? -a : a;
}
#define N 2003
#define M 4003
int len, len2, len4, C[2][N][M], X[1000003], Y[1000003];

inline void add(int tr[N][M], int x, int y, int v) {
	static int i, j; ++x, ++y;
	for (i = x; i <= len2; i += i & -i)
		for (j = y; j <= len4; j += j & -j)
			tr[i][j] += v;
}

inline int sum(int tr[N][M], int x, int y) {
	if (x < 0 || y < 0) return 0;
	static int i, j, ans;
	if (++x > len2) x = len2 + 1;
	if (++y > len4) y = len4 + 1;
	ans = 0;
	for (i = x; i; i -= i & -i)
		for (j = y; j; j -= j & -j)
			ans += tr[i][j];
	return ans;
}

inline int sum(int tr[N][M], int x1, int y1, int x2, int y2) {
	--x1, --y1;
	return sum(tr, x2, y2) + sum(tr, x1, y1) - sum(tr, x1, y2) - sum(tr, x2, y1);
}

int main() {
	int __ = gi(), t, c, l, r, d, ___;
	len = gi(), len2 = len << 1, len4 = len << 2;
	while (__--) {
		___ = gi(), t = gi();
		if (___ < 2) {
			c = gi(), l = gi(), r = gi(), d = gi();
			int &x = X[c], &y = Y[c];
			x = (t - d * l + len2) % len2;
			y = r - l;
			add(C[0], x, x + y, 1);
			add(C[1], x, y - x + len2, 1);
		} else if (___ < 3) {
			l = gi(), r = gi();
			t %= len2;
			d = (r ^ len) ? 0 : 1;
			printf("%d\n",
				   sum(C[0], t, l + t, r + t, len4) + sum(C[0], 0, l + t - len2, r + t - len2 - d, len4) + sum(C[1], t - r + len2 + d, l - t, len2, len4) + sum(C[1], t - r, l - t + len2, t - 1, len4)
				);
		} else {
			c = gi();
			add(C[0], X[c], Y[c] + X[c], -1);
			add(C[1], X[c], Y[c] - X[c] + len2, -1);
		}
	}
}
