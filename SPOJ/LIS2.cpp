#include <cstdio>
#include <algorithm>

#define N 100003

inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

int tr[N], ha[N], ans[N], hcnt;

void upd(int x, const int &v) {
	for (; x < hcnt; x += x & -x)
	  cmax(tr[x], v);
}

int quy(int x) {
	static int r;
	for (r = 0; x; x ^= x & -x)
	  cmax(r, tr[x]);
	return r;
}

void clr(int x) {
	for (; x < hcnt; x += x & -x)
	  tr[x] = 0;
}

struct point {
	int x, y, id;
	bool operator < (const point &a) const {
		return x < a.x;
	}
}p[N];

bool cmpid(const point &a, const point &b) {
	return a.id < b.id;
}

void cdq(int l, int r) {
	if (l >= r) 
	  return;
	int m = (l + r) >> 1;
	cdq(l, m);
	std::sort(p + l, p + m + 1);
	std::sort(p + m + 1, p + r + 1);
	for (int i = m + 1, j = l; i <= r; ++i) {
		for (; j <= m && p[j].x < p[i].x; ++j) 
		  upd(p[j].y, ans[p[j].id]);
		cmax(ans[p[i].id], quy(p[i].y - 1) + 1);
	}
	for (int i = l; i <= m; ++i) clr(p[i].y);
	std::sort(p + m + 1, p + r + 1, cmpid);
	cdq(m + 1, r);
}

int main() {
	int n, ans = 0;
	hcnt = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].id = i;
		ha[i] = p[i].y;
		::ans[i] = 1;
	}
	std::sort(ha + 1, ha + n + 1);
	hcnt = std::unique(ha + 1, ha + n + 1) - ha;
	for (int i = 1; i <= n; ++i)
	  p[i].y = std::lower_bound(ha + 1, ha + hcnt, p[i].y) - ha;
	cdq(1, n);
	for (int i = 1; i <= n; ++i) {
		cmax(ans, ::ans[i]);
		//printf("%d ", ::ans[i]);
	}
	printf("%d\n", ans);
	return 0;
}
