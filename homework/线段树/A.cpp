#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MS = 200010 << 2;

int C[MS], pre;

void update(int a, const int &b) {
	for (C[a += pre] = b, a >>=1; a; a >>= 1)
	C[a] = max(C[a<<1], C[a<<1|1]);
}

int query(int s, int t) {
	int ans = -1;
	for (s += pre - 1, t += pre + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
		if (~s & 1) ans = max(ans, C[s ^ 1]);
		if (t & 1) ans = max(ans, C[t ^ 1]);
	}
	return ans;
}

int main() {
	int n, m, a, b; char op[2];
	while (scanf("%d%d", &n, &m) ^ EOF) {
		memset(C, 0, sizeof C);
		pre = 1;
		while (pre <= n + 1) pre <<= 1;
		for (int i = 1; i <= n; ++i) scanf("%d", C + i + pre);
		for (int u = pre; u; --u)
			C[u] = max(C[u<<1], C[u<<1|1]);
		while (m--) {
			scanf("%s%d%d", op, &a, &b);
			if (*op == 'Q') printf("%d\n", query(a,b));
			else update(a,b);
		}
	}
	return 0;
}
