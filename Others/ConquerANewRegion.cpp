#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200005;
typedef long long LL;
int n, fa[N];
LL Sum[N], Siz[N];
int find(int u) { return u==fa[u] ? u : fa[u] = find(fa[u]); }
struct edge {
	int u, v; LL c;
	bool operator < (const edge &a) const {
		return c > a.c;
	}
}E[N];

LL Work() {
	for (int i = 1; i <  n; ++i) scanf("%d%d%lld", &E[i].u, &E[i].v, &E[i].c);
	for (int i = 1; i <= n; ++i) fa[i] = i, Sum[i] = 0LL, Siz[i] = 1;
	sort(E + 1, E + n);
	LL ans;
	for (int i = 1; i < n; ++i) {
		int x = find(E[i].u), y = find(E[i].v);
		LL t1 = Sum[x] + Siz[y] * E[i].c, t2 = Sum[y] + Siz[x] * E[i].c;
		if (t1 < t2) {
			fa[x] = y; ans = Sum[y] = t2;
			Siz[y] += Siz[x];
		} else {
			fa[y] = x; ans = Sum[x] = t1;
			Siz[x] += Siz[y];
		}
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) ^ EOF) printf("%lld\n", Work());
	return 0;
}
