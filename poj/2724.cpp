#include <cstdio>
#include <cstring>

const int N = 1024;
int vis[N], vist[N], Tim, SearchTime, link[N], n, m, MS;

bool dfs(int u) {
	for (int i = 0, t; i < n; ++i) {
		t = u ^ (1<<i);
		if (!(vis[t] ^ Tim) && (vist[t] ^ SearchTime)) {
			vist[t] = SearchTime;
			if (!~link[t] || dfs(link[t])) return link[t] = u, true;
		}
	}
	return false;
}

int main() {
	int tot, match, pos, t, i; char ch;
	while (scanf("%d%d", &n, &m) ^ EOF) {
		if (!n && !m) break;
		++Tim; MS = 1 << n; tot = match = 0;
		while (m--) {
			t = 0; pos = -1; getchar();
			for (i=0;i<n;++i) ch = getchar(), (ch^'*')?1:pos=i, (ch^'0')?t|=1<<i:1;
			vis[t] = Tim; if (~pos) vis[t^(1<<pos)] = Tim;
		}
		for (i = 0; i < MS; ++i) tot += vis[i] == Tim;
		memset(link, -1, sizeof link);
		for (i = 0; i < MS; ++i) if (vis[i] == Tim && (++SearchTime, dfs(i))) ++match;
		match >>= 1;
		printf("%d\n", tot - match);
	}
	return 0;
}
