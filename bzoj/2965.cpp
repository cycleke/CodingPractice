#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

inline char gc() {
	static char buffer[1<<16], *s = buffer, *e = buffer;
	if (s == e) e = (s = buffer) + fread(buffer, 1, 1<<16, stdin);
	return s == e ? EOF : *s++;
}
inline void gi(int &a) {
	static char c, f; f = 0;
	while (c = gc(), c < '0') f |= c == '-'; a = c - '0';
	while (c = gc(), '-' < c) 
	  a = (a << 3) + (a << 1) + c - '0';
	if (f) a = -a;
}
inline void cmin(int &a, const int &b) {
	if (b < a) a = b;
}
inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}
/*************************/
const int N = 233, M = 633;
int id[N], tot, n, vis[M], g[N], et = 1, blo, col, ans[13];
long long sum[N];
struct E {int t, w, n, p;} e[M];
struct P {
	int x, y;
	bool operator < (const P &a) const {
		return (x ^ a.x) ? (x < a.x) : y < a.y;
	}
	bool operator == (const P &a) const {
		return ! ((x ^ a.x) | (y ^ a.y));
	}
	P operator - (const P &a) const {
		return (P) {x - a.x, y - a.y};
	}
	long long operator * (const P &a) const {
		return (long long)x * a.y - (long long)y * a.x;
	}
}p[N];
struct D {
	P p; int n;
	bool operator < (const D &a) const {
		return atan2(p.y, p.x) < atan2(a.p.y, a.p.x);
	}
}cmpd[N], a[N];

bool cmp(const D &a, const D &b) {
	return (a.p == b.p) ? a.n < b.n : a.p < b.p;
}

inline void sort_edge(int u) {
	int cnt = 0;
	for (int i = g[u]; i; i = e[i].n)
	  cmpd[++cnt] = (D) {p[e[i].t] - p[u], i};
	std::sort(cmpd + 1, cmpd + cnt + 1);
	for (int i = 2; i <= cnt; ++i)
	  e[cmpd[i].n].p = cmpd[i - 1].n;
	e[cmpd[1].n].p = cmpd[cnt].n;
}

void get_area(int co, int i) {
	int o = i, x = e[i ^ 1].t;
	for (vis[i] = co; (i = e[i ^ 1].p) ^ o; vis[i] = co)
	  sum[co] += (p[e[i].t] - p[x]) * (p[e[i^1].t] - p[x]);
	if (sum[co] < 0) sum[co] = -sum[co];
}

double nx;

struct Tree {
	int tot;
	struct node {
		double k, b, x0;
		int col;
		bool operator < (const node &a) const {
			double y1 = k * (nx + 0.001) + b;
			double y2 = a.k * (nx + 0.001) + a.b;
			if (y1 < y2) return true;
			if (y2 < y1) return false;
			return x0 < a.x0;
		}
	}tr[M];
	std::set<node> s;
	std::set<node>::iterator it[M];
	void init() {
		P u, v;
		for (int i = 2; i <= et; i += 2) {
			node &x = tr[i>>1];
			u = p[e[i].t], v = p[e[i^1].t];
			x.k = (double)(u.y- v.y) / (u.x - v.x);
			x.b = u.y - x.k * u.x;
			x.x0 = std::min(u.x, v.x);
			x.col = vis[i ^ (u.x < v.x)];
		}
		tr[0].b = -1, tr[0].col = blo;
		s.insert(*tr);
		tot = (et >> 1) + 1;
	}
	void insert(int x, int o) {
		nx = x;
		it[o] = s.insert(tr[o]).first;
	}
	void remove(int o) {
		s.erase(it[o]);
	}
	void movedata(int o, int x, int y) {
		nx = x;
		tr[tot].b = y;
		id[o - ::n] = (--s.lower_bound(tr[tot]))->col;
	}
}Tr;

