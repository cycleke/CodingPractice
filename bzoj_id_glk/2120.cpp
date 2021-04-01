#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;
#define N 10010
#define M 1000010
#define inf 0x3f3f3f3f

int n, T, root[N], color[M];
struct D {
	int pre, nxt, v;
}f[N];
namespace Treap {
	int totNode, ch[N << 7][2], v[N << 7], w[N << 7], r[N << 7], s[N << 7];
	inline void maintain(int u) {
		s[u] = s[ch[u][0]] + s[ch[u][1]] + w[u];
	}
	inline void Rot(int &u, bool k) {
		int t = ch[u][k^1];
		ch[u][k^1] = ch[t][k];
		ch[t][k] = u; maintain(u); maintain(t);
		u = t;
	}
	void Ins(int &u, int val) {
		if (!u) {
			u = ++totNode; ch[u][0] = ch[u][1] = 0;
			v[u] = val; w[u] = 1; s[u] = 1; r[u] = rand();
		} else {
			++s[u];	int k = val < v[u] ? 0 : 1;
			if (val == v[u]) { ++w[u]; return; }
			Ins(ch[u][k], val);
			if (r[ch[u][k]] > r[u]) Rot(u, k ^ 1);
		}
	}
	void Del(int &u, int val) {
		if (!u) return;
		if (v[u] == val) {
			if (w[u] > 1) { --s[u]; --w[u]; return; }
			if (!ch[u][0] || !ch[u][1]) u = ch[u][0] + ch[u][1];
			else {
				int k = r[ch[u][0]] > r[ch[u][1]];
				Rot(u, k); Del(u, val);
			}
		} else {
			--s[u]; Del(ch[u][val < v[u] ? 0 : 1], val);
		}
	}
	int Query(int u, int val) {
		if (!u) return 0;
		if (val <= v[u]) return Query(ch[u][0], val);
		return w[u] + s[ch[u][0]] + Query(ch[u][1], val);
	}
}

void Build(int i, int val) {
	for (; i <= n; i += i & -i) Treap::Ins(root[i], val);
}
void Change(int i, int val) {
	for (; i <= n; i += i & -i) Treap::Del(root[i], val);
}
int ask	(int x, int val) {
	int ret = 0;
	for (; x > 0; x -= x & -x)
		ret += Treap::Query(root[x], val);
	return ret;
}

int main() {

	scanf("%d%d", &n, &T);
	int x, y; char op[3];
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		f[i].pre = color[x]; f[i].v = x;
		f[color[x]].nxt = i; color[x] = i;
		f[i].nxt = inf; Build(i, f[i].pre);
	}
	
	while (T--) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'Q') printf("%d\n", ask(y, x) - ask(x - 1, x));
		else {
			Change(x, f[x].pre); Change(f[x].nxt, x);
			Build(f[x].nxt, f[x].pre);
			if (f[x].pre) f[f[x].pre].nxt = f[x].nxt;
			if (f[x].nxt ^ inf) f[f[x].nxt].nxt = f[x].pre;
			else color[f[x].v] = f[x].pre;
			f[x].v = y, f[x].pre = color[y], f[x].nxt = 0;
			while (f[x].pre > x) {
				f[x].nxt = f[x].pre;
				f[x].pre = f[f[x].pre].pre;
			}
			if (!f[x].nxt) f[x].nxt = inf;
			if (f[x].pre) f[f[x].pre].nxt = x;
			if (f[x].nxt ^ inf) f[f[x].nxt].pre = x;
			else color[y] = x;
			Build(x, f[x].pre); Build(f[x].nxt, x);
			Change(f[x].nxt, f[x].pre);
		}
	}

	return 0;
}

