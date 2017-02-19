#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MaxN 100005
int mp[MaxN], *cnp, range;
pair<int, int>p[MaxN<<1];
int rt[MaxN], ls[MaxN<<7], rs[MaxN<<7], cnt[MaxN<<7], cnd;
long long sum[MaxN<<7];
inline int gid(const int &x) {
	return lower_bound(mp + 1, cnp, x) - mp;
}
void insert(int x, int &y, int l, int r, const int &p, const int &delta) {
	y = ++cnd;
	ls[y] = ls[x], rs[y] = rs[x];
	cnt[y] = cnt[x] + delta;
	sum[y] = sum[x] + delta * mp[p];
	if (l >= r) return;
	int m = l + r >> 1;
	if (p <= m) insert(ls[x], ls[y], l, m, p, delta);
	else insert(rs[x], rs[y], m + 1, r, p, delta);
}
inline long long query(int u, int k) {
	static long long ret;
	static int l, r;
	if (k >= cnt[u]) return sum[u];
	for (ret = 0, l = 1, r = range; k; ) {
		if (l ^ r) {
			if (k >= cnt[ls[u]]) ret += sum[ls[u]], k -= cnt[ls[u]], l = (l + r >> 1) + 1, u = rs[u];
			else r = (l + r >> 1), u = ls[u];
		} else return ret + sum[u] / cnt[u] * k;
	}return ret;
}
int main() {
	int N, M, X, P, x, a, b, c;
	long long t, pre;
	while (scanf("%d%d%d%d", &N, &M, &X, &P) ^ EOF) {
		cnp = mp + 1;
		for (int i = 0, l, r, d; i < N; ++i) {
			scanf("%d%d%d", &l, &r, &d);
			p[i<<1] = make_pair(l, d);
			p[i<<1|1] = make_pair(r + 1, -d);
			*cnp++ = d;
		}
		sort(p, p + 2 * N);
		sort(mp + 1, cnp);
		cnp = unique(mp + 1, cnp);
		range = cnp - mp - 1;
		rt[0] = 0;
		cnd = 0;
		for (int i = 1, j = 0; i <= X; ++i) {
			rt[i] = rt[i - 1];
			while (j < 2 * N && p[j].first == i) {
				if (p[j].second < 0) insert(rt[i], rt[i], 1, range, gid(-p[j].second), -1);
				else insert(rt[i], rt[i], 1, range, gid(p[j].second), 1);
				++j;
			}
		}
		pre = 1LL;
		while(M--) {
			scanf("%d%d%d%d", &x, &a, &b, &c);
			t = query(rt[x], (a * pre + b) % c);
			if (pre > P) t <<= 1;
			printf("%lld\n", pre = t);
		}
	}
	return 0;
}

