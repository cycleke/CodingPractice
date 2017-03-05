#include <cstdio>
#include <cstring>

const int MaxN = 1e5 + 4, MaxM = 1e6 + 3;

namespace FastIO {
	const int buf = 1 << 16 | 123;
	char b[buf], *s = b, *e = b, c;
	inline char gc() {
		if (s == e) {
			s = b;
			e = b + fread(b, 1, buf, stdin);
			if (s == e)
				return EOF;
		}
		return *s++;
	}
	inline void gi(int &a) {
		do c = gc(); while (c < 48);
		a = c - 48;
		while (47 < (c = gc())) 
			a = (a << 3) + (a << 1) + c - 48;
	}
}

struct edge {
	int to, w;
	edge *nxt;
} edge_mset[MaxM << 1], *cedge = edge_mset, *g[MaxN];

inline void add_edge(int u, int v, int w) {
	*cedge = (edge) {v, w, g[u]};
	g[u] = cedge++;
}

typedef int arr[MaxN];

bool inq[MaxN];
arr dis, sec_dis, from, que;
int *l = que, *r = que, *end = que + MaxN;

inline void nxt(int * &it) {
	if (++it >= end) it = que;
}

inline void SPFA() {
	int u, v;
	edge *it;
	while (l != r) {
		u = *l;
		nxt(l);
		inq[u] = false;
		for (it = g[u]; it; it = it->nxt) {
			v = it->to;
			if (sec_dis[u] + it->w <= dis[v]) {
				if (from[v] ^ u)
					sec_dis[v] = dis[v];
				dis[v] = sec_dis[u] + it->w;
				from[v] = u;
				if (!inq[v]) {
					inq[v] = true;
					*r = v;
					nxt(r);
				}
			} else if (sec_dis[u] + it->w < sec_dis[v]) {
				sec_dis[v] = sec_dis[u] + it->w;
				if (!inq[v]) {
					inq[v] = true;
					*r = v;
					nxt(r);
				}
			}
		}
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	memset(dis, 63, sizeof dis);
	memset(sec_dis, 63, sizeof sec_dis);
	memset(from, -1, sizeof from);
	int n, m, k, i, u, v, w;
	using namespace FastIO;
	gi(n), gi(m), gi(k);
	for (i = 0; i < m; ++i) {
		gi(u), gi(v), gi(w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	for (i = 0; i < k; ++i) {
		gi(u);
		dis[u] = sec_dis[u] = 0;
		*r = u;
		nxt(r);
		inq[u] = true;
	}
	SPFA();
	printf("%d\n", *sec_dis);
	return 0;
}
