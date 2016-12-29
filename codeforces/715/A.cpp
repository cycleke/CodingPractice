#include <cstdio>

int main() {
	int n;
	scanf("%d", &n);
	puts("2");
	for (int i = 2; i <= n; ++i) 
	  printf("%I64d\n", i * (i + 1LL) * (i + 1LL) - i + 1LL);
	return 0;
}
