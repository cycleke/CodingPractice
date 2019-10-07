// by OwenCreeper
#include "bits/stdc++.h"
#define N 1000000
#define MAX 10000000
using namespace std;
typedef long long ll;
int son[N + 5][2], father[N + 5], prime[N + 5], mi[MAX + 5], noprime[MAX + 5],
	l[N + 5], r[N + 5], pcnt = 0, a[N + 5],
	lst[MAX + 5], rst[MAX + 5], n;
void prework() {
	for (int i = 2; i <= MAX; i++) {
		if (!noprime[i]) prime[++pcnt] = i, mi[i] = i, lst[i] = -1, rst[i] = n + 2;
		for (int j = 1; j <= pcnt && prime[j] * 1ll * i <= MAX; j++) {
			noprime[i * prime[j]] = 1;
			mi[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
	// printf("pcnt = %d\n", pcnt);
}
int solve(int ll, int rr) {
	if (ll > rr) return 0;
	if (ll == rr) return ll;
	// printf("solve %d %d\n", ll, rr);
	int pos = 0;
	for (int ml = ll, mr = rr; ml <= mr; ml++, mr--) {
		if (l[ml] <= ll && r[ml] >= rr) {
			pos = ml;
			break;
		}
		if (l[mr] <= ll && r[mr] >= rr) {
			pos = mr;
			break;
		}
	}
	if (!pos) return -1;
	son[pos][0] = solve(ll, pos - 1);
	if (son[pos][0] == -1) return -1;
	father[son[pos][0]] = pos;
	son[pos][1] = solve(pos + 1, rr);
	if (son[pos][1] == -1) return -1;
	father[son[pos][1]] = pos;
	return pos;
}
int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	prework();
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		int x = a[i];
		l[i] = 0;
		while (x ^ 1) {
			int p = mi[x];
			l[i] = max(l[i], lst[p] + 1), lst[p] = i;
			// printf("x = %d p = %d\n", x, p);
			while (x % p == 0) {
				// printf("x = %d p = %d\n", x, p);
				x /= p;
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		int x = a[i];
		r[i] = n + 1;
		while (x ^ 1) {
			int p = mi[x];
			r[i] = min(r[i], rst[p] - 1), rst[p] = i;
			// printf("fs i = %d x = %d p = %d\n", i, x, p);
			while (x % p == 0) {
				// printf("x = %d p = %d\n", x, p);
				x /= p;
			}
		}
	}
	if (solve(1, n) == -1) puts("impossible"); else 
	for (int i = 1; i <= n; i++) printf("%d ", father[i]); puts("");
	return 0;
}
