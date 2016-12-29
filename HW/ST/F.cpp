#include <cstdio>
#include <cstring>
#include <algorithm>
const int MS = 100010 << 2, Maxn = 100010;
int C[MS], Cnt[Maxn];
bool lazy[MS];
int Num[Maxn << 1], opl[Maxn], opr[Maxn];

void PushDown(int u) {
	if (!lazy[u]) return;
	C[u<<1|1] = C[u<<1] = C[u];
	lazy[u<<1|1] = lazy[u<<1] = true;
	lazy[u] = false;
}

void Up(int u) {
	if (C[u<<1|1] ^ C[u<<1]) C[u] = -1;
	else C[u] = C[u<<1];
}

void Update(int u, int l, int r, int x, int y, int val) {
	if (!(l ^ x) && !(r ^ y)) {
		C[u] = val; lazy[u] = true; return;
	}
	PushDown(u);
	int mid = (l + r) >> 1;
	if (y <= mid) Update(u<<1, l, mid, x, y, val);
	else if (x > mid) Update(u<<1|1, mid + 1, r, x, y, val);
	else {
		Update(u<<1, l, mid, x, mid, val);
		Update(u<<1|1, mid + 1, r, mid + 1, y, val);
	}
	Up(u);
}

void Query(int u, int l, int r) {
	if (~C[u]) {
		++Cnt[C[u]]; return;
	}
	int mid = (l + r) >> 1;
	Query(u<<1, l, mid); Query(u<<1|1, mid + 1, r);
}

int main() {
	using namespace std;
	int T, n, x, y, *end, len, ans;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(C, 0, sizeof C);
		memset(Cnt, 0, sizeof Cnt);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", opl + i, opr + i);
			Num[(i<<1) - 1] = opl[i], Num[i<<1] = opr[i];
		}
		sort(Num + 1, Num + (n << 1) + 1);
		end = unique(Num + 1, Num + (n << 1) + 1);
		len = end - Num - 1;
		for (int i = 1; i <= n; ++i) {
			x = lower_bound(Num + 1, end, opl[i]) - Num;
			y = lower_bound(Num + 1, end, opr[i]) - Num;
			if (x > y) x ^= y ^= x ^= y;
			Update(1, 1, len, x, y, i);
		}
		Query(1, 1, len);
		ans = 0;
		for (int i = 1; i <= n; ++i) ans += (Cnt[i] > 0);
		printf("%d\n", ans);
	}
	return 0;
}
