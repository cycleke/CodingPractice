#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb; bool insign;
inline char getc() {
	if (ins == ine) ine = (ins = inb) + fread(inb, 1, 1 << 16, stdin);
	return (ins == ine) ? EOF : *ins++;
}
inline int geti() {
	insign = false;
	while ((inc = getc()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; 
	return insign ? -ina : ina;
}

const int N = 55, M = 2005;
int n, m, dis[N][N], d[M][N], deg[M];
int head[M], nxt[M<<1], to[M<<1], totE;
inline void Adde(int a, int b) { to[totE] = b; nxt[totE] = head[a]; head[a] = totE++; }

#define clr(a,b) memset(a, b, sizeof a)

void dfs(int u, int fa, int anc) {
	for (int i = head[u], v; ~i; i = nxt[i])
	if (to[i] ^ fa) {
		v = to[i]; d[v][anc] = d[u][anc] + 1;
		dfs(v, u, anc);
	}
}

void Work() {
	int i, j, k, t;
	totE = 0; m = 1;
	clr(head,-1), clr(d, 0), clr(deg, 0);
	for (i = 1; i <= n; ++i)
	  for (j = 1; j <= n; ++j)
		dis[i][j] = geti();
	for (k = 2; k <= n; ++k) {
		for (i = 1; i <= m; ++i) {
			t = dis[k][1] - d[i][1];
			for (j = 1; j < k; ++j) if (dis[k][j] - d[i][j] != t) break;
			if (j >= k) {
				while (t > 0) {
					++m; Adde(i, m); Adde(m, i);
					++deg[i], ++deg[m];
					for (j = 1; j < k; ++j)
					  d[m][j] = d[i][j] + 1;
					i = m; --t;
				}
				dfs(i, 0, k); break;
			}
		}
	}
	sort(deg + 1, deg + m + 1);
	for (i = 1; i <= m; ++i)
	  if (deg[i] > 1) printf("%d%c", deg[i], " \n"[i==m]);
}

int main() {
	freopen("T.in", "r", stdin);
	while (n = geti()) Work();
	return 0;
}
