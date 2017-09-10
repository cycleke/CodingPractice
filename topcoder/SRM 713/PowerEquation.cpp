typedef long long i64;

inline int gcd(int a, int b) {
	for (static int t; b; t = a % b, a = b, b = t);
	return a;
}

inline int max(const int &a, const int &b) {
	return a < b ? b : a;
}

class PowerEquation {
	public:
		int count(int n) {
			const int mod(1e9 + 7);
			int ans = (2 * n - 1ll) * n % mod;
			for (int base = 2; base * base <= n; ++base) {
				i64 a = base, c;
				int b = 1, d;
				while (a <= n) {
					c = base, d = 1;
					while (c <= n) {
						if (gcd(b, d) == 1 && b != d)
						  ans = (ans + n / max(b, d)) % mod;
						c *= base, ++d;
					}
					a *= base, ++b;
				}
			}
			return ans;
		}
};

// BEGIN CUT HERE

#include <cstdio>

int main() {

	int ans = PowerEquation().count(100);

	printf("%d\n", ans);

	return 0;
}

// END CUT HERE
