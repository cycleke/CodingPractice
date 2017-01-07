#include <cstdio>
#include <algorithm>
int weight[10005],n,m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", weight + i);
		weight[i] <<= 1;
	}
	while (m--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		weight[a] += c;
		weight[b] += c;
	}
	std::sort(weight + 1, weight + n + 1);
	long long maxdelta = 0LL;
	for (int i = 1; i <= n; i += 2)
		maxdelta += weight[i+1] - weight[i];
	maxdelta >>= 1;
	printf("%lld", maxdelta);
	return 0;
}
