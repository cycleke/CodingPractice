#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 65;
const double oo = 1e22;
int Nxt[N], to[N], nxt[N], head[N], totE, n, m, Siz[N];
#define Adde(a,b) (to[totE] = b, nxt[totE] = head[a], head[a] = totE++)
double kk[N], dp[N][N][N], C[N], tmp[N][N], k, _MinT;
#define cans(a) ((_MinT = (a)) > ans ? ans = _MinT : 1)

void init() {
	for (int i = 0; i <= n; head[i++] = -1)
	  for (int j = 0; j <= n; ++j)
		for (int k = 0; k <= n; ++k)
		  dp[i][j][k] = -oo;
	totE = 0;
}

void Cal(int u, int dep) {
	for (int i = 0; i <= Siz[u]; ++i)
	  for (int j = 0; j <= m; ++j)
		tmp[i][j] = -oo;
	tmp[0][0] = 0.;
	for (int i = head[u], s = 1; ~i; i = nxt[i], ++s) {
		int v = to[i];
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= j; ++k)
				tmp[s][j] = max(tmp[s][j], tmp[s-1][k] + dp[v][j-k][dep]);
			
	}
}

void dfs(int u) {
	Siz[u] = 0;
	for (int i = head[u]; ~i; i = nxt[i], ++Siz[u]) dfs(to[i]);
	Cal(u, 2);
	for (int i = 0; i <= n; ++i)
	  for (int j = 1; j <= m; ++j)
		dp[u][j][i] = tmp[Siz[u]][j-1] + C[u] * k;//直接将此站接到1后面

	for (int i = 0; i <= n; ++i) {
		Cal(u, i + 1);
		for (int j = 0; j <= m; ++j)
		  dp[u][j][i] = max(dp[u][j][i], tmp[Siz[u]][j] + C[u] * kk[i]);
	}
}

int main() {
	scanf("%d%d%lf", &n, &m, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", Nxt + i);
	for (int i = 1; i <= n; ++i) scanf("%lf", C + i);
	kk[0] = 1; kk[1] = k;
	double ans = -oo;
	for (int i = 2; i < N; ++i) kk[i] = kk[i-1] * k;
	for (int i = Nxt[1], len = 2, j; i ^ 1; i = Nxt[i], ++len) {
		init();
		for (j = 2; j <= n; ++j) 
		  if (j ^ i) Adde(Nxt[j], j); else Adde(1, j);
		dfs(1);
		cans(dp[1][m - (Nxt[i] != 1)][0] / (1. - kk[len]));
	}
	printf("%.2lf\n", ans);
	
	return 0;
}
