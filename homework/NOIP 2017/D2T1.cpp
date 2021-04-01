#include <cmath>
#include <cstdio>

const int N = 1005;

int f[N];
int x[N], y[N], z[N];

int FindRoot(int x) {
	return (f[x] == x) ? x : f[x] = FindRoot(f[x]);
}

inline void Union(int x, int y) {
	x = FindRoot(x), y = FindRoot(y);
	if (x != y) f[x] = y;
}

inline double pow2(double x) {
	return x * x;
}

inline double Distance(int i, int j) {
	return sqrt(pow2(x[i] - x[j]) + pow2(y[i] - y[j]) + pow2(z[i] - z[j]));
}

int main() {
	int _;
	scanf("%d", &_);
	while (_--) {
		int n, h, r;
		scanf("%d %d %d", &n, &h, &r);
		f[0] = 0;
		f[n + 1] = n + 1;
		for (int i = 1; i <= n; ++i) {
			f[i] = i;
			scanf("%d %d %d", x + i, y + i, z + i);
			if (abs(z[i]) <= r) Union(0, i);
			if (abs(h - z[i]) <= r) Union(i, n + 1);
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j < i; ++j) {
				if (FindRoot(i) != FindRoot(j) && (Distance(i, j) <= 2 * r + 1e-9))
					Union(i,j);
			}
		puts(FindRoot(0) == FindRoot(n + 1) ? "Yes" : "No");
	}
	return 0;
}
