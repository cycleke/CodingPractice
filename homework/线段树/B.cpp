#include <cstdio>
#include <cstring>
#include <iostream>

int C[5010], a[5010];

void Add(int u) {
	while (u < 5010) {
		++C[u];
		u += u & -u;
	}
}

int Sum(int u) {
	int sum = 0;
	while (u) {
		sum += C[u];
		u -= u & -u;
	}
	return sum;
}

int main() {
	int n, S, ans;
	while (scanf("%d", &n) ^ EOF) {
		memset(C, 0, sizeof C);
		S = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			Add(a[i] + 1);
			S += i - Sum(a[i] + 1);
		}
		ans = S;
		for (int i = 1; i <= n; ++i) {
			S += n - (a[i] << 1) - 1;
			ans = std::min(ans, S);
		}
		printf("%d\n", ans);
	}
}
