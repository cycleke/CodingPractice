#include <cstdio>
#include <cstring>
const int N = 5e4 + 10;
int s[N], mu[N], prime[N], cnp;
void init() {
	memset(s, 1, sizeof s);
	mu[1] = 1;
	int i, j, cnp = 0;
	long long t;
	for (i = 2; i < N; ++i) {
		if (s[i]) mu[i] = -1, prime[cnp++] = i;
		for (j = 0; j < cnp; ++j) {
			t = i * prime[j];
			if (t > N) break;
			s[t] = 0;
			if (i % prime[j]) mu[t] = -mu[i];
			else mu[t] = 0, j = cnp;
		}
	}
	s[0] = 0;
	for (i = 1; i < N; ++i) s[i] = s[i-1] + mu[i];
}
int min(const int &a, const int &b) {
	return a < b ? a : b;
}
long long cal(int n, int m) {
	if (n > m) n ^= m ^= n ^= m;
	static long long r;
	static int i, j;
	for (r = 0, i = 1; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		r += (long long)(s[j] - s[i - 1]) * (n / i) * (m / i);
	}
	return r;
}
int main() {
	init();
	int a, b, c, d, k, __;
	scanf("%d", &__);
	while (__--) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		a = (a - 1) / k;
		b = b / k;
		c = (c - 1) / k;
		d = d / k;
		printf("%lld\n", cal(b, d) + cal(a, c) - cal(a, d) - cal(b, c));
	}
	return 0;
}
