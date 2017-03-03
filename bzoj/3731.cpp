#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MaxN = 1e5 + 5, Block_Cnt = 2e5 + 5;
namespace FastIO {
	const int buffersize = (1 << 16) | (0x3f);
	int a;
	char b[buffersize], *s = b, *e = b, c;
	inline char gc() {
		if (s == e) {
			s = b;
			e = b + fread(b, 1, buffersize, stdin);
			if (s == e)
			  return EOF;
		}
		return *s++;
	}
	inline int gi() {
		do c = gc(); while (c < 48);
		for (a = c - 48; 47 < (c = gc()); a = (a << 3) + (a << 1) + c - 48);
		return a;
	}
}
struct Block {
	vector<int>a;
#define all a.begin(), a.end()
	void insert(const int &x) {
		a.insert(lower_bound(all, x + 1), x);
	}
	void erase(const int &x) {
		a.erase(lower_bound(all, x));
	}
	void modify(const int &pre, const int &cur) {
		erase(pre);
		insert(cur);
	}
	int query(const int &x) const {
		int t = upper_bound(all, x) - a.begin() + 1;
		return a.size() - t + 1;
	}
	int size() const {
		return a.size();
	}
}block[Block_Cnt];
struct edge {
	int to;
	bool ban;
	edge *nxt;
} edge_mset[MaxN * 3], *head[MaxN << 1], *block_head[Block_Cnt], *from[MaxN << 1], *block_from[Block_Cnt], *cedge = edge_mset;
#define over(u) for (edge *it = u; it; it = it->nxt)
inline void add_edge(edge **_g, int u, int v) {
	*cedge = (edge) {v, false, _g[u]};
	_g[u] = cedge;
	if (_g == head)
	  from[v] = cedge++;
	else
	  block_from[v] = cedge++;
}
int n, m, cnt, block_size, ans;
typedef int arr[MaxN << 1];
arr fa, a, belong;
void dfs(int u) {
	if (!fa[u] || block[belong[fa[u]]].size() >= block_size) {
		belong[u] = ++cnt;
		add_edge(block_head, belong[fa[u]], cnt);
	} else
	  belong[u] = belong[fa[u]];
	block[belong[u]].insert(a[u]);
	over(head[u])
		if (it->to ^ fa[u]) {
			fa[it->to] = u;
			from[it->to] = it;
			dfs(it->to);
		} else
		  it->ban = true;
}
void inblock(int x, const int &y) {
	ans += block[x].query(y);
	over(block_head[x])
		if (!it->ban)
		  inblock(it->to, y);
}
void getans(int x, const int &y) {
	if (a[x] > y) ++ans;
	over(head[x]) if (!it->ban) {
		if (belong[it->to] ^ belong[x])
		  inblock(belong[it->to], y);
		else
		  getans(it->to, y);
	} 
}
void split(int u, bool flag, int nb, int z, int pb) {
	flag |= u == z;
	if (flag) {
		block[pb].erase(a[u]);
		block[belong[u] = nb].insert(a[u]);
	} 
	over(head[u]) if (!it->ban) {
		if (belong[it->to] == pb)
		  split(it->to, flag, nb, z, pb);
		else if (flag) {
			block_from[belong[it->to]]->ban = true;
			add_edge(block_head, nb, belong[it->to]);
		}
	}
}
int main() {
	int i, x, y;
	n = FastIO::gi();
	for (i = 1; i < n; ++i) {
		x = FastIO::gi();
		y = FastIO::gi();
		add_edge(head, x, y);
		add_edge(head, y, x);
	}
	for (i = 1; i <= n; ++i)
	  a[i] = FastIO::gi();
	block_size = (int)(sqrt(n * log2(n)) + 1e-7);
	dfs(1);
	for (m = FastIO::gi(); m; --m) {
		i = FastIO::gi();
		x = FastIO::gi() ^ ans;
		if (i ^ 3) y = FastIO::gi() ^ ans;
		if (!i) {
			ans = 0;
			getans(x, y);
			printf("%d\n", ans);
		} else if (i < 2) {
			block[belong[x]].modify(a[x], y);
			a[x] = y;
		} else if (i < 3) {
			++n;
			a[n] = y;
			fa[n] = x;
			add_edge(head, x, n);
			if (block[belong[x]].size() >= block_size) {
				belong[n] = ++cnt;
				add_edge(block_head, belong[x], cnt);
			} else 
			  belong[n] = belong[x];
			block[belong[n]].insert(y);
		} else {
			if (belong[x] ^ belong[fa[x]])
			  block_from[belong[x]]->ban = true;
			else {
				for (y = x; fa[y] && belong[fa[y]] == belong[x]; y = fa[y]);
				split(y, 0, ++cnt, x, belong[x]);
			}
			from[x]->ban = true;
			fa[x] = 0;
		}
	}
	return 0;
}
