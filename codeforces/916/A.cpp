#include <cstdio>

int main() {
	int x, h, m, ans = 0;
	scanf("%d %d %d", &x, &h, &m);
	while (h % 10 != 7 && m % 10 != 7) {
		++ans;
		m -= x;
		if (m < 0) {
			m += 60;
			--h;
		}
		if (h < 0)
			h += 24;
	}
	printf("%d\n", ans);
	return 0;
}
