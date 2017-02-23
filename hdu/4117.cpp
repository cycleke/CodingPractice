#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int MaxN = 2e4 + 5, MaxSize = 3e5 + 5, Size = 26, ST_Size = 1 << 16 | 7;

typedef int arr[MaxN];

arr W, S;
int n;
char s[MaxSize];

struct edge {
	int to;
	edge *nxt;
	edge(int to = 0, edge *nxt = NULL) :
		to(to), nxt(nxt) {}
} edge_mset[MaxN], *g[MaxSize], *curten_edge;
#define overedge edge *it = g[u]; it; it = it->nxt
inline void add_edge(int a, int b) {
	*curten_edge = edge(b, g[a]);
	g[a] = curten_edge++;
}
inline void init_edge(const int &n) {
	memset(g, 0, n * sizeof(edge*));
	curten_edge = edge_mset;
}

int dfn;
arr in, ou;
#define ls u << 1
#define rs u << 1 | 1
#define Range const int &x, const int &y
#define VarMid int mid = (C[u].l + C[u].r) >> 1
struct Node {
	int l, r, value;
	Node(int l = 0, int r = 0, int value = 0) :
		l(l), r(r), value(value) {}
	
	bool inrange(Range) const {
		return (!l && !r) || (x <= l && r <= y);
	}

	void update(const int &a) {
		if (value < a)
			value = a;
	}
	
} C[ST_Size];
void build(int u, int l, int r) {
	C[u] = Node(l, r);
	if (r - l > 1) {
		VarMid;
		build(ls, l, mid);
		build(rs, mid, r);
	}
}
void update(int u, Range, const int &v) {
	if (C[u].inrange(x, y))
		return C[u].update(v);
	VarMid;
	if (x < mid) update(ls, x, y, v);
	if (y >  mid) update(rs, x, y, v);
}
inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}
int query(const int &pos) {
	int ret = 0, u = 1, l = 0, r = dfn;
	while (r - l > 0) {
		VarMid;
		if (pos < mid)
			u = ls, r = mid;
		else
			u = rs, l = mid + 1;
		cmax(ret, C[u].value);
	}
	return ret;
}

struct AC_automata {
	queue<int>q;
	int cnt, nx_val[MaxN];
	struct Trie {
		int ch[Size], f, last, val;
		void Init() {
			val = 0;
			memset(ch, 0, sizeof ch);
		}
	} T[MaxSize];
	void add_val(int u, int x) {
		nx_val[x] = T[u].val;
		T[u].val = x;
	}
	int newnode() {
		T[cnt].Init();
		return cnt++;
	}
	void Init() {
		cnt = 0;
		newnode();
	}
	int insert(char *s, int id) {
		int u = 0, i = 0, c;
		for (char *it = s; *it; ++it, ++i) {
			c = *it - 'a';
			if (!T[u].ch[c])
				T[u].ch[c] = newnode();
			u = T[u].ch[c];
		}
		add_val(u, id);
		return i;
	}
	void BuildFail() {
		int u, c, v, r;
		for (c = 0; c < Size; ++c) {
			u = T[0].ch[c];
			if (!u) continue;
			q.push(u);
			T[u].f = T[u].last = 0;
		}
		while (!q.empty()) {
			r = q.front();
			q.pop();
			for (c = 0; c < Size; ++c) {
				u = T[r].ch[c];
				if (u) {
					q.push(u);
					v = T[u].f = T[T[r].f].ch[c];
					T[u].last = T[v].val ? v : T[v].last;
				} else
					T[r].ch[c] = T[T[r].f].ch[c];
			}
		}
	}

	void dfs(int u) {
		int l = dfn++;
		for (overedge)
			dfs(it->to);
		int r = dfn;
		for (int it = T[u].val; it; it = nx_val[it])
			in[it] = l, ou[it] = r;
	}
	void BuildTree() {
		init_edge(cnt + 1);
		for (int i = 1; i < cnt; ++i)
			if (T[i].val)
				add_edge(T[i].last, i);
		dfn = 0;
		dfs(0);
	}
	void Work() {
		int i, j, c, u, ans = 0, mx;
		build(1, 0, dfn);
		for (i = 1; i <= n; ++i) {
			u = mx = 0;
			for (j = S[i - 1]; j < S[i]; ++j) {
				c = s[j] - 'a';
				u = T[u].ch[c];
				if (T[u].val)
					cmax(mx, query(in[T[u].val]));
				else if (T[u].last)
					cmax(mx, query(in[T[T[u].last].val]));
			}
			if (W[i] > 0) {
				cmax(ans, mx += W[i]);
				update(1, in[i], ou[i], mx);
			}
		}
		printf("%d\n", ans);
	}
}ac;

void solve() {
	scanf("%d", &n);
	ac.Init();
	for (int i = 1; i <= n; ++i) {
		scanf("%s%d", s + S[i - 1], W + i);
		S[i] = ac.insert(s + S[i - 1], i) + S[i - 1];
	}
	ac.BuildFail();
	ac.BuildTree();
	ac.Work();
}

int main() {
	//freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	for (int __ = 0; __ < _;) {
		printf("Case #%d: ", ++__);
		solve();
	}
	return 0;
}
