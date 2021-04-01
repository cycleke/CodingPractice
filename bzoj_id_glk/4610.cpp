#include <cstdio>
#include <cstring>
#define MS 1010
#define N 52
int root[N], ch[2][MS], v[MS], totNode;
int fa[N];
int find(int a) { return (fa[a]^a)?fa[a]=find(fa[a]):a; }
void Insert(int &u, const int &val) {
	if (!u) {
		v[u = ++totNode] = val; ch[0][u] = ch[1][u] = 0;
	} else {
		if (val < v[u]) Insert(ch[0][u], val);
		else Insert(ch[1][u], val);
	}
}
bool diff(int u, int v) {
	if (!u && !v) return false;
	if (!u || !v) return true;
	return diff(ch[0][u], ch[0][v]) || diff(ch[1][u], ch[1][v]);
}

int main() {
	int n, k, i, j, a, x, y;
	scanf("%d%d", &n, &k);
	for (i = 1; i <= n; ++i) {
		fa[i] = i;
		for (j = 1; j <= k; ++j) {
			scanf("%d", &a);
			Insert(root[i], a);
		}
	}
	a = 0;
	for (i = 1; i <= n; ++i)
	  for (j = 1; j < i; ++j)
		if (!diff(root[i], root[j])) {
			x = find(i), y = find(j);
			if (x ^ y) fa[x] = y;
		}
	for (i = 1; i <= n; ++i) a += fa[i] == i;
	printf("%d\n", a);
	return 0;
}
