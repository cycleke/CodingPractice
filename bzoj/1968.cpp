#include <cstdio>
int n, i, j, k, ans;
int main() {
	scanf("%d", &n);
	for (i = 1; i <= n; i = j + 1) {
		k = n / i;
		j = n / k;
		ans += k * (j - i + 1);
	}
	printf("%d\n", ans);
	return 0;
}
