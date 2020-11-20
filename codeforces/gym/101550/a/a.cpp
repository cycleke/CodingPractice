#include "bits/stdc++.h"
#define N 1000
#define Q 10000
using namespace std;
int fa[N * N + 5], a[N + 5][N + 5], as[Q + 5], n, m, q,
	sx[4] = {0, 0, 1, -1}, sy[4] = {1, -1, 0, 0},
	X1[Q + 5], X2[Q + 5], Y1[Q + 5], Y2[Q + 5], ans = 0;
int pos(int x, int y) { return (x - 1) * m + y; }
int getfa(int x) { return x == fa[x] ? x : fa[x] = getfa(fa[x]); }
void merge(int x, int y) {
	x = getfa(x), y = getfa(y);
	if (x == y) return ;
	fa[x] = y, ans--;
}
void check(int x, int y) {
	if (a[x][y]) return ;
	for (int i = 0; i < 4; i++) {
		int nx = x + sx[i], ny = y + sy[i];
		if (a[nx][ny] || nx < 1 || nx > n || ny < 1 || ny > m) continue;
		merge(pos(x, y), pos(nx, ny));
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			fa[pos(i, j)] = pos(i, j);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d%d", X1 + i, Y1 + i, X2 + i, Y2 + i);
		for (int x = X1[i]; x <= X2[i]; x++)
			for (int y = Y1[i]; y <= Y2[i]; y++)
				a[x][y]++;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (!a[i][j])
				ans++;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			check(i, j);
	for (int i = q; i; i--) {
		as[i] = ans;
		for (int x = X1[i]; x <= X2[i]; x++)
			for (int y = Y1[i]; y <= Y2[i]; y++) {
				a[x][y]--;
				if (!a[x][y]) ans++;
			}
		for (int x = X1[i]; x <= X2[i]; x++)
			for (int y = Y1[i]; y <= Y2[i]; y++) 
				check(x, y);
	}
	for (int i = 1; i <= q; i++) printf("%d\n", as[i]);
	return 0;
}
