#include <bits/stdc++.h>
#define N 100003
#define wlp while
#define rep(i, l, r) for (register int i = l; i <= r; ++i)
#define rrp(i, l, r) for (register int i = l; i >= r; --i)
typedef int arr[N];
typedef long long arr64[N];
arr cnt;
arr sum, ha, a;
arr64 ans;
char s[N];
struct Q {
	int l, r, id, _l, _r;
} q[N];
bool operator < (const Q &a, const Q &b) {
	return (a._l ^ b._l) ? a._l < b._l : a._r < b._r;
}
int main() {
	long long ct;
	int *end, p;
	int n, m, rn;
	scanf("%d%s%d", &p, s + 1, &m);
	n = strlen(s + 1);
	if (!(p ^ 2) || !(p ^ 5)) {
		unsigned int _p = p, l, r;
		rep(i, 1, n) {
			cnt[i] = cnt[i - 1];
			sum[i] = sum[i - 1];
			if ((s[i] - '0') % _p == 0) {
				++cnt[i];
				sum[i] += i;
			}
		}
		wlp (m--) {
			scanf("%u%u", &l, &r);
			printf("%lld\n", sum[r] - sum[l - 1] - (cnt[r] - cnt[l - 1]) * (l - 1LL));
		}
		return 0;
	}
	for (rn = 1; rn * rn <= n; ++rn);
	int l, r, _l, _r;
	rep(i, 1, m) {
		scanf("%d%d", &l, &r);
		++r;
		_l = l / rn, _r = r / rn;
		q[i] = (Q) {l, r, i, _l, _r};
	}
	std::sort(q + 1, q + m + 1);
	ct = 1;
	rrp(i, n, 1) {
		ha[i] = a[i] = (a[i + 1] + ct * (s[i] - '0')) % p;
		for (ct = (ct << 3) + (ct << 1); ct >= p; ct -= p);
	}
	ha[++n] = 0;
	std::sort(ha + 1, ha + n + 1);
	end = std::unique(ha + 1, ha + n + 1);
	rep(i, 1, n) a[i] = std::lower_bound(ha + 1, end, a[i]) - ha;
	l = 1, r = 0;
	ct = 0;
	rep(i, 1, m) {
		_l = q[i].l, _r = q[i].r;
		wlp (_l < l) ct += cnt[a[--l]]++;
		wlp (r < _r) ct += cnt[a[++r]]++;
		wlp (l < _l) ct -= --cnt[a[l++]];
		wlp (_r < r) ct -= --cnt[a[r--]];
		ans[q[i].id] = ct;
	}
	rep(i, 1, m)
		printf("%lld\n", ans[i]);
	return 0;
}
