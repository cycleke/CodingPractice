#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1e5 + 10;
int N, K, a[Maxn], b[Maxn];
typedef long long LL;

bool check(const int &v) {
	int k = K; LL tmp;
	for (int i = 1; i <= N; ++i) {
		tmp = (LL)v * a[i] - b[i];
		if (tmp <= 0) continue;
		if (tmp > k) return false;
		k -= tmp;
	}
	return true;
}

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) scanf("%d", a + i);
	for (int i = 1; i <= N; ++i) scanf("%d", b + i);
	
	int l = 0, r = ~0U>>1, mid, ans = 0;
	while (l <= r) {
		mid = ((LL)l + r) >> 1;
		
		if (check(mid)) {
			ans = mid, l = mid + 1;
		} else r = mid - 1;
	}
	printf("%d", ans);
	return 0;
}
