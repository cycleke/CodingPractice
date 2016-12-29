#include <cstdio>

int Cnt[110];

int main() {
	int n, m, mv, t, a;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		mv = 0; t = 0;
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &a);
			if (a > mv) mv = a, t = j;
		}
		++Cnt[t];
	}
	mv = 0;
	for (int i = 1; i <= n; ++i)
	  if (Cnt[i] > mv) mv = Cnt[i], t = i;
	printf("%d\n", t);
	return 0;
}
