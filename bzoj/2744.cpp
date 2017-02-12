#include <cstdio>
#define _A 203
#define _B 3003
struct edge {int t; edge *n;} me[_B *_B >> 2 | 1], *g[_B], *ce = me;
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
#define rep(i, l, r) for (register int i = l; i <= r; ++i)
int a[_A], b[_B], A, B, vis[_B], _vis, lk[_B];
bool mp[_A][_B], able[_B];
inline int Count(int x) {
	static int r;
	for (r = 0; x; x = x & (x - 1)) ++r;
	return r;
}
inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

bool dfs(int u) {
	for (edge *it = g[u]; it; it = it->n)
	  if (able[it->t] && (vis[it->t] ^ _vis)) {
		  vis[it->t] = _vis;
		  if (!lk[it->t] || dfs(lk[it->t]))
			return lk[it->t] = u, true;
	  }
	return false;
}

inline int hunger(int x = 0, int y = 0) {
	static int r;
	r = 0;
	rep(i, 1, B)
		if (lk[i] = 0, mp[x][i] && mp[y][i])
		  able[i] = true, ++r;
		else able[i] = false;
	rep(i, 1, B) 
		if ((b[i] & 1) && able[i] && (++_vis, dfs(i)))
		  --r;
	return r;
}

int main() {
	int m, u, v, ans;
	scanf("%d%d%d", &A, &B, &m);
	rep(i, 1, A) scanf("%d", a + i);
	rep(i, 1, B) scanf("%d", b + i);
	while (m--) {
		scanf("%d%d", &u, &v);
		mp[u][v] = true;
	}
	rep(i, 1, B) mp[0][i] = true;
	rep(i, 1, B)
		if (b[i] & 1)
		  rep(j, 1, B)
			  if ((~b[j] & 1) && (~Count(b[i] | b[j]) & 1))
				adde(i, j);
	ans = hunger();
	rep(i, 1, A)
		cmax(ans, hunger(i) + 1);
	rep(i, 1, A)
		if (a[i] & 1)
		  rep(j, 1, A)
			  if (~a[j] & 1)
				cmax(ans, hunger(i, j) + 2);
	printf("%d\n", ans);
	return 0;
}
