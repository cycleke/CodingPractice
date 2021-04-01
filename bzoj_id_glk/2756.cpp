#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MS = 100000, N = 42;
const LL inl = 1LL << 55;

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

int mp[N][N], n, m;
bool col[N][N];
LL Sum[2], Num[2], mv;

namespace CC {
	int To[MS], Nxt[MS], totE, head[N * N], S, T, d[N * N], dt[N * N];
	LL C[MS];
	inline void Adde(int a, int b, LL c) {
		To[totE] = b; Nxt[totE] = head[a]; C[totE] = c; head[a] = totE++;
		To[totE] = a; Nxt[totE] = head[b]; C[totE] = 0; head[b] = totE++;
	}
	
	const int dx[] = {0,0,-1,1};
	const int dy[] = {1,-1,0,0};

	inline int getp(const int &x, const int &y) { return (x-1)*m + y; }

	LL dfs(int u, LL flow) {
		if (u==T||!flow) return flow;
		LL res = 0, t;
		for (int i = head[u]; ~i; i = Nxt[i]) 
		if (d[u] == d[To[i]] + 1 && C[i] > 0){
			t = dfs(To[i], min(flow, C[i]));
			C[i] -= t, C[i^1] += t;
			res += t, flow -= t;
			if (!flow) return res;
			if (d[S] > T) return res;
		}
		if (!(--dt[d[u]])) d[S] = T + 1;
		++dt[++d[u]];
		return res;
	}
	

	bool check(LL x) {
		memset(head, -1, sizeof head); totE = 0;
		S = 0, T = getp(n, m) + 1;
		LL t, tot = 0, maxflow = 0;
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= m; ++j) {
			  t = x - mp[i][j];
			  if (col[i][j]) Adde(getp(i, j), T, t);
			  else Adde(S, getp(i, j), t);
			  tot += t;
		  }
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= m; ++j) 
			for (int k = 0; k < 4; ++k) {
				int _i = i + dx[k], _j = j + dy[k];
				if (_i < 1 || _i > n || _j < 1 || _j > m) continue;
				if (!col[i][j]) Adde(getp(i, j), getp(_i, _j), inl);
			}
		memset(d, 0, sizeof d); memset(dt, 0, sizeof dt);
		dt[0] = T + 1;
		while (d[S] < T + 1) maxflow += dfs(S, inl);
		return tot == (maxflow << 1);
	}

}
void init() {
	memset(col, 0, sizeof col);
	n = geti(), m = geti(); 
	*Sum = Sum[1] = *Num = Num[1] = mv = 0LL;
	bool st = true;
	for (int i = 1; i <= n; ++i) 
	  for (int j = 1; j <= m; ++j) {
		  if ((mp[i][j] = geti()) > mv) mv = mp[i][j];
		  col[i][j] = !col[i][j-1];
		  if (j <= 1) col[i][j] = (st = !st);
		  ++Num[col[i][j]]; Sum[col[i][j]] += mp[i][j];
	  }
}

#define getskip(a) (a*n*m - Sum[0] - Sum[1]) >> 1

void Work() {
	if (n * m & 1) {
		LL x = Sum[0] - Sum[1];
		if (x >= mv && CC::check(x)) printf("%lld\n", getskip(x));
		else puts("-1");
	} else {
		LL l = mv, r = inl / 1000, M, ans = -1;
		while (l <= r) {
			M = l + r >> 1;
			if (CC::check(M)) r = (ans = M) - 1;
			else l = M + 1;
		}
		if (~ans) printf("%lld\n", getskip(ans));
		else puts("-1");
	}
}

int main() {
	freopen("T.in", "r", stdin);
	for (int T = geti(); T; --T) {
		init(); Work();
	}
	return 0;
}
