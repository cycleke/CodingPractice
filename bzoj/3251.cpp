#include <cstdio>
#include <algorithm>

#define N 100005
#define YY (void)puts("Y")
#define NN (void)puts("N")
struct edge {int t; edge *n;} me[N], *g[N], *ce = me;
#define adde(a, b) (ce->t = b, ce->n = g[a], g[a] = ce++)
int v[N], q[N], fa[N], deep[N];

inline void bfs() {
	int *l = q, *r = q;
	edge *it;
	*r++ = 1;
	while (l < r) {
		for (it = g[*l]; it; it = it->n)
			deep[*r++ = it->t] = deep[*l] + 1;
		++l;
	}
}

inline void query(int a, int b) {
	static int tp, i;
	for (tp = 0; (tp ^ 51) && (a ^ b); a = fa[a]) {
		if (deep[a] < deep[b]) std::swap(a, b);
		q[tp++] = v[a];
	}
	if (tp ^ 51) {
		q[tp++] = v[a];
		std::sort(q, q + tp);
		for (tp -= 3; tp > -1; --tp)
			if ((long long)q[tp] + q[tp + 1] > q[tp + 2])
				return YY;
		return NN;
	} else
		return YY;
}

int main() {
	int n, q, i, x, y;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; ++i)
		scanf("%d", v + i);
	for (i = 1; i <  n; ++i) {
		scanf("%d%d", &x, &y);
		fa[y] = x;
		adde(x, y);
	}

	bfs();

	while (q--) {
		scanf("%d%d%d", &i, &x, &y);
		if (i) v[x] = y;
		else query(x, y);
	}
	
	return 0;
}
