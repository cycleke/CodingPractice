#include <cstdio>
//Input
char Inc; int Ina;
inline int geti() {
    while ((Inc = getchar()) < '0' || Inc > '9'); Ina = Inc - '0';
    while ((Inc = getchar()) >= '0' && Inc <= '9') Ina = (Ina << 3) + (Ina << 1) + Inc - '0'; return Ina;
}
//
const int Mod = 1e9 + 7, N = 100005;
int f[N][17]; bool vis[N];
int find(int i, int j) {
	return (f[i][j] ^ i) ? f[i][j] = find(f[i][j], j) : i;
}

void Union(int k, int i, int j) {
	if (find(i, k) ^ find(j, k)) {
		f[f[i][k]][k] = f[j][k];
		if (!k--) return;
		Union(k, i, j); Union(k, i + (1 << k), j + (1 << k));
	}
}

int main() {
	int n, m, i, j, a, b, c, d, ans;
	n = geti(), m = geti();
	if (n < 2) return puts("9"), 0;
	for (j = 0; (1 << j) <= n; ++j) 
	  for (i = 1; i + (1 << j) - 1 <= n; ++i)
		f[i][j] = i;
	while (m--) {
		a = geti(), b = geti(), c = geti(), d = geti();
		j = b - a + 1, i = 0;
		while ((1 << i + 1) <= j) ++i;
		Union(i, a, c); Union(i, b - (1 << i) + 1, d - (1 << i) + 1);
	}
	ans = 9; vis[find(1, 0)] = true;
	for (i = 2; i <= n; ++i) if (!vis[find(i, 0)]) vis[find(i, 0)] = true, ans = 10LL * ans % Mod;
	printf("%d\n", ans);
	return 0;
}
