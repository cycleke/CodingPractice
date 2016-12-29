#include <cstdio>

int m, k, d[1010], s[1010];

int main() {
	scanf("%d%d",&m,&k);
	for (int i = 1; i <= m; ++i) scanf("%d", d + i);
	for (int i = 1; i <= m; ++i) scanf("%d", s + i);
	int t = 0, sumd = 0, sums = 0, maxs = 0, _t = 0;
	for (int i = 1; i <= m; ++i) {
		sumd += d[i], sums += s[i];
		t += d[i];
		if (s[i] > maxs) maxs = s[i];
		while (sumd > sums) {
			sums += maxs; ++_t;
		}
	}
	printf("%d\n", t + _t * k);
	return 0;
}
