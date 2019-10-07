// by OwenCreeper
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll a[4];
ll F(ll x) {
	ll b[3], res = a[3] - x, delta;
	// printf("x = %lld\n", x);
	for (int i = 0; i < 3; i++) b[i] = a[i];
	delta = min(b[1] - b[0], x);
	b[0] += delta, x -= delta;
	delta = min(b[2] - b[0], x / 2);
	b[0] += delta, x -= delta;
	delta = min(b[2] - b[1], x);
	b[1] += delta, x -= delta;
	b[0] += x / 3, x -= x /3, b[1] += x / 2, x -= x / 2, b[2] += x, x = 0;
	// printf("%lld %lld %lld\n", b[0], b[1], b[2]);
	return b[0] * 7 + b[0] * b[0] + b[1] * b[1] + (b[2] + res) * (b[2] + res);
}
void work() {
	for (int i = 0; i < 4; i++) scanf("%lld", a + i);
	sort(a, a + 3);
	ll l = 0, r = a[3]; 
	// for (int i = 0; i <= r; i++) printf("%lld ", F(i)); puts("");
	ll ans = max(F(l), F(r));
	while (l < r - 5) {
		ll mid = l + r >> 1, mr = r + mid >> 1;
		if (F(mid) > F(mr))
			r = mr;
		else
			l = mid;
	}
	for (int i = l; i <= r; i++)
		ans = max(ans, F(i));
	printf("%lld\n", ans);
}
int main(int argc, char const *argv[]) {
	int n;
	scanf("%d", &n);
	while (n--) work();
	return 0;
}
