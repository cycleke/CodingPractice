#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MILLER_RABIN_TIMES 20

int Count(int s) {
	int c = 0;
	while (s) {
		c++;
		s &= s - 1;
	}
	return c;
}

int ModPow(int a, int b, int p) {
	a %= p;
	int ret = 1;
	while (b) {
		if (b & 1) ret = 1ll * ret * a % p;
		a = 1ll * a * a % p;
    b >>= 1;
	}
	return ret;
}

bool Check(int a, int n, int x, int t) {
	int ret = ModPow(a, x, n);
	int last = ret;
	for (int i = 1; i <= t; i++) {
		ret = 1ll * ret * ret % n;
		if (ret == 1 && last != 1 && last != n - 1) return true;
		last = ret;
	}
	if (ret != 1) return true;
	return false;
}

bool Miller_Rabin(int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if ((n & 1) == 0) return false;
	int x = n - 1, t = 0;
	while ((x & 1) == 0) {
		x >>= 1;
		t++;
	}
	for (int i = 0; i < MILLER_RABIN_TIMES; i++) {
		int a = rand() % (n - 1) + 1;
		if (Check(a, n, x, t)) return false;
	}
	return true;
}

int main() {
	int n, k;
	int x[20];
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", x + i);
	}
	int ans = 0;
	int all = 1 << n;
	for (int s = 0; s < all; s++) {
		if (Count(s) != k) continue;
		int sum = 0;
		for (int i = 0; i < n; i++) {
			if (s >> i & 1) sum += x[i];
		}
		if (Miller_Rabin(sum)) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
