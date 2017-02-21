#include <bits/stdc++.h>
using namespace std;
#define MaxB 455
#define MaxN 100005
typedef int arr[MaxN];
typedef vector<int> v_int;
arr f, rk;
inline int gf(int u) {
	return f[u] ? f[u] = gf(f[u]) : u;
}
inline void uni(int u, int v) {
	u = gf(u), v = gf(v);
	if (u ^ v)
	  (rk[u] < rk[v]) ? f[u] = v : (f[v] = u, (rk[u] ^ rk[v]) ? 0 : ++rk[v]);
}
arr a, b;
bool vis[MaxN];
v_int color[MaxN], in_block[MaxN], tmp[MaxN];
vector <v_int> block;
void ins(int u) {
	if (!vis[u]) {
		vis[u] = true;
		tmp[gf(u)].push_back(u);
	}
}
void del(int u) {
	if (tmp[u].size() > 1) {
		block.push_back(tmp[u]);
		tmp[u].clear();
	}
	if (vis[u]) {
		vis[u] = false;
		f[u] = rk[u] = 0;
	}
}
arr ans[MaxB], id;
int main() {
	int n, m, q, i, j, k;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", a + i, b + i, &j);
		color[j].push_back(i);
	}
	for (i = 1; i <= m; ++i) {
		for (j = 0; j < (int)color[i].size(); ++j) {
			k = color[i][j];
			uni(a[k], b[k]);
		}
		for (j = 0; j < (int)color[i].size(); ++j) {
			k = color[i][j];
			ins(a[k]);
			ins(b[k]);
		}
		for (j = 0; j < (int)color[i].size(); ++j) {
			k = color[i][j];
			del(a[k]);
			del(b[k]);
		}
		//color[i].clear();
	}
	for (i = 0; i < (int)block.size(); ++i)
	  for (j = 0; j < (int)block[i].size(); ++j) {
		  k = block[i][j];
		  in_block[k].push_back(i);
	  }
	//block.clear();
	const int B = floor(sqrt(2.0 * m));
	int x, y, ans, idx = 0;
	for (i = 1; i <= n; ++i)
	  if ((int)in_block[i].size() > B) {
		  id[i] = ++idx;
		  for (j = 0; j < (int)in_block[i].size(); ++j)
			for (k = 0; k < (int)block[in_block[i][j]].size(); ++k)
			  ++::ans[idx][block[in_block[i][j]][k]];
	  }
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &x, &y);
		if (id[x]) ans = ::ans[id[x]][y];
		else if (id[y]) ans = ::ans[id[y]][x];
		else {
			ans = i = j = 0;
			v_int &X = in_block[x], &Y = in_block[y];
			n = X.size(), m = Y.size();
			while (i < n && j < m) {
				if (X[i] ^ Y[j]) {
					X[i] < Y[j] ? ++i : ++j;
				} else {
					++ans;
					++i;
					++j;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