struct MF {
	int et, g[N], og[N], to[M], nxt[M], c[M], C[M], la[N], tot, s, t, d[N], dt[N];
	void ade(int x, int y, int z) {
		to[++et] = y, C[et] = z, nxt[et] = og[x], og[x] = et;
		to[++et] = x, C[et] = z, nxt[et] = og[y], og[y] = et;
	}
	void adde(int x, int y, int z) {
		to[++tot] = y, c[tot] = z, nxt[tot] = g[x], g[x] = tot;
		to[++tot] = x, c[tot] = z, nxt[tot] = g[y], g[y] = tot;
	}
	int dfs(int u, int flow) {
		if (u == t || !flow) return flow;
		int ret = 0, tmp;
		for (int &i = la[u]; i; i = nxt[i])
		  if (c[i] && d[u] == d[to[i]] + 1) {
			  tmp = dfs(to[i], std::min(flow, c[i]));
			  c[i] -= tmp, c[i^1] += tmp;
			  ret += tmp, flow -= tmp;
			  if (!flow || d[s] > ::col + 2) return ret;
		  }
		if (!(--dt[d[u]])) d[s] = ::col + 3;
		++dt[++d[u]];
		la[u] = g[u];
		return ret;
	}
	int SAP() {
		int ret = 0;
		memset(d, 0, sizeof d);
		memset(dt, 0, sizeof dt);
		dt[0] = ::col + 1;
		while (d[s] < ::col + 3)
		  ret += dfs(s, 0x3f3f3f3f);
		return ret;
	}
	void mf(int p) {
		memset(ans, 63, sizeof ans);
		int end = 1 << p, cnt, i, x, tmp, S;
		for (S = 1; S ^ end; ++S) {
			memcpy(g, og, sizeof og);
			memcpy(c, C, sizeof c);
			tot = et, cnt = 0, x = S;
			for (i = 1; i <= p; ++i, x >>= 1)
			  if (x & 1) ++cnt, adde(s, id[i], 0x3f3f3f3f);
			tmp = SAP();
			for (; cnt; --cnt)
			  cmin(ans[cnt], tmp);
		}
	}
}G;

int main() {
#ifndef ONLINE_JUDGE
	freopen("2965.in", "r", stdin);
	freopen("2965.out", "w", stdout);
#endif
	int t, m, x, y, i;
	gi(t), gi(n), gi(m);
	tot = n, G.et = 1;
	for (i = 1; i <= t; ++i) {
		gi(x), gi(y);
		a[++tot] = (D){(P) {x, y}, i + n};
	}
	for (i = 1; i <= n; ++i) {
		gi(x), gi(y);
		a[i] = (D){p[i] = (P){x,y}, i};
	}
	while (m--) {
		gi(x), gi(y), gi(i);
		e[++et] = (E) {y, i, g[x]}, g[x] = et;
		e[++et] = (E) {x, i, g[y]}, g[y] = et;
	}
	for (i = 1; i <= n; ++i)
	  sort_edge(i);
	for (i = 2; i <= et; ++i)
	  if (!vis[i]) get_area(++col, i);
	blo = 1;
	for (i = 2; i <= col; ++i)
	  if (sum[blo] < sum[i]) blo = i;
	for (i = 2; i <= et; i += 2)
	  G.ade(vis[i], vis[i ^ 1], e[i].w);
	Tr.init();
	std::sort(a + 1, a + tot + 1, cmp);
	for (i = 1; i <= tot; ++i)
	  if((x = a[i].n) <= n) {
		  for (int j = g[x]; j; j = e[j].n)
			if (p[e[j].t].x < p[x].x) Tr.remove(j >> 1);
			else if (p[x].x < p[e[j].t].x) Tr.insert(p[x].x, j >> 1);
	  } else Tr.movedata(x, a[i].p.x, a[i].p.y);
	G.s = col + 1;
	G.t = blo;
	G.mf(t);
	for (i = 1; i <= t; ++i)
	  printf("%d\n", ans[i]);
	return 0;
}
