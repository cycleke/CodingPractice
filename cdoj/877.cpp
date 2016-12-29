#include <cstdio>
#include <algorithm>

#define N 1005
#define cmax(a,b) (a<(__t=b)?a=__t:1)
int C[N][N], h[N], r[N], ret, __t;

bool cmp(const int &a, const int &b) { return h[a]<h[b]; }
inline int Query(int *tr, int x) {
	for (ret = 0; 0 < x; x -= x & -x)
	  cmax(ret, tr[x]);
	return ret;
}
inline void Update(int *tr, int x, const int &val) {
	for (; x < N; x += x & -x)
	  cmax(tr[x], val);
}

int main() {
	int n, id, pre; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", h + i), r[i] = i;
	std::sort(r + 1, r + n + 1, cmp);
	pre = h[r[1]]; h[r[1]] = id = 1;
	for (int i = 2; i <= n; ++i) {
		if (h[r[i]] ^ pre) pre = h[r[i]], ++id;
		h[r[i]] = id;
	}
	for (int i = 1, j, t = h[1]; i <= n; t = h[++i]) {
		for (j = 1; j <= id; ++j)
		  r[j] = Query(C[j], t) + 1;
		for (j = 1; j <= id; ++j) {
			Update(C[j], t, r[j]);
			Update(C[t], j, r[j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= id; ++i) cmax(ans, Query(C[i], id));
	printf("%d\n", ans);
	return 0;
}
