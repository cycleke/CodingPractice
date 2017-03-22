#include <cmath>
#include <cstdio>

int r;
double _r;

inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

inline int calc(int n, int a, int b, int c) {
	//// \sum_{i=1}^{n} \lfloor{{b * i + c} \over a}
	if (!n) return 0;
	int g = gcd(a, gcd(b, c));
	a /= g, b /= g, c /= g;
	long long m = ((long long)b * _r + c) / a;
	long long sum = n * (n + 1LL) / 2 * m;
	c -= m * a;
	m = ((long long)b * _r + c) / a * n;
	sum += n * m;
	return sum - calc(m, b * b * r - c * c, a * b, -a * c);
}

int main() {
	int o_o, n, t;
	scanf("%d", &o_o);
	while (o_o--) {
		scanf("%d%d", &n, &r);
		_r = sqrt(r);
		t = int(_r);
		if (t * t == r)
			printf("%d\n", t & 1 ? (n & 1 ? -1 : 0) : n);
		else
			printf("%d\n", n - ((calc(n, 1, 1, 0) - (calc(n, 2, 1, 0) << 1)) << 1));
	}
	return 0;
}
