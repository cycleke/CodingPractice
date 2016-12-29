#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100010;
int x[Maxn], y[Maxn], v[Maxn], Hax[Maxn], pre;
long long C[Maxn << 2], dp[Maxn];

void SelfMax(long long &a, const long long &b) { if (a < b) a = b; }

long long query(int l, int r) {
	long long ans = -1;
	for (l += pre - 1, r += pre + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) SelfMax(ans, C[l ^ 1]);
		if (r & 1) SelfMax(ans, C[r ^ 1]);
	}
	return ans;
}

void update(int p, const long long &val) {
	for (C[p += pre] = val, p >>= 1; p; p >>= 1)
		C[p] = max(C[p<<1], C[p<<1|1]);
}

int main() {
	int N, l, r, *end, len;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) scanf("%d%d%d", x + i, v + i, y + i), Hax[i] = x[i];
	sort(Hax + 1, Hax + N + 1); pre = 1;
	end = unique(Hax + 1, Hax + N + 1); len = end - Hax - 1;
	while (pre <= len + 1) pre <<= 1; memset(C, 0, sizeof C);
	for (int i = 1; i <= N; ++i) {
		l = lower_bound(Hax + 1, end, x[i] - y[i]) - Hax;
		r = lower_bound(Hax + 1, end, x[i]) - Hax;
		dp[i] = query(l, r) + v[i];
		update(r, dp[i]);
	}
	cout << query(1, len) << endl;
	return 0;
}
