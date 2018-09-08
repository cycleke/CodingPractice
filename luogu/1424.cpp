#include <cstdio>

int main() {
	int x, n;
	scanf("%d%d", &x, &n);
	int weekday = n / 7 * 5;
	int remain = n % 7;
	if (remain > 0) {
		if (remain + x == 7 || x == 7) {
			remain -= 1;
		} else if (remain + x > 7) {
			remain -= 2;
		}
	}
	printf("%lld\n", (weekday + remain) * 250ll);
	return 0;
}
