#include <cstdio>
#include <cstring>

const int mo = 1000000001;
int n, mx; bool mark[100003];

inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}

inline void add(int &a, const int &b) {
	a += b;
	if (a >= mo) a -= mo;
}

inline int cal(int x) {
	static int M[2][2049], *f = M[0], *g = M[1], *t, mat[21][21], a[21];
	static int i, j, k, size = sizeof M[0];
	mat[1][1] = x;
	for (i = 2; i < 19; ++i)
		mat[i][1] = min(mat[i - 1][1] * 2, mx);
	for (i = 1; i < 19; ++i)
		for (j = 2; j < 12; ++j)
			mat[i][j] = min(mat[i][j - 1] * 3, mx);
	memset(a, 0, sizeof a);
	for (i = 1; i < 19; ++i)
		for (j = 1; j < 12; ++j)
			if (mat[i][j] < mx){
				a[i] ^= 1 << j - 1;
				mark[mat[i][j]] = true;
			}
	memset(f, 0, size);
	f[0] = 1;
	for (i = 0; i < 18; ++i) {
		t = f, f = g, g = t;
		memset(f, 0, size);
		for (j = 0; j <= a[i]; ++j)
			if (g[j]) for (k = 0; k <= a[i + 1]; ++k)
						  if (!(j&k) && !(k & (k >> 1)))
							  add(f[k], g[j]);
	}
	return f[0];
}

int main() {
	scanf("%d", &n);
	mx = n + 1;
	long long ans = 1LL;
	for (int i = 1; i <= n; ++i)
		if (!mark[i]) ans = ans * cal(i) % mo;
	printf("%d\n", (int)ans);
	return 0;
}
