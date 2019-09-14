// by OwenCreeper
#include "bits/stdc++.h"
#define N 1000000
#define MOD 1000000007
using namespace std;
typedef long long ll;
inline int read() {
	int num = 0, k = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') k = ch == '-' ? -1 : 1, ch = getchar();
	while (ch >= '0' && ch <= '9') num *= 10, num += ch - 48, ch = getchar();
	return num * k;
}
ll fpow(int a, int n) {
	ll ans = 1, tmp = a;
	while (n) {
		if (n & 1) ans = ans * tmp % MOD;
		tmp = tmp * tmp % MOD, n >>= 1;
	}
	return ans;
}
int fac[N + 5], inv[N + 5];
void prework() {
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * 1ll * i % MOD;
	inv[N] = fpow(fac[N], MOD - 2);
	for (int i = N; i; i--) inv[i - 1] = inv[i] * 1ll * i % MOD;
}
ll C(int n, int m) { return fac[n] * 1ll * inv[m] % MOD * inv[n - m] % MOD; }
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	prework();
	while (T--) {
		int n, x;
		scanf("%d%d", &n, &x);
		int ans = fac[n];
		for (int i = x + 1; i <= n; i++)
			ans -= C(n, i) * fac[i - 1] % MOD * fac[n - i] % MOD, ans %= MOD;
		if (ans < 0) ans += MOD;
		ans = ans * 1ll * inv[n] % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
