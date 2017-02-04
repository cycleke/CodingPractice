#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 100013
#define SIZE 26
struct edge {int t; edge *n;} me[N], *g[N], *ce;
#define adde(a, b) (ce->t = b, ce->n = g[a], g[a] = ce++)
int ch[N][SIZE], fail[N], in[N], out[N], que[N], son[N], tp[N], _clock, size[N];
long long C1[N], C2[N];

inline char gc() {
    static char b[1 << 16], *s = b, *e = b;
    if (s == e) e = (s = b) + fread(b, 1, 1 << 16, stdin);
    return (s == e) ? EOF : *s++;
}
 
inline void gi(int &a) {
    static char c;
    while (c = gc(), c < '0'); a = c - '0';
    while (c = gc(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}

inline void BuildFail() {
	static int i, *l, *r, f, p;
	fail[0] = 1;
	l = r = que;
	for (i = 0; i ^ SIZE; ++i)
		if (ch[ch[0][i] = 1][i]) {
			fail[ch[1][i]] = 1;
			*r++ = ch[1][i];
		}
	while (l < r) {
		p = *l++;
		f = fail[p];
		adde(f, p);
		for (i = 0; i ^ SIZE; ++i)
			if (ch[p][i]) {
				for (f = fail[p];!ch[f][i]; f = fail[f]);
				fail[*r++ = ch[p][i]] = ch[f][i];
			}
	}
}

void dfs1(int u) {
	size[u] = 1;
	son[u] = 0;
	for (edge *it = g[u]; it; it = it->n) {
		dfs1(it->t);
		if (size[it->t] > size[son[u]])
			son[u] = it->t;
		size[u] += size[it->t];
	}
}

void dfs2(int u, int anc) {
	in[u] = ++_clock;
	tp[u] = anc;
	if (son[u]) dfs2(son[u], anc);
	for (edge *it = g[u]; it; it = it->n)
		if (son[u] ^ it->t) dfs2(it->t, it->t);
	out[u] = _clock;
}

inline long long sum(long long *tr,int x) {
	static long long r;
	for (r = 0; x; x -= x & -x)
		r += tr[x];
	return r;
}

inline long long sum(int x) {
	return sum(C1, x) * (x + 1LL) - sum(C2, x);
}

inline long long query(const int &l, const int &r) {
	return sum(r) - sum(l - 1);
}

inline void add(long long *tr, int x, const long long &val) {
	for (; x < _clock; x += x & -x)
		tr[x] += val;
}

inline void add(int x, const long long &val) {
	add(C1, x, val); add(C2, x, x * val);
}

inline void modify(const int &l, const int &r) {
	add(l, 1LL), add(r + 1, -1LL);
}

void GetSum(int u, long long &v) {
    if (!u || que[tp[u]] >= in[u])
		return;
	if (que[tp[u]])
		v += query(que[tp[u]] + 1, in[u]);
	else {
		v += query(in[tp[u]], in[u]);
		GetSum(fail[tp[u]], v);
	}
	que[tp[u]] = in[u];
}

inline void Clear(int u) {
	for (; u; u = fail[tp[u]])
		que[tp[u]] = 0;
}

struct D{int l, r;} a[N * 5];
bool operator < (const D &a, const D &b) {
	return a.l < b.l;
}
int main() {
	//freopen("t.in", "r", stdin);
	int __, n, m, k, i, x;
	long long ans;
	char typec;
	gi(__);
	while (__--) {
		gi(n);
		memset(C1, 0, (n + 3) * sizeof(long long));
		memset(C2, 0, (n + 3) * sizeof(long long));
		memset(ch, 0, (n + 3) * sizeof(ch[0]));
		memset(g, 0, (n + 3) * sizeof(edge*));
		memset(fail, 0, (n + 3) * sizeof(int));
		for (i = 2; i <= n; ++i) {
			gi(x);
			do typec = gc(); while (typec < 'a');
			ch[x][typec - 'a'] = i;
		}
		ce = me;
		BuildFail();
		fail[1] = 0;
		dfs1(1);
		_clock = 0;
		dfs2(1, 1);
		++_clock;
/*
		for (i = 1; i <= n; ++i) {
			printf("%d %d", fail[i], in[i]);
		}
*/		
		//scanf("%d", &m);
		gi(m);
		while (m--) {
			//scanf("%d%d", &i, &k);
			gi(i), gi(k);
			if (i < 2) {
				for (i = 0; i < k; ++i) {
					//scanf("%d", &x);
					gi(x);
					a[i] = (D){in[x], out[x]};
				}
				std::sort(a, a + k);
				x = 0;
				for (i = 0; i < k; ++i) {
					if (a[i].r <= x) continue;
					x = a[i].r;
					modify(a[i].l, a[i].r);
				}
			}
			else {
				ans = 0LL;

				for (i = 0; i < k; ++i) {
					gi(x);
					Clear(son[i] = x);
				}
				for (i = 0; i < k; ++i) 
					GetSum(son[i], ans);
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
