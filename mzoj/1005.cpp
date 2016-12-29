#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1010, M = 100005, inf = 0x7f7f7f7f;
int dis[N][N], sd[N], bd[N];

int to[M], nxt[M], head[N], w[M], totE;
inline void Adde(int a, int b, int c) { to[totE] = b; w[totE] = c; nxt[totE] = head[a]; head[a] = totE++; }

//SPFA
queue<int>q;
bool inq[N];
void SPFA(int s, int *d) {
	memset(d, 127, N * sizeof(int));
	d[s] = 0; q.push(s);
	int p;
	while (!q.empty()) {
		p = q.front(); inq[p] = false; q.pop();
		for (int i = head[p]; ~i; i = nxt[i]) 
		  if (d[to[i]] > d[p] + w[i]) {
			  d[to[i]] = d[p] + w[i];
			  if (!inq[to[i]]) {
				  q.push(to[i]); inq[to[i]] = true;
			  }
		  }
	}
}

int main() {
	int n, m, x, a, b, t;
	scanf("%d%d%d", &n, &m, &x);
	memset(dis, 127, sizeof dis);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &t);
		if (t < dis[a][b]) dis[a][b] = t;
	}
	
	memset(head, -1, sizeof head);
	totE = 0;
	for (int i = 1; i <= n; ++i)
	  for (int j = 1; j <= n; ++j)
		if (dis[i][j] ^ inf) Adde(i, j, dis[i][j]);
	SPFA(x, sd);

	memset(head, -1, sizeof head);
	totE = 0;
	for (int i = 1; i <= n; ++i)
	  for (int j = 1; j <= n; ++j)
		if (dis[i][j] ^ inf) Adde(j, i, dis[i][j]);
	SPFA(x, bd);
	
	int ans = 0;
	
	for (int i = 1; i <= n; ++i)
	  if ((x ^ i) && ans < sd[i] + bd[i]) ans = sd[i] + bd[i];
	
	printf("%d\n", ans);

	return 0;
}
