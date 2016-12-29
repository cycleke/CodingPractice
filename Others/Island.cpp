#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb; bool insign;
inline char getc() {
	if (ins == ine) ine = (ins = inb) + fread(inb, 1, 1 << 16, stdin);
	return (ins == ine) ? EOF : *ins++;
}
inline int geti() {
	insign = false;
	while ((inc = getc()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; 
	return insign ? -ina : ina;
}

typedef pair<int, int>pii;
const int N = 1005, MT = 1e5 + 5;
int fa[N * N], mp[N][N], X[N * N], Y[N * N], ans[MT], que[MT], totBlocks, n, m;
pii Val[N * N];

#define mk make_pair
int find(int u) { return (fa[u] ^ u)?fa[u]=find(fa[u]):u; }
bool Union(int x, int y) {
	x = find(x), y = find(y);
	return (x ^ y) ? (fa[x] = y) : 0;
}

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};


bool Exband(int u, const int &x) {
	if (Val[u].first <= x) return false;
	int p = Val[u].second; ++totBlocks;
	for (int i = 0; i < 4; ++i) {
		int _x = X[p] + dx[i], _y = Y[p] + dy[i];
		if (_x <= 0 || _x > n || _y <= 0 || _y > m) continue;
		if (mp[_x][_y] > x && Union(p, m * (_x - 1) + _y)) --totBlocks;
	}
	return true;
}

int main() {
	freopen("T.in", "r", stdin);
	int T, i, j, tot, __ = geti(), tail;
	while (__--) {
		n = geti(), m = geti(); tot = 0;
		for (i = 1; i <= n; ++i)
		  for (j = 1; j <= m; ++j) {
			  ++tot; X[tot] = i, Y[tot] = j;
			  Val[tot] = mk(mp[i][j] = geti(), tot); fa[tot] = tot;
		  }
		tail = tot; totBlocks = 0;
		sort(Val + 1, Val + tot + 1);
		for (i = 1, j = T = geti(); i <= T; ++i) que[i] = geti();
		while (T) {
			while (Exband(tail, que[T])) 
			  --tail;
			ans[T--] = totBlocks;
		}
		for (i = 1; i <= j; ++i) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}
