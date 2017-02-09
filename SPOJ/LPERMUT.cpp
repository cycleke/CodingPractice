#include <cstdio>
#define N 100009
#define cmax(a, b) (a < (b) ? a = (b) : 1)
#define rep for (i = 1; i <= n; ++i)
#define cans(l, r, len) ((len > ans && L[r] <= l && (s[r] - s[l - 1] << 1) == (len + 1) * (len)) ? ans = len : 1)
int a[N], L[N], la[N], s[N];
int main() {
	int n, ans = 0, i, j, mx = 0;
	scanf("%d", &n);
	L[0] = 0;
	rep {
		scanf("%d", a + i);
		s[i] = s[i - 1] + a[i];
		cmax(mx, la[a[i]] + 1);
		L[i] = mx;
		la[a[i]] = i;
	}
	L[n + 1] = n + 1;
	rep if (a[i] < 2) {
		cmax(ans, 1);
		for (j = i - 1, mx = 1; j >= L[i]; --j) {
			cmax(mx, a[j]);
			if (j + mx - 1 <= n)
				cans(j, j + mx - 1, mx);
		}
		for (j = i + 1, mx = 1; i >= L[j]; ++j) {
			cmax(mx, a[j]);
			if (j - mx + 1 > 0)
				cans(j - mx + 1, j, mx);
		}
	}
	printf("%d\n", ans);
	return 0;
}
