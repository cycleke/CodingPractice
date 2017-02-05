#include <cstdio>
#include <algorithm>

#define N 50005
#define MS 2000005
std::pair<int, int> a[N];
//Trie
int rt[N], ch[2][MS], idx[MS], cnd;
int pre[N], nxt[N];

inline void insert(const int &p, const int &v) {
	static int i, pre, cur, d;
	rt[p] = cur = ++cnd;
	pre = rt[p - 1];
	idx[cur] = p;
	for (i = 1 << 30; i; i >>= 1) {
		d = (v & i) ? 1 : 0;
		ch[d ^ 1][cur] = ch[d ^ 1][pre];
		ch[d][cur] = ++cnd;
		idx[cnd] = p;
		cur = cnd;
		pre = ch[d][pre];
	}
}

inline int query(const int &l, const int &r, const int &v) {
	static int i, ret, cur, d;
	for (cur = rt[r], ret = 0, i = 1 << 30; i; i >>= 1) {
		d = (v & i) ? 0 : 1;
		if (idx[ch[d][cur]] >= l)
			ret ^= i, cur = ch[d][cur];
		else
			cur = ch[d ^ 1][cur];
	}
	return ret;
}

int main() {
	int n, x, i, ans, t;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &x);
		insert(i, x);
		a[i] = std::make_pair(x, i);
		pre[i] = i - 1;
		nxt[i] = i + 1;
	}
	pre[n + 1] = n;
	nxt[n + 1] = n + 1;
	std::sort(a + 1, a + n + 1);
	ans = 0;
	for (i = 1; i < n; ++i) {
		x = a[i].second;
		t = query(pre[pre[x]] + 1, nxt[nxt[x]] - 1, a[i].first);
		if (t > ans) ans = t;
		nxt[pre[x]] = nxt[x];
		pre[nxt[x]] = pre[x];
	}
	printf("%d\n", ans);
	return 0;
}
