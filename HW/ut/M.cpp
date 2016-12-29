#include <cstdio>

int a[23];

int f(int t, int g) {
	if (t <= 0) return 0;
	while (a[t] == g && t) --t;
	if (!t) return 0;
	return f(t - 1, 6 - g - a[t]) + (1 << (t - 1));
}

int main() {
	int M;
	scanf("%d", &M);
	for (int i = 20; i; --i) scanf("%d", a + i);
	if (f(20, 1) <= M || f(20,2) <= M || f(20,3) <= M) puts("YES");
	else puts("NO");
	return 0;
}
