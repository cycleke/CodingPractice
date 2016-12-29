#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int sta[N], ans[N];
char S[N];
typedef pair<int, int>pii;
vector<int>g[N];
vector<pii>query[N];


void dfs(int u, int dep) {
	pii t;
	for (int i = 0; i < query[u].size(); ++i) {
		t = query[u][i];
		ans[t.first] ^= sta[t.second];
	}
	for (int i = 0; i < g[u].size(); ++i) dfs(g[u][i], dep + 1);
	sta[dep] ^= 1 << S[u] - 'a';
	for (int i = 0; i < query[u].size(); ++i) {
		t = query[u][i];
		ans[t.first] ^= sta[t.second];
	}
}

int main() {
	int n, m, v, h;
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; ++i) {
		scanf("%d", &v); g[v].push_back(i);
	}
	scanf("%s", S + 1);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &v, &h);
		query[v].push_back(make_pair(i, h));
	}
	dfs(1, 1);
	for (int i = 1; i <= m; ++i) puts((ans[i] & (ans[i] - 1)) ? "No" : "Yes");
	return 0;
}
