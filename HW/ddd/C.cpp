#include <bits/stdc++.h>
using namespace std;

const int Maxn = 5e5 + 10;
int n, k, w[Maxn];
typedef long long LL;
LL PreS[Maxn];

bool is_min(const int& v) {
	int p = lower_bound(w + 1, w + n + 1, v) - w - 1;
	return (LL)p * v - PreS[p] <= k;
}

bool is_max(const int& v) {
	int p = upper_bound(w + 1, w + n + 1, v) - w;
	return PreS[n] - PreS[p - 1] - (LL)(n - p + 1) * v <= k;
}

int main() {
	LL sum = 0; int ave;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", w + i);
	
	sort(w + 1, w + n + 1);
	
	for (int i = 1; i <= n; ++i) PreS[i] = (sum += w[i]);
	ave = sum / n;
	
	int l, r, imin, imax, mid;
	
	l = w[1], r = ave;
	while (l <= r) {
		mid = ((LL)l + r) >> 1;
		if (is_min(mid)) {
			imin = mid; l = mid + 1;
		} else r = mid - 1;
	}
	
	l = ave + (sum % n != 0), r = w[n];
	while (l <= r) {
		mid = ((LL)l + r) >> 1;
		if (is_max(mid)) {
			imax = mid; r = mid - 1;
		} else l = mid + 1;
	}
	
	printf("%d" ,imax - imin);
	
	return 0;
}
