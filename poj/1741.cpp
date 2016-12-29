#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e4 + 10;
typedef pair<int, int>pii;
vector<pii>G[N];
int n, Siz, s[N], f[N], root, d[N], K, ans;
vector<int>dep;
bool vis[N];

void getroot(int u, int fa) {
	int v; s[u] = 1; f[u] = 0;
	for (int i = 0; i < G[u].size(); ++i)
	  if ((v = G[u][i].first) != fa && !vis[v]) {
		  getroot(v, u); s[u] += s[v];
		  if (s[v] > f[u]) f[u] = s[v];
	  }
	if (Siz - s[u] > f[u]) f[u] = Siz - s[u];
	if (f[u] < f[root]) root = u;
}

void getdep(int u, int fa) {
	int v; dep.push_back(d[u]);
	s[u] = 1; 
	for (int i = 0; i < G[u].size(); ++i) 
	  if ((v = G[u][i].first) != fa && !vis[v]) {
		  d[v] = d[u] + G[u][i].second;
		  getdep(v, u);
		  s[u] += s[v];
	  }
}

int F(int u, int di) {
	dep.clear(); d[u] = di;
	getdep(u, 0);
	sort(dep.begin(), dep.end());
	int ret = 0;
	for (int l = 0, r = dep.size() - 1; l < r;) {
		if (dep[l] + dep[r] <= K) ret += r - l++;
		else --r;
	}
	return ret;
}

void Work(int u) {
	int v; ans += F(u, 0);
	vis[u] = true;
	for (int i = 0; i < G[u].size(); ++i) 
	  if (!vis[v = G[u][i].first]){
		  ans -= F(v, G[u][i].second);
		  f[0] = Siz = s[v];
		  getroot(v, root = 0);
		  Work(root);
	  }
}

int main() {
	int a, b, c;
	while (scanf("%d%d", &n, &K) ^ EOF) {
		if (!n && !K) break;
		for (int i = 0; i <= n; ++i) G[i].clear();
		memset(vis, false, sizeof vis);

		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			G[a].push_back(make_pair(b, c));
			G[b].push_back(make_pair(a, c));
		}

		f[0] = Siz = n;
		getroot(1, root = 0);
		ans = 0;
		Work(root);
		printf("%d\n", ans);
	}
}
