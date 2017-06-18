#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>

#define MAXN 3033
#define _MAXN 6033
#define BUFFER_SIZE 10000000

typedef int arr[MAXN];
typedef std::vector<int> vi;
typedef std::pair<int, int> pii;

struct Fast_Input {
	char buffer[BUFFER_SIZE], *s;
	Fast_Input(FILE * in_FILE = stdin) {
		s = buffer;
		fread_unlocked(buffer, 1, BUFFER_SIZE, in_FILE);
	}
	inline void get_int(int &a) {
		while (*s < 48) ++s;
		a = *s++ ^ 48;
		while (47 < *s)
			a = (a << 3) + (a << 1) + (*s++ ^ 48);
	}
} in;

struct TWO_SAT {
	vi e[_MAXN];
	int n, mark[_MAXN], _mark, stk[_MAXN], *top;
	inline void init(const int &n) {
		++_mark;
		this->n = n << 1;
		for (int i = 0; i < this->n; ++i) e[i].clear();
	}
	inline void addClause(int u, int u_val, int v, int v_val) {
		//NOT (u == u_val AND v == v_val)
		u = u << 1 | u_val;
		v = v << 1 | v_val;
		e[u].push_back(v ^ 1);
		e[v].push_back(u ^ 1);
	}
	bool dfs(int u) {
		if (mark[u ^ 1] == _mark)
			return false;
		if (mark[u] == _mark)
			return true;
		mark[u] = _mark;
		*top++ = u;
		for (int v : e[u])
			if (!dfs(v)) return false;
		return true;
	}
	inline bool solve() {
		for (int i = 0; i ^ n; i += 2)
			if ((mark[i] ^ _mark) && (mark[i ^ 1] ^ _mark)) {
				top = stk;
				if (dfs(i)) continue;
				while (top > stk) mark[*--top] = 0;
				if (!dfs(i ^ 1))
					return false;
			}
		return true;
	}
} solver;

const int dx[][2] = {{0, 1}, {1, 0}};
const int dy[][2] = {{0, 1}, {0, 1}};

int _vis, _visit, n, *_w;
std::vector<pii> edge[MAXN];
arr vis, visit, col, x, y, work;

inline void init() {
	++_visit;
	in.get_int(n);
	for (int i = 0; i < n; ++i) {
		in.get_int(x[i]);
		in.get_int(y[i]);
		edge[i].clear();
	}
	int m, u, v, w;
	in.get_int(m);
	while (m--) {
		in.get_int(u);
		in.get_int(v);
		in.get_int(w);
		--u, --v;
		edge[u].push_back(std::make_pair(v, w));
		edge[v].push_back(std::make_pair(u, w));
	}
}

inline int disc(int u, int v) {
	return abs(x[u] - x[v]) + abs(y[u] - y[v]);
}

bool draw(int u, int c) {
	if (vis[u] == _vis)
		return col[u] == c;
	*_w++ = u;
	col[u] = c;
	vis[u] = _vis;
	visit[u] = _visit;
	for (pii e : edge[u])
		if (!draw(e.first, c ^ (e.second & 1) ^ (disc(u, e.first) & 1)))
			return false;
	return true;
}

inline bool can(int u, int c) {
	++_vis;
	_w = work + 1;
	if (!draw(u, c))
		return false;
	solver.init(n);
	for (int u(*--_w); _w > work; u = *--_w)
		for (pii e : edge[u]) {
			int v = e.first, w = e.second;
			for (int iu = 0; iu < 2; ++iu)
				for (int iv = 0; iv < 2; ++iv) {
					int dist = abs(x[u] - x[v] + dx[col[u]][iu] - dx[col[v]][iv])
						+ abs(y[u] - y[v] + dy[col[u]][iu] - dy[col[v]][iv]);
					if (dist ^ w) solver.addClause(u, iu, v, iv);
				}
		}
	return solver.solve();
}

inline bool judge() {
	init();
	for (int i = 0; i < n; ++i)
		if (visit[i] ^ _visit)
			if (!can(i, 0) && !can(i, 1))
				return false;
	return true;
}

int main() {

	int o_o;
	in.get_int(o_o);
	while (o_o--)
		puts(judge() ? "possible" : "impossible");
	return 0;
}
