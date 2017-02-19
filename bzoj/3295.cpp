#include <cstdio>
#include <algorithm>
#define N 100005
int n, m, tr[N];
void add(int x, const int &delta) {
	for (; x <= n; x += x & -x)
	  tr[x] += delta;
}
int sum(int x) {
	static int r;
	for (r = 0; x; x ^= x & -x)
	  r += tr[x];
	return r;
}
struct dot {
	int x, y, t;
} a[N], ta[N];
int pos[N];
long long ans[N];
void cdq(int l, int r) {
	if (l >= r)
	  return;
	int m = (l + r) >> 1;
	int i1 = l, i2 = m + 1, i;
	for (i = l; i <= r; ++i) 
		if (a[i].t <= m)
		  ta[i1++] = a[i];
		else 
		  ta[i2++] = a[i];
	for (i = l; i <= r; ++i)
	  a[i] = ta[i];
	i1 = l;
	for (i = m + 1; i <= r; ++i) {
		for (; i1 <= m && a[i1].x < a[i].x; ++i1)
		  add(a[i1].y, 1);
		ans[a[i].t] += i1 - l - sum(a[i].y);
	}
	for (i = l; i < i1; ++i)
	  add(a[i].y, -1);
	i1 = m;
	for (int i = r; i > m; --i) {
		for (; i1 >= l && a[i1].x > a[i].x; --i1)
		  add(a[i1].y, 1);
		ans[a[i].t] += sum(a[i].y - 1);
	}
	for (i = i1 + 1; i <= m; ++i)
	  add(a[i].y, -1);
	cdq(l, m); cdq(m + 1, r);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i].y);
		a[i].x = i;
		pos[a[i].y] = i;
	}
	int curtime = n;
	for (int i = 1, x; i <= m; ++i) {
		scanf("%d", &x);
		a[pos[x]].t = curtime--;
	}
	for (int i = 1; i <= n; ++i)
	  if (!a[i].t) a[i].t = curtime--;
	cdq(1, n);
	for (int i = 1; i <= n; ++i)
	  ans[i] += ans[i - 1];
	for (int i = n; i >= n - m + 1; --i)
	  printf("%lld\n", ans[i]);
	return 0;
}
