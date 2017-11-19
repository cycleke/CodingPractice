#include <cstdio>

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%llu", 1ll * (a - 1ull) * (b - 1ull) - 1);
	return 0;
}
