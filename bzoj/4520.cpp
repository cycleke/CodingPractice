#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100005
int n, m, tx, ty, rt, h[N], cmp_d;
inline void cmin(int &a, const int &b) {
	if (b < a) a = b;
}
inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}
priority_queue<long long, vector<long long>, greater<long long> >heap;
struct node {
	int d[2], x[2], y[2], ls, rs;
	void init(const int &a, const int &b) {
		d[0] = x[0] = x[1] = a;
		d[1] = y[0] = y[1] = b;
	}
}p[N];
bool cmp(const int &a, const int &b) {
	return p[a].d[cmp_d] < p[b].d[cmp_d];
}
void update(node &u, const node &v) {
	cmin(u.x[0], v.x[0]);
	cmin(u.y[0], v.y[0]);
	cmax(u.x[1], v.x[1]);
	cmax(u.y[1], v.y[1]);
}
void build(int &u, int l, int r, int D) {
	int mid = (l + r) >> 1;
	cmp_d = D;
	nth_element(h + l, h + mid, h + r + 1, cmp);
	u = h[mid];
	if (l < mid) {
		build(p[u].ls, l, mid - 1, D ^ 1);
		update(p[u], p[p[u].ls]);
	}
	if (mid < r) {
		build(p[u].rs, mid + 1, r, D ^ 1);
		update(p[u], p[p[u].rs]);
	}
}
inline long long p2(const int &x) {
	return (long long)x * x;
}
inline long long func(const node &u) {
	return max(p2(u.x[0] - tx), p2(u.x[1] - tx)) + max(p2(u.y[0] - ty), p2(u.y[1] - ty));
}
void query(int u) {
	long long dl = func(p[p[u].ls]), dr = func(p[p[u].rs]), du = p2(p[u].d[0] - tx) + p2(p[u].d[1] - ty);
	if (du > heap.top()) {
		heap.pop();
		heap.push(du);
	}
	if (dl < dr) {
		if (p[u].rs && dr > heap.top()) query(p[u].rs);
		if (p[u].ls && dl > heap.top()) query(p[u].ls);
	} else {
		if (p[u].ls && dl > heap.top()) query(p[u].ls);
		if (p[u].rs && dr > heap.top()) query(p[u].rs);
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		p[i].init(x, y);
		h[i] = i;
	}
	build(rt, 1, n, 0);
	for (int i = 0; i < m; ++i) {
		heap.push(0);
		heap.push(0);
	}
	for (int i = 1; i <= n; ++i) {
		tx = p[i].d[0], ty = p[i].d[1];
		query(rt);
	}
	printf("%lld\n", heap.top());
	return 0;
}
