#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int ina; char inc, inb[1<<16], *ins = inb, *ine = inb; bool insign;
inline char getc() {
	if (ins == ine) ine = (ins = inb) + fread(inb, 1, 1 << 16, stdin);
	return (ins == ine) ? EOF : *ins++;
}
inline int geti() {
	insign = false;
	while ((inc = getc()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; return insign ? -ina : ina;
}

const int N = 105, INF = 0x7f7f7f7f;
int head[N], to[N * N << 1], nxt[N * N << 1], totE, C[N * N << 1];
void Adde(int a, int b, int c) {
	to[totE] = b; nxt[totE] = head[a]; C[totE] = c; head[a] = totE++;
	to[totE] = a; nxt[totE] = head[b]; C[totE] = 0; head[b] = totE++;
}

int n, m, s, t, d[N], dt[N], last[N];

int dfs(int u, int flow) {
	if (u == t || !flow) return flow;
	int ret = 0, tmp;
	for (int i = last[u]; ~i; i = nxt[i]) 
	  if (d[u] > d[to[i]] && C[i] > 0) {
		  last[u] = i; tmp = dfs(to[i], min(flow, C[i]));
		  ret += tmp; flow -= tmp;
		  C[i] -= tmp; C[i^1] += tmp;
		  if (!flow) return ret;
	  }
	if (d[s] >= n) return ret;
	if (!(--dt[d[u]])) d[s] = n;
	++d[u]; ++dt[d[u]]; last[u] = head[u];
	return ret;
}

int SAP() {
	memset(d, 0, sizeof d); memset(dt, 0, sizeof dt);
	dt[0] = 0; for (int i = 1; i <= n; ++i) last[i] = head[i];
	int ret = 0;
	while (d[s] < n) ret += dfs(s, INF);
	return ret;
}

int main() {
	freopen("T.in", "r", stdin); freopen("T.out", "w", stdout);
	int Case = 0, a, b, c;
	while (n = geti()) {
		memset(head, -1, sizeof head);
		s = geti(), t = geti(), m = geti(); totE = 0;
		while (m--) {
			a = geti(), b = geti(), c = geti();
			Adde(a, b, c); Adde(b, a, c);
		}
		printf("Network %d\nThe bandwidth is %d.\n\n", ++Case, SAP());
	}
	return 0;
}


