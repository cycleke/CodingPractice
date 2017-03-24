#include <queue>
#include <cstdio>
#include <cstring>
const int maxn(13), inf(0x3f3f3f3f);
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int f[maxn][maxn][1 << maxn], pre[maxn][maxn][1 << maxn];

int n, m, all, a[maxn][maxn];
bool inq[maxn * maxn * 2], vis[maxn][maxn];

inline int pack(int x, int y) {
	return (x << 4) | y;
}

inline void uncode(int sta, int &x, int &y) {
	x = sta >> 4;
	y = sta & 15;
}

inline int pack(int x, int y, int z) {
	return (x << 14) | (y << 10) | z;
}

inline void uncode(int sta, int &x, int &y, int &z) {
	x = sta >> 14;
	y = (sta >> 10) & 15;
	z = sta & 1023;
}

std::queue<int> q;

inline void spfa(int sta) {
	while (!q.empty()) {
		static int x, y, p, _x, _y;
		p = q.front(), q.pop();
		inq[p] = false;
		uncode(p, x, y);
		for (register int i = 0; i ^ 4; ++i) {
			_x = x + dx[i], _y = y + dy[i];
			if (_x < 0 || _y < 0 || _x >= n || _y >= m)
				continue;
			if (f[_x][_y][sta] > f[x][y][sta] + a[_x][_y]) {
				f[_x][_y][sta] = f[x][y][sta] + a[_x][_y];
				pre[_x][_y][sta] = pack(x, y, sta);
				if (!inq[p = pack(_x, _y)])
					inq[p] = true, q.push(p);
			}
		}
	}
}

void dfs(int x, int y, int s) {
	if (!pre[x][y][s]) return;
	vis[x][y] = true;
	int _x, _y, _s;
	uncode(pre[x][y][s], _x, _y, _s);
	dfs(_x, _y, _s);
	if (_x == x && _y == y)
		dfs(x, y, s ^ _s);
}


inline void print() {
	for (register int i = 0; i < n; ++i) {
		for (register int j = 0; j < m; ++j)
			if (!a[i][j]) putchar('x');
			else if (vis[i][j]) putchar('o');
			else putchar('_');
		putchar('\n');
	}
}

int main() {
	//freopen("2595.in","r", stdin);
	int all = 1;
	scanf("%d%d", &n, &m);
	memset(f, 63, sizeof f);
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j < m; ++j) {
			scanf("%d", a[i] + j);
			if (!a[i][j]) f[i][j][all] = 0, all <<= 1;
		}
	for (register int sta = 1, t; sta ^ all; ++sta) {
		for (register int i = 0; i < n; ++i)
			for (register int j = 0; j < m; ++j) {
				for (register int s = sta & (sta - 1); s; s = (s - 1) & sta)
					if (f[i][j][sta] > f[i][j][s] + f[i][j][sta ^ s] - a[i][j]) {
						f[i][j][sta] = f[i][j][s] + f[i][j][sta ^ s] - a[i][j];
						pre[i][j][sta] = pack(i, j, s);
					}
				if (f[i][j][sta] != inf)
					q.push(t = pack(i, j)), inq[t] = true;
			}
		spfa(sta);
	}
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j < m; ++j)
			if (!a[i][j]) {
				printf("%d\n", f[i][j][all - 1]);
				dfs(i, j, all - 1);
				print();
				return 0;
			}
	return 0;
}
