#include <cstdio>

typedef unsigned int ui;
ui sg[23], vis[1003], _vis, p[23], ans, cnt;

int main() {
	int o_o, n;
	scanf("%d", &o_o);
	while (o_o--) {
		scanf("%d", &n);
		for (register int i = 0; i < n; ++i)
			scanf("%d", p + i);
		cnt = ans = sg[n - 1] = 0U;
		for (register int i = n - 2; ~i; --i) {
			++_vis;
			for (register int j = i + 1; j < n; ++j)
				for (register int k = j; k < n; ++k)
					vis[sg[j] ^ sg[k]] = _vis;
			for (ui &x = sg[i] = 0; ; ++x)
				if (vis[x] ^ _vis) break;
			printf("%d\n", sg[i]);
			if (p[i] & 1) ans ^= sg[i];
		}
		for (register int i = 0; i < n; ++i)
			for (register int j = i + 1; j < n; ++j)
				for (register int k = j; k < n; ++k)
					if (ans ^ sg[i] ^ sg[j] ^ sg[k]);
					else {
						if (++cnt <= 1) printf("%d %d %d\n", i, j, k);
					}
		if (!cnt) puts("-1 -1 -1");
		printf("%u\n", cnt);
	}
	return 0;
}
