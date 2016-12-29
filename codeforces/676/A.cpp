#include <cstdio>

inline int max(int a, int b) {
	return a<b?b:a;
}

int main() {
	int n, maxp, minp, a;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a);
		if (a == 1) minp = i;
		if (a == n) maxp = i;
	}
	a = max(max(minp-1,n-minp), max(maxp-1,n-maxp));
	printf("%d", a);
	return 0;
}
