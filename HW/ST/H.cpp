#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int Maxn = 500010;
int ly[Maxn << 2], dl[Maxn << 2], dr[Maxn << 2];
int lm[Maxn << 2], rm[Maxn << 2], mm[Maxn << 2];

void Up(const int &u) {
	lm[u] = lm[u<<1]; rm[u] = rm[u<<1|1];
	mm[u] = max(mm[u<<1], mm[u<<1|1]);
	if (lm[u<<1] == dr[u<<1] - dl[u<<1] + 1)
		lm[u] += lm[u<<1|1];
	if (rm[u<<1|1] == dr[u<<1|1] - dl[u<<1|1] + 1)
		rm[u] += rm[u<<1];
	mm[u] = max(mm[u], rm[u<<1] + lm[u<<1|1]);
}

void Down(const int &u) {
	if (~ly[u]) {
		if (ly[u]) {
			lm[u<<1] = rm[u<<1] = mm[u<<1] = 0;
			lm[u<<1|1] = rm[u<<1|1] = mm[u<<1|1] = 0;
			ly[u<<1] = ly[u<<1|1] = 1;
		} else {
			lm[u<<1] = rm[u<<1] = mm[u<<1] = dr[u<<1] - dl[u<<1] + 1;
			lm[u<<1|1] = rm[u<<1|1] = mm[u<<1|1] = dr[u<<1|1] - dl[u<<1|1] + 1;
			ly[u<<1] = ly[u<<1|1] = 0;
		}
		ly[u] = -1;
	}
}

void build(int u, int l, int r) {
	ly[u] = -1; dl[u] = l; dr[u] = r;
	lm[u] = rm[u] = mm[u] = r - l + 1;
	if (l == r) return;
	build(u<<1, l, (l + r) >> 1);
	build(u<<1|1, ((l + r)>>1) + 1, r);
}

int query(int u, const int &x) {
	if (dl[u] == dr[u]) return dl[u];
	Down(u);
	int mid = (dl[u] + dr[u]) >> 1;
	if (mm[u<<1] >= x)
		return query(u<<1, x);
	else if (rm[u<<1] + lm[u<<1|1] >= x)
		return mid - rm[u<<1] + 1;
	return query(u<<1|1,x);
}

void Update(int u, int x, int y, const int &val) {
	if (x == dl[u] && y == dr[u]) {
		ly[u] = val;
		if (ly[u]) lm[u] = rm[u] = mm[u] = 0;
		else lm[u] = rm[u] = mm[u] = dr[u] - dl[u] + 1;
		return;
	}
	Down(u);
	int mid = (dl[u] + dr[u]) >> 1;
	if (y <= mid) Update(u << 1, x, y, val);
	else if (x > mid) Update(u << 1 | 1, x, y, val);
	else {
		Update(u << 1, x, mid, val);
		Update(u << 1 | 1, mid + 1, y, val);
	}
	Up(u);
}

int main() {
	int n, m, op, x, d;
	while (scanf("%d%d", &n, &m) == 2) {
		build(1,1,n);
		while (m--) {
			scanf("%d%d", &op, &x);
			if (op > 1) {
				scanf("%d", &d);
				Update(1, x, x + d - 1, 0);
			} else {
				d = 0;
				if (mm[1] < x) puts("0");
				else printf("%d\n", d = query(1, x));
				if (d) Update(1, d, d + x - 1, 1);
			}
		}
	}
	return 0;
}
