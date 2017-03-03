#include <cstdio>
int a[10005], b[10005], n;
#define rit register int
inline int g(int x, int y) {
	b[1] = x, b[2] = y;
	for (rit i = 2; i < n; ++i) {
		b[i + 1] = a[i] - b[i] - b[i - 1];
		if (b[i + 1] >> 1) return 0;
	}
	return b[n] + b[n - 1] == a[n];
}
int main() {
	scanf("%d", &n);
	for (rit i = 1; i <= n; ++i)
	  scanf("%d", a + i);
	if (!a[1]) printf("%d\n", g(0, 0));
	else if (a[1] < 2) printf("%d\n", g(1, 0) + g(0, 1));
	else printf("%d\n", g(1, 1));
	return 0;
}
