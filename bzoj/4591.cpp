#include <cstdio>

#define mod 2333

int C[mod][mod], S[mod][mod];

int Lucas(long long n, long long k) {
	int ret = 1, _n, _k;
	while (n && k) {
		_n = n % mod, _k = k % mod;
		if (_n < _k)
		  return 0;
		ret = ret * C[_n][_k] % mod;
		n /= mod, k /= mod;
	}
	return ret;
}

int Cal(long long n, long long k) {
	if (k < 0)
	  return 0;
	if (k < 1)
	  return 1;
	long long _n = n / mod, _k = k / mod;
	int s1 = Cal(_n, _k - 1);
	int s2 = s1 + Lucas(_n, _k);
	if (s2 >= mod)
	  s2 -= mod;
	return (S[n % mod][k % mod] * s2 % mod + (S[n % mod][mod - 1] - S[n % mod][k % mod] + mod) * s1 % mod + mod) % mod;
}

int main() {
	unsigned int _;
	long long k, n;
	C[0][0] = 1;
	for (int i = 1; i < mod; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
		  for (C[i][j] = C[i - 1][j] + C[i - 1][j - 1]; C[i][j] >= mod; C[i][j] -= mod);
	}

	for (int i = 0; i < mod; ++i) {
		S[i][0] = 1;
		for (int j = 1; j < mod; ++j)
		  for (S[i][j] = S[i][j - 1] + C[i][j]; S[i][j] >= mod; S[i][j] -= mod);
	}

	scanf("%u", &_);
	while (_--) {
		scanf("%lld%lld", &n, &k);
		printf("%d\n", Cal(n, k));
	}
	return 0;
}
