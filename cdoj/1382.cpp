#include <bits/stdc++.h>
using namespace std;
#define N 50005
#define M 400005
int to[M], nxt[M], w[M], head[N], totE, vis[M];
int sta[N], fail, cnt, tot;

void dfs(int u) {
	++tot; if (sta[u]) ++cnt;
	for (int i = head[u]; ~i; i = nxt[i])
	  if (!vis[i]) {
		  vis[i] = vis[i^1] = true;
		  if (~sta[to[i]]) {
			  if (sta[u] ^ sta[to[i]] ^ w[i]) fail = 1;
		  } else {
			  sta[to[i]] = sta[u] ^ w[i];
			  dfs(to[i]);
		  }
	  }
}

int main() {
	int n, m, a, b, c;
	scanf("%d%d", &n, &m);
	memset(head, -1, N << 2);
	memset(sta, -1, N << 2);
	while (m--) {
		scanf("%d%d%d", &a, &b, &c);
		to[totE]=b,w[totE]=c,nxt[totE]=head[a],head[a]=totE++;
		to[totE]=a,w[totE]=c,nxt[totE]=head[b],head[b]=totE++;
	}
	int ans = 0;
	for (int i = 1; i <= n && !fail; ++i)
	  if (sta[i] < 0) {
		tot = cnt = 0; sta[i] = 0;
		dfs(i); if (tot-cnt<cnt) cnt = tot - cnt;
		ans += cnt;
	  }
	if (fail) return puts("Pan must forget something."), 0;
	int cnt = 0;
	printf("%d\n",ans);
	return 0;
}
