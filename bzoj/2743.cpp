#include <cstdio>
#include <algorithm>
typedef int arr[1000005];
arr C, pre, last, ans;
int n, m, c;
struct query {
	int l, r, id;
}q[1000005];
bool operator < (const query&a,const query&b) {
	return a.r < b.r;
}
void add(int x,int v) {
	for (; x <= n; x += x & -x)
		C[x] += v;
}
int sum(int x) {
	static int r;
	for (r = 0; x; x -= x & -x)
		r += C[x];
	return r;
}
int main() {
	scanf("%d%d%d", &n, &c, &m);
	for (int i = 1, a; i <= n; ++i) {
		scanf("%d", &a);
		pre[i] = last[a];
		last[a] = i;
	}
	for (int i = 1, l, r; i <= m; ++i) {
		scanf("%d%d", &l, &r);
		q[i] = (query){l, r, i};
	}
	std::sort(q + 1, q + m + 1);
	for (int i = 1, j = 1; i <= n; ++i) {
		if (pre[i]) add(pre[i], 1);
		if (pre[pre[i]]) add(pre[pre[i]], -1);
		while (i == q[j].r) {
			ans[q[j].id] = sum(q[j].r) - sum(q[j].l - 1);
			if (++j > m) i = n;
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
