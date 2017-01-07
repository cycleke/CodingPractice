#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 50005, M = 200005, MaxNum = 1000005;
struct query {
	int l, r, id;
}q[M];
bool operator < (const query&a, const query&b) {
	return a.r < b.r;
}
int last[MaxNum], pre[MaxNum], C[N], n, m, ans[M];
int sum(int x) {
	static int r;
	for (r = 0; x; x -= x & -x)
		r += C[x];
	return r;
}
void add(int x, int v) {
	for (; x <= n; x += x & -x)
		C[x] += v;
}
int main() {
	scanf("%d", &n);
	for (int i = 1, a; i <= n; ++i) {
		scanf("%d", &a);
		pre[i] = last[a];
		last[a] = i;
	}
	scanf("%d", &m);
	for (int i = 1, l, r; i <= m; ++ i) {
		scanf("%d%d", &l, &r);
		q[i] = (query){l, r, i};
	}
	std::sort(q + 1, q + m + 1);
	for (int i = 1,j = 1; i <= n; ++i) {
		if (pre[i]) add(pre[i], -1);
		add(i, 1);
		while (q[j].r == i) {
			ans[q[j].id] = sum(q[j].r) - sum(q[j].l - 1);
			if (++j > m) i = n;
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
