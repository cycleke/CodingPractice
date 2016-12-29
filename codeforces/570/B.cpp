#include <cstdio>

int main() {
	
	int n, m, a;
	scanf("%d%d", &n, &m);
	if (n == 1) return puts("1"), 0;
	if (m - 1 >= n - m) a = m - 1;
	else a = m + 1;
	printf("%d\n", a);
	return 0;
}
