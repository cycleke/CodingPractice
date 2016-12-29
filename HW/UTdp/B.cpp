#include <bits/stdc++.h>
using namespace std;

const int Maxn = 500010, INF = ~0U>>1;

long long front[Maxn], back[Maxn];
int a[Maxn];

int main() {
	int n, i; long long ans, sum, maxx;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) scanf("%d", a + i);
	sum = 0LL; maxx = a[1];
	for (i = 1; i <= n; ++i) {
		if (sum < 0LL) sum = 0; sum += a[i];
		if (sum > maxx) maxx = sum;
		front[i] = maxx;
	}
	sum = 0LL; maxx = a[n];
	for (i = n; i; --i) {
		if (sum < 0LL) sum = 0; sum += a[i];
		if (sum > maxx) maxx = sum;
		back[i] = maxx;
	}
	ans = -INF;
	for (i = 2; i < n; ++i) ans = max(ans, front[i - 1] + back[i + 1]);
	printf("%lld", ans);
	return 0;
}

