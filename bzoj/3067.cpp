#include <cstdio>
#include <cstring>
#define N 300005
#define mo ((1<<22)-1)
//#define tail ((1LL<<52)-1LL)
struct edge {long long hashvalue; int key; edge *n;} me[N], *g[mo], *ce;

inline void add(const long long &status) {
	static edge *it;
	for (it = g[status & mo]; it; it = it->n)
		if (!(status ^ it->hashvalue)) return (void)(++it->key);
	ce->hashvalue = status;
	ce->key = 1;
	ce->n = g[status & mo];
	g[status & mo] = ce++;
}

inline int query(const long long &status) {
	static edge *it;
	for (it = g[status & mo]; it; it = it->n)
		if (!(status ^ it->hashvalue)) return it->key;
	return 0;
}

char ts[N];

int main() {
	int i;
	char *s;
	long long ans, x, y;
	while (scanf("%d%s", &i, ts) != EOF) {
		ans = 0LL;
		memset(g, 0, sizeof g);
		ce = me;
		add(x = y = 0LL);
		for (s = ts; *s; ++s, add(y = x)) {
			ans += query(x = y ^ (1LL << ((*s < 'a') ? (*s - 'A') : (*s - 'a' + 26))));
			for (i = 0; i ^ 52; ++i)
				ans += query(x ^ (1LL << i));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
