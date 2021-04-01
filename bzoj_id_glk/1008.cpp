#include <cstdio>

#define Mod 100003LL
long long ret, n, m, ans;
long long Mod_Pow(long long b, long long n) {
	ret = 1;
	while (n) {
		if (n & 1) ret = ret * b % Mod;
		b = b * b % Mod;
		n >>= 1;
	}
	return ret;
}

int main() {
	scanf("%lld%lld", &m, &n);
	m %= Mod;
	ans = Mod_Pow(m, n);
	ans -= m * Mod_Pow(m - 1, n - 1);
	ans = (ans % Mod + Mod) % Mod;
	printf("%lld\n", ans);
	return 0;
}
