// by OwenCreeper
#include "bits/stdc++.h"
#define N 1000000
#define MOD 1000000007
using namespace std;
typedef long long ll;
inline int read() {
	int num = 0, k = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') k = ch == '-' ? -1 : 1, ch = getchar();
	while (ch >= '0' && ch <= '9') num *= 10, num += ch - 48, ch = getchar();
	return num * k;
}
ll sa[N + 5], tot;
int a[N + 5], k, n;
ll calh(int pos, int x) { return (pos - 1) * 1ll * x - sa[pos - 1]; }
ll calt(int pos, int x) { return tot - sa[pos] - (n - pos) * 1ll * x; }
int work() {
	memset(sa, 0, sizeof(sa)), memset(a, 0, sizeof(a));
	tot = sa[0] = 0;
	for (int i = 1; i <= n; i++) a[i] = read(), tot += a[i];
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) sa[i] = sa[i - 1] + a[i];
	int mi, mx, avel = tot / n, aver = avel + (tot % n == 0 ? 0 : 1);
	// printf("tot = %lld n = %d %d %d\n", tot, n, avel, aver);
	for (int i = 1; i <= n; i++) 
		if (a[i] <= avel && aver <= a[i + 1]) {
			if (calt(i, aver) <= k) 
				return aver - avel;
			else
				break;
		}
	for (int i = 1; i <= n; i++) 
		if (calh(i, a[i]) >= k) {
			int l = a[i - 1], r = a[i];
			while (l < r) {
				int mid = l + r + 1 >> 1;
				if (calh(i, mid) <= k) l = mid; else r = mid - 1;
			}
			// printf("i = %d\n", i);
			mi = l;
			break;
		}
	for (int i = n; i >= 1; i--) 
		if (calt(i, a[i]) >= k) {
			int l = a[i], r = a[i + 1];
			while (l < r) {
				int mid = l + r >> 1;
				// printf("cal %d, %d = %lld\n", i, mid, calt(i, mid));
				if (calt(i, mid) <= k) r = mid; else l = mid + 1;
			}
			// printf("i = %d\n", i);
			mx = l;
			break;
		}
	// printf("%d %d\n", mi, mx);
	return mx - mi;
}
int main(int argc, char const *argv[]) {
	// freopen("f.in", "r", stdin);
	while (scanf("%d%d", &n, &k) != EOF) printf("%d\n", work());
	return 0;
}
