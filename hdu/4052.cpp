#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 100005

struct Line {
	int lx, rx, h, flag;
	Line(int lx, int rx, int h, int flag) :
		lx(lx), rx(rx), h(h), flag(flag) {}
	bool operator < (const Line &a) const {
		return h < a.h;
	}
};

struct Point {
	int x1, y1, x2, y2;
} p[N];

struct segment {
	int l, r, flag;
	long long sum;
}C[N << 2];

int n;
long long ans;
vector<int> a;
vector<Line> line;

int idx(const int &x) {
	return lower_bound(a.begin(), a.end(), x) - a.begin();
}

#define ls u << 1
#define rs u << 1 | 1
void pu(int u) {
	if (C[u].flag)
		C[u].sum = a[C[u].r] - a[C[u].l];
	else if (C[u].l + 1 == C[u].r)
		C[u].sum = 0;
	else
		C[u].sum = C[ls].sum + C[rs].sum;
}

void build(int u, int l, int r) {
	C[u] = (segment){l, r, 0, 0LL};
	if (l + 1 == r)
		return;
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid, r);
}

void upd(int u, const int &x, const int &y, const int &v) {
	if (x <= C[u].l && C[u].r <= y) {
		C[u].flag += v;
		pu(u);
		return;
	}
	int mid = (C[u].l + C[u].r) >> 1;
	if (x < mid) upd(ls, x, y, v);
	if (mid < y) upd(rs, x, y, v);
	pu(u);
}

void solve(bool flag, int w, int h, int m) {
	a.clear(), line.clear();
	a.push_back(1);
	a.push_back(w + 1);
	int tmp = max(h - m + 2, 1);
	line.push_back(Line(1, w + 1, tmp, 1));
	line.push_back(Line(1, w + 1, h + 1, -1));
	for (int i = 1; i <= n; ++i) {
		if (!flag) {
			scanf("%d%d%d%d", &p[i].x1, &p[i].y1, &p[i].x2, &p[i].y2);
			++p[i].x2, ++p[i].y2;
		} else {
			swap(p[i].x1, p[i].y1);
			swap(p[i].x2, p[i].y2);
		}
		tmp = max(p[i].y1 - m + 1, 1);
		line.push_back(Line(p[i].x1, p[i].x2, tmp, 1));
		line.push_back(Line(p[i].x1, p[i].x2, p[i].y2, -1));
		a.push_back(p[i].x1);
		a.push_back(p[i].x2);
	}
	sort(a.begin(), a.end());
	sort(line.begin(), line.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	int sza = a.size(), szline = line.size();
	build(1, 0, sza);
	for (int i = 0; i < szline; ++i) {
		if (i)
			ans -= C[1].sum * (long long)(line[i].h - line[i - 1].h);
		upd(1, idx(line[i].lx), idx(line[i].rx), line[i].flag);
	}
}

int main() {
	int w, h, m;
	while (scanf("%d%d%d%d", &w, &h, &n, &m) == 4) {
		ans = 2LL * w * h;
		solve(false, w, h, m);
		solve(true, h, w, m);
		if (m == 1)
			ans >>= 1;
		printf("%lld\n", ans);
	}
	return 0;
}
