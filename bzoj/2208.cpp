#include <cstdio>

struct edge {
	int to;
	edge *nxt;
} edge_mset[2000 * 2000 + 3], *g[2002], *cedge = edge_mset;

int main() {

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		static char s[2002];
		scanf("%s", s);
		for (int j = 0; j < n; ++j)
			if (s[j] == '1') {
				*cedge = (edge) {j, g[i]};
				g[i] = cedge++;
			}
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		static int q[2002], *l, *r, v[2002], _v = 0, u;
		v[i] = ++_v;
		l = r = q;
		*r++ = i;
		while (l < r) {
			u = *l++;
			++ans;
			for (edge *it = g[u]; it; it = it->nxt)
				if (v[it->to] ^ _v) v[*r++ = it->to] = _v;
		}
		//printf("%d\n", ans);
	}

	printf("%d\n", ans);

	return 0;
}
