#include <bits/stdc++.h>
using namespace std;
#define N 1003
struct Main{
	int f[N], sz[N], n, ans, cnte;
	long double sum[N];
	struct edge {
		long double w;
		int u, v;
		bool operator < (const edge &a) const {
			return w < a.w;
		}
	} e[N * N];
	int gf(int u) {
		return f[u] == u ? u : f[u] = gf(f[u]);
	}
	void merge(int u, int v) {
		u = gf(u), v = gf(v);
		if (u == v)
		  return;
		f[u] = v;
		sz[v] += sz[u];
		if (sz[v] > ans)
		  ans = sz[v];
	}
	void Init() {
		scanf("%d", &n);
		cnte = 0;
		for (int i = 1, x; i < n; ++i) {
			scanf("%d", &x);
			sum[i + 1] = sum[i] + log10(x);
		}
	}
	void Build_Edge() {
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j < i; ++j)
			e[cnte++] = (edge){(sum[i] - sum[j]) / (i - j), i, j};
		sort(e, e + cnte);
		for (int i = 1; i <= n; ++i)
		  f[i] = i, sz[i]  =1;
	}

	void Work() {
		merge(e[0].u, e[0].v);
		int pre = 0;
		for (int i = 1; i < cnte; ++i) {
			if (e[i - 1].w < e[i].w) {
				for (int j = pre; j < i; ++j) {
					sz[e[j].u] = sz[e[j].v] = 1;
					f[e[j].u] = e[j].u;
					f[e[j].v] = e[j].v;
					pre = i;
				}
			}
			merge(e[i].u, e[i].v);
		}
		for (int i = 1; i <= n; ++i)
		  if (gf(i) == i && ans < sz[i])
			ans = sz[i];
	}
	Main() {
		cnte = 0, ans = 0;
		Init();
		Build_Edge();
		Work();
		printf("%d\n", ans);
	}

}Solve;
int main() {}
