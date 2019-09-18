// by OwenCreeper
#include "bits/stdc++.h"
using namespace std;
int Case = 0;
void work() {
	int a, b, c, d, f, n;
	scanf("%d%d%d%d%d", &a, &b, &c, &d, &f);
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		if (x <= 48) ans += a; else 
		if (x <= 56) ans += b; else 
		if (x <= 60) ans += c; else 
		if (x <= 62) ans += d; else 
		ans += f;
	}
	ans *= 10000;
	Case++;
	printf("Case #%d: %lld\n", Case, ans);
}
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) work();
	return 0;
}
