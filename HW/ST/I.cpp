#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int Maxn = 110;
struct Acc {
	double x, y1, y2;
	int v;
	Acc (double a = 0, double b = 0, double c = 0, int d = 0) {
		x = a; y1 = b; y2 = c; v = d;
	}
	bool operator < (const Acc &A) const {
		if (x != A.x) return x < A.x;
		return v > A.v;
	}
}Eve[Maxn << 1];
double Y[Maxn << 1], C[Maxn << 3];
int Has[Maxn << 3], n, len, dl[Maxn << 3], dr[Maxn << 3];

int find(const double &x) {
	int l = 0, r = len, mid, pos;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (Y[mid] <= x) {
			l = mid + 1; pos = mid;
		} else r = mid - 1;
	}
	return pos;
}

void Cal(const int &u) {
	if (Has[u])
		C[u] = Y[dr[u] + 1] - Y[dl[u]];
	else if (dr[u] == dl[u])
		C[u] = 0;
	else if (dl[u] ^ dr[u])
		C[u] = C[u<<1] + C[u<<1|1];
}

void Update(int u, int x, int y, const int &val) {
	if (dl[u] == x && dr[u] == y) {
		Has[u] += val; 
		Cal(u); return;
	}
	int mid = (dl[u] + dr[u]) >> 1;
	if (y <= mid) Update(u<<1, x, y, val);
	else if (x > mid) Update(u<<1|1, x, y, val);
	else {
		Update(u<<1, x, mid, val);
		Update(u<<1|1, mid + 1, y, val);
	}
	Cal(u);
}

void Build(int u, int l, int r) {
	dl[u] = l; dr[u] = r; C[u] = Has[u] = 0;
	if (l ^ r) {
		int mid = (l + r) >> 1;
		Build(u<<1, l, mid);
		Build(u<<1|1, mid + 1, r);
	}
}

int main() {
	double x1, x2, y1, y2, *end, ans;
	int Case = 0, p1, p2, cnt;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = cnt = 0; i < n; ++i) {
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			Eve[cnt] = Acc(x1, y1, y2, 1);
			Eve[cnt+1] = Acc(x2, y1, y2, -1);
			Y[cnt++] = y1; Y[cnt++] = y2;
		}
		sort(Y, Y + cnt);
		sort(Eve, Eve + cnt);
		end = unique(Y, Y + cnt);
		len = end - Y - 1; ans = 0;
		Build(1, 0, len);
		for (int i = 0; i < (n << 1); ++i) {
			p1 = find(Eve[i].y1), p2 = find(Eve[i].y2) - 1;
			Update(1, p1, p2, Eve[i].v);
			ans += C[1] * (Eve[i+1].x - Eve[i].x);
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++Case, ans);
	}
	return 0;
}
