#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int Maxn = 100010;
LL Sum[Maxn << 2], Add[Maxn << 2];
int dl[Maxn << 2], dr[Maxn << 2];

void Change(int u, LL val) {
	Add[u] += val; Sum[u] += (dr[u] - dl[u] + 1) * val;
}

void PushDown(int u) {
	if (!Add[u]) return;
	Change(u<<1, Add[u]); Change(u<<1|1, Add[u]);
	Add[u] = 0;
}

void PushUp(int u) {
	Sum[u] = Sum[u<<1] + Sum[u<<1|1];
}

void Update(int u,int x, int y, LL val) {
	if (!(dl[u] ^ x) && !(dr[u] ^ y)) {	Change(u, val);  return; }
	PushDown(u);
	Sum[u] += (y - x + 1) * val;
	int mid = (dl[u] + dr[u]) >> 1;
	if (y <= mid) Update(u<<1, x, y, val);
	else if (x > mid) Update(u<<1|1, x, y, val);
	else {
		Update(u<<1, x, mid, val);
		Update(u<<1|1, mid + 1, y, val);
	}
}

LL Query(int u, int x, int y) {
	if (!(dl[u] ^ x) && !(dr[u] ^ y)) {	return Sum[u]; }
	PushDown(u);
	int mid = (dl[u] + dr[u]) >> 1;
	if (y <= mid) return Query(u<<1, x, y);
	else if (x > mid) return Query(u<<1|1, x, y);
	else return Query(u<<1, x, mid) + Query(u<<1|1, mid + 1, y);
}

void build(int u, int l, int r) {
	dl[u] = l; dr[u] = r; Add[u] = 0;
	if (l ^ r) {
		int mid = (l + r) >> 1;
		build(u<<1, l, mid); build(u<<1|1, mid + 1, r);
		PushUp(u);
	} else {
		scanf("%lld", Sum + u);
	}
}

int main() {
	int n, m, a, b, c; char op[2];
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for (int i = 1; i <= m; ++i) {
		scanf("%s%d%d", op, &a, &b);
		if (a > b) a ^= b ^= a ^= b;
		if (*op == 'Q') printf("%lld\n", Query(1, a, b));
		else {
			scanf("%d", &c);
			Update(1, a, b, c);
		}
	}
	return 0;
}
