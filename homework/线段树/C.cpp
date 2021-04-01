#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int pre, C[200010 << 2];

int query(const int &val) {
	if (C[1] < val) return -1;
	int u = 1, p;
	while (u <= pre) {
		if (C[u<<1] >= val) u = u << 1;
		else u = u << 1 | 1;
	}
	p = u - pre;
	C[u] -= val; u >>= 1;
	while (u) {
		C[u] = max(C[u<<1], C[u<<1|1]);
		u >>= 1;
	}
	return p;
}

int main() {
	int n, w ,h, t;
	while (scanf("%d%d%d", &h, &w, &n) ^ EOF) {
		memset(C, 0, sizeof C);
		t = min(n, h);
		for (pre = 1; pre < t; pre <<= 1); --pre;
		for (int i = 1; i <= t; ++i) C[i + pre] = w;
		for (int i = pre; i; --i) C[i] = max(C[i<<1], C[i<<1|1]);
		while (n--) {
			scanf("%d", &h);
			printf("%d\n", query(h));
		}
	}
	return 0;
}
