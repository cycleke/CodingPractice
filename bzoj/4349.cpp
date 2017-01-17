#include <cstdio>
#include <algorithm>
#define N 53
#define inf 1e99
double a[N], In[N];
int pre[N], b[N], vis[N], id[N], pos[N];
struct edge {
	int u, v;
	double w;
}e[3333];
inline bool cmin(double &a, const double &b) {
	if (b < a) return a = b, true;
	return false;
}
inline double MST(int rt, int n, int m) {
	int i, j, cnt, v;
	double ret = 0.0;
	while (true) {
		for (i = 0; i < n; ++i) In[i] = inf;
		for (i = 0; i < m; ++i) if (cmin(In[e[i].v], e[i].w)) pre[e[i].v] = e[i].u;
		for (i = 0; i < n; ++i) id[i] = vis[i] = -1;
		cnt = 0;
		In[rt] = 0.0;
		for (i = 0; i < n; ++i) {
			ret += In[v = i];
			while ((v ^ rt) && (vis[v] ^ i) && !(~id[v])) vis[v] = i, v = pre[v];
			if ((v ^ rt) && !(~id[v])) {
				id[v] = cnt;
				for (j = pre[v]; j ^ v; j = pre[j]) id[j] = cnt;
				++cnt;
			}
		}
		if (!cnt) return ret;
		for (i = 0; i < n; ++i) if (!(~id[i])) id[i] = cnt++;
		for (i = j = 0; i < m; ++i)
			if (id[e[i].u] ^ id[e[i].v])
				e[j++] = (edge) { id[e[i].u], id[e[i].v], e[i].w - In[e[i].v] };
		n = cnt, m = j; rt = id[rt];
	}
}

int main() {
	int n, idx = 1, i, ce = 0, k, x, y;
	double v;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%lf%d", &v, &k);
		if (k) {
			e[ce++] = (edge) {0, pos[i] = idx, v};
			a[idx] = v, b[idx] = k - 1;
			++idx;
		}
	}
	scanf("%d", &k);
	while (k--) {
		scanf("%d%d%lf", &x, &y, &v);
		if (!pos[x] || !pos[y] || !(x ^ y)) continue;
		e[ce++] = (edge) {pos[x], pos[y], v};
		if (v < a[y = pos[y]]) a[y] = v;
	}
	v = 0.0;
	for (i = 1; i < idx; ++i)
		v += a[i] * b[i];
	printf("%.2lf\n", MST(0, idx, ce) + v);
	return 0;
}
