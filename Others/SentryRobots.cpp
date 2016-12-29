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
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; 
	return insign ? -ina : ina;
}

const int N = 105;
typedef pair<int, int>pii;
int X, Y, hx, hy, mp[N][N], G[N][N], vis[N], Timv, Timg, link[N];
pii pos[N][N];

bool dfs(int u) {
	for (int i = 1; i <= hy; ++i)
	  if (G[u][i] >= Timg && (vis[i] ^ Timv)) {
		  vis[i] = Timv;
		  if (!link[i] || dfs(link[i])) return link[i] = u;
	  }
	return false;
}

int main() {
	freopen("T.in", "r", stdin); freopen("T.out", "w", stdout);
	bool ok;
	for (int T = geti(), i, j, k, ans; T; --T) {
		X = geti(), Y = geti(); ++Timg;
		memset(mp, 0, sizeof mp); 
		memset(link, 0, sizeof link);
		for (k = geti(); k; --k) {
			i = geti(), j = geti();
			mp[i][j] = 1;
		}
		for (k = geti(); k; --k) {
			i = geti(), j = geti();
			mp[i][j] = 2;
		}
		hx = hy = 0;
		for (i = 1; i <= X; ++i) {
			ok = true;
			for (j = 1; j <= Y; ++j)
			  if (mp[i][j] == 1) {
				  if (ok) ++hx;
				  pos[i][j].first = hx;
				  ok = false;
			  } else if (mp[i][j] > 1) ok = true;
 		}
		for (j = 1; j <= Y; ++j) {
			ok = true;
			for (i = 1; i <= X; ++i)
			  if (mp[i][j] == 1) {
				  if (ok) ++hy;
				  pos[i][j].second= hy;
				  ok = false;
			  } else if (mp[i][j] > 1) ok = true;
		}
		for (i = 1; i <= X; ++i)
		  for (j = 1; j <= Y; ++j)
			if (mp[i][j] == 1) 
			  G[pos[i][j].first][pos[i][j].second] = Timg;
		ans = 0;
		for (i = 1; i <= hx; ++i)
			if (++Timv, dfs(i)) ++ans;
		printf("%d\n", ans);
	}
	return 0;
}
