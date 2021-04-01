#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 5e4 + 10;
int mu[N], s[N], prime[N];

void init() {
	memset(s, 1, sizeof s);
	mu[1] = 1; int i, j, totp = 0; long long t;
	for (i = 2; i < N; ++i) {
		if (s[i]) mu[i] = -1, prime[totp++] = i;
		for (j = 0; j < totp; ++j) {
			t = (long long)i * prime[j];
			if (t > N) break;
			s[t] = 0;
			if (i % prime[j]) mu[t] = -mu[i];
			else mu[t] = 0, j = totp;
		}
	}
	s[0] = 0;
	for (i = 1; i < N; ++i) s[i] = s[i - 1] + mu[i];
}

long long Cal(int n, int m) {
	if (n > m) swap(n, m);
	long long ret = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		ret += (long long)(s[j] - s[i - 1]) * (n / i) * (m / i);
	}
	return ret;
}

int main() {
	init();
	int a, b, c, d, k, T;
	long long t;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		--a, --c; a /= k; b /= k; c /= k; d /= k;
		t = Cal(b, d) + Cal(a, c);
		t -= Cal(a, d) + Cal(b, c);
		printf("%lld\n", t);
	}
	return 0;
}
