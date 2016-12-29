#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1005
#define getid(i,j) ((i-1)*(m)+(j))
using namespace std;
typedef pair<int, int>pii;
pii D[N * N];
int fa[N * N], n, m, v[N][N], t[100005], ans[100005], res, X[100005], Y[100005];
int find(int u) { return (fa[u]^u)?fa[u]=find(fa[u]):u; }
bool Unoin(int x, int y) {
	x = find(x), y = find(y);
	return (x ^ y) ?(fa[x] = y) : 0;
}

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

bool Exband(int u, int val) {
	if (D[u].first <= val) return false;
	int p = D[u].second; ++res;
	for (int i = 0; i < 4; ++i) {
		int _x = X[p] + dx[i], _y = Y[p] + dy[i];
		if (_x < 1 || _y < 1 || n < _x || m < _y) continue;
		if (v[_x][_y] > val && Unoin(p, getid(_x, _y))) --res;
	}
	return true;
}

int main() {
	int __, id, T, it; scanf("%d", &__);
	while (__--) {
		id = 0; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= m; ++j) {
			  scanf("%d", v[i] + j); ++id;
			  X[id] = i, Y[id] = j;
			  D[id] = make_pair(v[i][j], id);
			  fa[id] = id;
		  }
		scanf("%d", &T);
		for (int i = 1; i <= T; ++i) scanf("%d", t + i);
		sort(D + 1, D + id + 1); res = 0; it = id;
		for (int i = T; i; --i) {
			while (it && Exband(it, t[i])) --it;
			ans[i] = res;
		}
		for (int i = 1; i <= T; ++i) printf("%d%c", ans[i], " \n"[i != T]);
	}
	return 0;
}
