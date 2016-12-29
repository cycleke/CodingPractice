#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define ls u<<1
#define rs u<<1|1
#define clr(a,b) memset(a, b, sizeof (a))
using namespace std;
const int Maxn = 100010;

struct Que {
	int l, r, id;
	Que(int a = 0, int b = 0, int c = 0) : l(a), r(b), id(c) {}
	bool operator < (const Que &A) const { return r < A.r; }
	void Read(const int &a) {
		scanf("%d%d", &l, &r); id = a;
	}
}Op[Maxn];

int old_cover[Maxn << 2], now_cover[Maxn << 2], old_max[Maxn << 2], now_max[Maxn << 2], dl[Maxn << 2], dr[Maxn << 2];
int pos[(Maxn << 1) + 5], ans[Maxn];

void Up(const int &u) {
	now_max[u] = max(now_max[ls], now_max[rs]);
	old_max[u] = max(old_max[ls], old_max[rs]);
}

void SelfMax(int &a, const int &b) {
	if (a < b) a = b;
}

void Down(const int &u) {
	SelfMax(old_cover[ls], now_cover[ls] + old_cover[u]);
	SelfMax(old_cover[rs], now_cover[rs] + old_cover[u]);
	SelfMax(old_max[ls], now_max[ls] + old_cover[u]);
	SelfMax(old_max[rs], now_max[rs] + old_cover[u]);
	now_cover[ls] += now_cover[u]; now_cover[rs] += now_cover[u];
	now_max[ls] += now_cover[u]; now_max[rs] += now_cover[u];
	old_cover[u] = now_cover[u] = 0;
}

void Build(int u, int l, int r) {
	dl[u] = l; dr[u] = r;
	old_cover[u] = old_max[u] = now_cover[u] = now_max[u] = 0;
	if (l ^ r) {
		int mid = (l + r) >> 1;
		Build(ls, l, mid); Build(rs, mid + 1, r);
	}
}

void Update(int u, int x, int y, const int &val) {
	if (!(dl[u] ^ x) && !(dr[u] ^ y)) {
		SelfMax(old_max[u], now_max[u] += val);
		SelfMax(old_cover[u], now_cover[u] += val);
		return;
	}
	Down(u);
	int mid = (dl[u] + dr[u]) >> 1;
	if (y <= mid) Update(ls, x, y, val);
	else if (x > mid) Update(rs, x, y, val);
	else {
		Update(ls, x, mid, val); Update(rs, mid + 1, y, val);
	}
	Up(u);
}

int Query(int u, int x, int y) {
	if (!(dl[u] ^ x) && !(dr[u] ^ y)) 
		return old_max[u];
	Down(u);
	int mid = (dl[u] + dr[u]) >> 1;
	if (y <= mid) return Query(ls, x, y);
	else if (x > mid) return Query(rs, x, y);
	else return max(Query(ls, x, mid), Query(rs, mid + 1, y));
}

int a[Maxn];
int main() {
	int n, q;
	while (scanf("%d", &n) ^ EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		clr(pos, 0);
		Build(1, 1, n);
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) Op[i].Read(i);
		sort(Op, Op + q);
		for (int i = 1, j = 0; i <= n && j < q; ++i) {
			Update(1, pos[a[i] + Maxn] + 1, i, a[i]);
			pos[a[i] + Maxn] = i;
			while (j < q && Op[j].r == i) {
				ans[Op[j].id] = Query(1, Op[j].l, Op[j].r);
				++j;
			}
		}
		for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
