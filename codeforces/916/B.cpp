#include <cstdio>

int main() {
	long long n;
	static int k, b[1000005] = {};
	scanf("%lld %d", &n, &k);
  for (int i = 900000; n != 0; n >>= 1, ++i)
		if ((n & 1) == 1) {
			++b[i];
			k--;
		}
	if (k < 0)
		puts("No");
	else {
		puts("Yes");
		for (int i = 1000000; k >= b[i]; --i) {
			while (b[i] != 0) {
				--b[i];
				b[i - 1] += 2;
				--k;
			}
		}
		int i = 0;
		while (b[i] == 0)
			++i;
		while (k)
			if (b[i] != 0) {
				--b[i];
				b[i - 1] += 2;
				--k;
				--i;
			}
		for (i = 1000000; i >= 0; --i) {
			while (b[i] != 0) {
				printf("%d ", i - 900000);
				--b[i];
			}
		}
	}
	return 0;
}
