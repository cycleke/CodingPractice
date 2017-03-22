#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MaxN(100005);
typedef unsigned long long ull;
struct FastInput {
	char b[5<<20], *s;
	FastInput() : s(b) {
		b[fread(b, 1, 5 << 20, stdin)] = 0;
	}
	template<class T>
		inline void gi(T &a) {
			while (*s < 48) ++s;
			a = *s++ - 48;
			while (47 < *s) a = (a << 3) + (a << 1) + *s++ - 48;
		}
} io;
struct FastOutput {
	char bufout[3<<19], outtmp[50], *pout;
	FastOutput() : pout(bufout) {}
	inline void write() {
		*pout = 0;
		fwrite(bufout, sizeof(char), pout - bufout, stdout);
	}
#define out_char(c) *(pout++) = c
	inline void out_int(ull x) {
		if(!x) {
			out_char('0');
			return;
		}
		register int len = 0;
		while(x) {
			outtmp[len++] = x % 10 + 48;
			x /= 10;
		}
		for(--len; ~len; --len) out_char(outtmp[len]);
		out_char('\n');
	}
} op;
struct edge {
	int to;
	edge *nxt;
} edge_mset[MaxN << 1], *cedge = edge_mset, *g[MaxN];
#define add_edge(u, v) { \
	*cedge = (edge) {v, g[u]}; \
	g[u] = cedge++; \
}
int dfn, in[MaxN], top[MaxN], fa[MaxN], son[MaxN], size[MaxN], val[MaxN];
ull s[MaxN];
inline void d1(int u) {
	int v;
	size[u] = 1;
	s[u] = val[u];
	for (edge *it = g[u]; it; it = it->nxt)
	  if ((v = it->to) ^ fa[u]) {
		  fa[v] = u;
		  d1(v);
		  s[u] += s[v];
		  size[u] += size[v];
		  if (size[son[u]] < size[v])
			son[u] = v;
	  }
}
inline void d2(int u, int anc) {
	top[u] = anc;
	in[u] = ++dfn;
	if (son[u]) d2(son[u], anc);
	for (edge *it = g[u]; it; it = it->nxt)
	  if (!in[it->to]) d2(it->to, it->to);
}
struct node {
	int d[2], mx[2], mi[2], size;
	ull sum, val;
	long long lazy;
	node *ls, *rs;
	node() {}
	node (int x, int y, ull s) : val(s) , sum(s) {
		lazy = 0;
		d[0] = mx[0] = mi[0] = x;
		d[1] = mx[1] = mi[1] = y;
	}
	inline void maintain(const node &a) {		
		if (a.mx[1] > mx[1]) mx[1] = a.mx[1];
		if (a.mi[1] < mi[1]) mi[1] = a.mi[1];
		if (a.mx[0] > mx[0]) mx[0] = a.mx[0];
		if (a.mi[0] < mi[0]) mi[0] = a.mi[0];
	}
	inline bool x(const int &l, const int &r, const int &a) const {
		return l <= mx[a] && mi[a] <= r;
	}
	inline void pd() {
		if (!lazy) return;
		if (ls) {
			ls->lazy += lazy;
			ls->val += lazy;
			ls->sum += ls->size * lazy;
		}
		if (rs) {
			rs->lazy += lazy;
			rs->val += lazy;
			rs->sum += rs->size * lazy;
		}
		lazy = 0;
	}
} C[MaxN], *rt;
int cmp_d;
inline bool operator < (const node &a, const node &b) {
	return a.d[cmp_d] < b.d[cmp_d];
}
inline node *build(int l, int r, int d) {
	int mid = (l + r) >> 1;
	cmp_d = d;
	nth_element(C + l, C + mid, C + r + 1);
	node *u = C + mid;
	u->size = r - l + 1;
	if (l < mid) {
		u->ls = build(l, mid - 1, d ^ 1);
		u->maintain(*(u->ls));
		u->sum += u->ls->sum;
	}
	if (mid < r) {
		u->rs = build(mid + 1, r, d ^ 1);
		u->maintain(*(u->rs));
		u->sum += u->rs->sum;
	}
	return u;
}
inline void update(node *u, const int &l, const int &r, const long long &delta) {
	if (l <= u->mi[1] && u->mx[1] <= r) {
		u->sum += u->size * delta;
		u->val += delta;
		u->lazy += delta;
		return;
	}
	u->pd();
	if (l <= u->d[1] && u->d[1] <= r)
	  u->val += delta;
	if (u->ls && u->ls->x(l, r, 1))
	  update(u->ls, l, r, delta);
	if (u->rs && u->rs->x(l, r, 1))
	  update(u->rs, l, r, delta);
	u->sum = u->val + (u->ls ? u->ls->sum : 0) + (u->rs ? u->rs->sum : 0);
}
inline void modify(int u, long long delta) {
	while (u) {
		update(rt, in[top[u]], in[u], delta);
		u = fa[top[u]];
	}
}
inline void query(node *u, const int &l, const int &r, ull &v) {
	if (l <= u->mi[0] && u->mx[0] <= r)
	  return (void)(v += u->sum);
	if (l <= u->d[0] && u->d[0] <= r) v += u->val;
	u->pd();
	if (u->ls && u->ls->x(l, r, 0)) query(u->ls, l, r, v);
	if (u->rs && u->rs->x(l, r, 0)) query(u->rs, l, r, v);
}
int main() {
	int n, m, a, b, root, type;
	io.gi(n), io.gi(m);
	for (register int i = 1; i <= n; i += 4) {
		io.gi(val[i]);
		if (i < n) io.gi(val[i + 1]); {
			if (i + 1 < n) io.gi(val[i + 2]); {
				if (i + 2 < n) io.gi(val[i + 3]);
			}
		}
	}
	for (register int i = 0; i < n; i += 4) {
		io.gi(a), io.gi(b);
		if (a) {
			add_edge(a, b);
			add_edge(b, a);
		} else
		  root = b;
		if (i + 1 < n) {
			io.gi(a), io.gi(b);
			if (a) {
				add_edge(a, b);
				add_edge(b, a);
			} else
			  root = b;
			if (i + 2 < n) {
				io.gi(a), io.gi(b);
				if (a) {
					add_edge(a, b);
					add_edge(b, a);
				} else
				  root = b;
				if (i + 3 < n) {
					io.gi(a), io.gi(b);
					if (a) {
						add_edge(a, b);
						add_edge(b, a);
					} else
					  root = b;
				}
			}
		}
	}
	d1(root);
	d2(root, root);
	for (register int i = 1, r; i <= n; i += 4) {
		C[i] = node(i, in[i], s[i]);
		if (i < n) {
			C[i + 1] = node(i + 1, in[i + 1], s[i + 1]);
			if (i + 1 < n) {
				C[i + 2] = node(i + 2, in[i + 2], s[i + 2]);
				if (i + 2 < n) {
					C[i + 3] = node(i + 3, in[i + 3], s[i + 3]);
				}
			}
		}
	}
	rt = build(1, n, 0);
	ull x;
	while (m--) {
		io.gi(type), io.gi(a), io.gi(b);
		if (type == 1) {
			modify(a, (long long)b - val[a]);
			val[a] = b;
		} else {
			x = 0;
			query(rt, a, b, x);
			op.out_int(x);
		}
	}
	op.write();
	return 0;
}
