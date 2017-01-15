#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define inf 0x3f3f3f3f
typedef int edge[50003], vert[1003];
edge nt, c, w, to;
vert d, hd, q, from;
int ce, T;
bool inq[1003];
inline void adde(int x, int y, int z, int v) {
	to[ce] = y, nt[ce] = hd[x];
	c[ce] = z, w[ce] = v;
	hd[x] = ce++;
}
#define nxt(i) (++(i)>=1003?i=0:i)
inline bool SPFA() {
	static int u, v, i, l, r;
	for (i = 1; i <= T; ++i) d[i] = inf;
	d[0] = 0; q[0] = 0; from[0] = -1;
	for (l = 0, r = 1; l ^ r; ) {
		u = q[l]; nxt(l);
		for (i = hd[u]; ~i; i = nt[i])
			if (c[i] && d[v = to[i]] > w[i] + d[u]) {
				d[v] = w[i] + d[u];
				from[v] = i;
				if (!inq[v]) inq[v] = true, q[r] = v, nxt(r);
			}
		inq[u] = false;
	}
	return d[T] < inf;
}

inline int mcf() {
	static int f, e, ret;
	for (f = inf, e = from[T], ret = 0; ~e; e = from[to[e^1]]) f = min(f, c[e]), ret += w[e];
	for (e = from[T]; ~e; e = from[to[e^1]]) c[e] -= f, c[e^1] += f;
	return f * ret;
}

int main() {
	int n, m, i, x, y, v;
	memset(hd, -1, sizeof hd);
	scanf("%d%d", &n, &m);
	T = n + 2;
	for (y = 0, i = 1; i <= n; ++i) {
		scanf("%d", &x);
		v = x - y;
		y = x;
		if (v > 0) adde(0, i, v, 0), adde(i, 0, 0, 0);
		else adde(i, T, -v, 0), adde(T, i, 0, 0);
		adde(i + 1, i, inf, 0), adde(i, i + 1, 0, 0);
	}
	adde(n + 1, T, y, 0), adde(T, n + 1, 0, 0);
	while (m--) {
		scanf("%d%d%d", &x, &y, &v);
		++y;
		adde(x, y, inf, v), adde(y, x, 0, -v);
	}
	v = 0;
	while (SPFA())
		v += mcf();
	printf("%d\n", v);
	return 0;
}
