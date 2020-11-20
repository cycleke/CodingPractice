#include <cstdio>

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	const int p = 1e5 + 3;
	puts("100003 100003");
	printf("1 2 %d\n", p - n + 2);
	for (int i = 2; i < n; ++i)
		printf("%d %d 1\n", i, i + 1);
	m -= n - 1;
	for (int i = 0, j = n; m--;) {
		if (++j > n) j = ++i + 2;
		printf("%d %d 99990999\n", i, j);
	}
	return 0;
}
