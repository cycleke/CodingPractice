#include <bits/stdc++.h>
using namespace std;

int f[10010];

int main() {
	int n, m, t, v, i;
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &t, &v);
		for (i = n; i >= t; --i)
			f[i] = max(f[i], f[i - t] + v);
	}
	printf("%d", f[n]);
	return 0;
}
