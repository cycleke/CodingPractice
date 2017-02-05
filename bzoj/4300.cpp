#include <cstdio>
int mx[31];
int main() {
	int n, i, x, t;
	for (scanf("%d", &n); n; --n) {
		scanf("%d", &x);
		for (i = t = 0; i ^ 31; ++i)
			if ((x >> i & 1) && mx[i] > t) t = mx[i];
		for (i = 0, ++t; i ^ 31; ++i)
			if ((x >> i & 1) && mx[i] < t) mx[i] = t;
	}
	for (i = t = 0; i ^ 31; ++i)
		if (mx[i] > t) t = mx[i];
	printf("%d\n", t);
	return 0;
}
