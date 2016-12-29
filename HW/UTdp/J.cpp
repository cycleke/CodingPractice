#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1000010;
int d[Maxn];
map<int, int>pos;

int main() {
	int n, m, a, len = 0, p;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a);
		pos[a] = i;
	}
	memset(d, 127, sizeof d);
	map<int, int>::iterator it;
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &a);
		it = pos.find(a);
		if (it == pos.end()) continue;
		p = lower_bound(d + 1,d + m + 1, it->second) - d;
		d[p] = it->second;
		if (p > len) len = p;
	}
	printf("%d", len + 1);
	return 0;
}
