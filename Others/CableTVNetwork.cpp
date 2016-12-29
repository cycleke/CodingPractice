#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int ina; char inc; bool insign;
inline int geti() {
	insign = false;
	while ((inc = getchar()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getchar()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; return insign ? -ina : ina;
}

const int N = 202, INF = 0x7f7f7f7f;
int head[N], to[N * N << 1], nxt[N * N << 1], totE, C[N * N << 1], tC[N * N << 1];
void Adde(int a, int b, int c) {
	to[totE] = b; nxt[totE] = head[a]; C[totE] = c; head[a] = totE++;
	to[totE] = a; nxt[totE] = head[b]; C[totE] = 0; head[b] = totE++;
}

int n, m, s, t, d[N], dt[N], last[N];

int dfs(int u, int flow) {
	if (u == t || !flow) return flow;
	int ret = 0, tmp;
	for (int i = last[u]; ~i; i = nxt[i]) 
	  if (d[u] > d[to[i]] && tC[i] > 0) {
		  last[u] = i; tmp = dfs(to[i], min(flow, tC[i]));
		  ret += tmp; flow -= tmp;
		  tC[i] -= tmp; tC[i^1] += tmp;
		  if (!flow) return ret;
	  }
	if (d[s] >= n) return ret;
	if (!(--dt[d[u]])) d[s] = n;
	++d[u]; ++dt[d[u]]; last[u] = head[u];
	return ret;
}

int SAP() {
	memset(d, 0, sizeof d); memset(dt, 0, sizeof dt);
	dt[0] = n; 
	for (int i = 0; i < n; ++i) last[i] = head[i];
	for (int i = 0; i < totE; ++i) tC[i] = C[i];
	int ret = 0;
	while (d[s] < n) ret += dfs(s, INF);
	return ret;
}

int main() {
	freopen("T.in", "r", stdin); freopen("T.out", "w", stdout);
	int a, b;
	while (scanf("%d%d", &n, &m) ^ EOF) {
		memset(head, -1, sizeof head); totE = 0;
		for (a = 0; a < n; ++a) Adde(a, a + n, 1);
		while (m--) {
			a = geti(), b = geti();
			Adde(a + n, b, INF); Adde(b + n, a, INF);
		}
		a = INF; s = m = n; n <<= 1;
		for (t = 1; t < m; ++t)
		  a = min(a, SAP());
		a = min(a, m);
		printf("%d\n", a);
	}
	return 0;
}


