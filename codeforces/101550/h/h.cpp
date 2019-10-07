#include "bits/stdc++.h"
#define N 1000000
using namespace std;
typedef long long ll;
struct Edge {
	int next, to;
} ed[N + 5];
ll as[N + 5], ans = 0;
int stk[N + 5], last[N + 5], a[N + 5], d[N + 5], b[N + 5], num[N + 5], cnt = 0, p, m, n, ecnt = 0;
bool vis[N + 5];
void addEdge(int u, int v) {
	ed[++ecnt].to = v, ed[ecnt].next = last[u], last[u] = ecnt;
	ed[++ecnt].to = u, ed[ecnt].next = last[v], last[v] = ecnt;
	d[u]++, d[v]++;
}
void dfs(int u, int S) {
	vis[u] = 1;
	stk[++p] = u;
	for (int i = last[u]; i; i = ed[i].next) {
		int v = ed[i].to;
		m++;
		if (vis[v]) continue;
		dfs(v, S), as[S] += num[u];
	}
}
ll getAns(int u, int fa) {
	ll mx = 0;
	if (fa) as[u] = as[fa] - num[fa] + num[u];
	mx = as[u];
	for (int i = last[u]; i; i = ed[i].next) {
		int v = ed[i].to;
		if (v == fa) continue;
		mx = max(mx, getAns(v, u));
	}
	return mx;
}
void work(int S) {
	p = m = 0;
	as[S] = 0;
	dfs(S, S);
	if (m / 2 == p - 1) ans += getAns(S, 0); else 
		for (int i = 1; i <= p; i++)
			ans += num[stk[i]] * 1ll * (d[stk[i]] - 1);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i), num[++cnt] = a[i], num[++cnt] = b[i];
    sort(num + 1, num + 1 + cnt);
	cnt = unique(num + 1, num + 1 + cnt) - num - 1;
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(num + 1, num + 1 + cnt, a[i]) - num,
		b[i] = lower_bound(num + 1, num + 1 + cnt, b[i]) - num,
		addEdge(a[i], b[i]);
	for (int i = 1; i <= cnt; i++) if (!vis[i]) work(i);
	printf("%lld\n", ans);
    return 0;
}
