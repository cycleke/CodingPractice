#include <cstdio>
#include <cstring>

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

const int N = 105;
int dis[N][N];

void SelfMin(int &a, const int &b) { if (b < a) a = b;}

int main() {
	freopen("T.in", "r", stdin); freopen("T.out", "w", stdout);
	int i, j, k, inf; long long totdis;
	memset(dis, 63, sizeof dis); inf = dis[0][0];
	for (int Case = 1;; ++Case) {
		k = 0;
		while (1) {
			i = geti(); j = geti();
			if (!i && !j) break; ++k;
			dis[i][j] = 1;
		}
		if (!k) break;
		for (i = 1; i <= 100; ++i) dis[i][i] = 0;
		for (k = 1; k <= 100; ++k)
		  for (i = 1; i <= 100; ++i)
			for (j = 1; j <= 100; ++j)
			  SelfMin(dis[i][j], dis[i][k] + dis[k][j]);
		k = 0; totdis = 0LL;
		for (i = 1; i <= 100; ++i)
		  for (j = 1; j <= 100; ++j)
			if ((i ^ j) && (dis[i][j] ^ inf)) totdis += dis[i][j], ++k;
		printf("Case %d: average length between pages = %.3lf clicks\n", Case, (double)totdis / k);
		memset(dis, 63, sizeof dis);
	}
	return 0;
}

