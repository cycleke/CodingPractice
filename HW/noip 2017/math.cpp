#include <cstdio>

int main() {
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%lld\n", (a - 1ll) * (b - 1ll) - 1ll);
	return 0;
}
