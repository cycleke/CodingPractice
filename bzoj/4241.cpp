#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100003
#define wlp while
#define rep(i, l, r) for (i = l; i <= r; ++i)
int cnt[N], a[N], pre[319][N], bel[N], L[319], R[319], stk[713], hash[N];
long long f[319][319];
char buf[6000001], *s, *e;
inline void gi(int &a) {
    wlp (*s < '0') ++s; a = *s++ - '0';
    wlp ('-' < *s) a = (a << 3) + (a << 1) + (*s++) - '0';
}
int main() {
    e = buf + fread(s = buf, 1, 6000001, stdin);
    int n, q, blo, t, *hcnt, *tp = stk, l, r, sz, *sx, *sy;
    register int i, j, k;
    long long mx, _t;
    gi(n), gi(q);
    rep(i, 1, n) gi(a[i]);
	memcpy(hash, a, (n + 1) * sizeof(int));
    std::sort(hash + 1, hash + n + 1);
    hcnt = std::unique(hash + 1, hash + n + 1);
	rep(i, 1, n) a[i] = std::lower_bound(hash + 1, hcnt, a[i]) - hash;
	blo = sqrt(n) + 10.5;
    rep(i, 1, n) bel[i] = (i - 1) / blo + 1;
    for (i = 1, j = 1; i <= n; i += blo, ++j) {
		L[j] = i;
		R[j] = i + blo - 1;
	}
	blo = bel[n];	
	R[blo] = n;
	sz = (int)(hcnt - hash) * sizeof(int);
    rep(i, 1, blo) {
		k = R[i];
        rep(j, L[i], k) ++cnt[a[j]];
        memcpy(pre[i], cnt, sz);
    }
    rep(i, 1, blo) {
        mx = -1LL;
		k = L[i];
		t = a[L[i]];
		sx = pre[i - 1];
        rep(j, i, blo) {
			sy = pre[j];
            wlp (k <= R[j]) {
                _t = (long long)(sy[a[k]] - sx[a[k]]) * hash[a[k]];
                if (mx < _t) mx = _t;
                ++k;
            }
            f[i][j] = mx;
        }
    }
    memset(cnt, 0, sz);
    wlp (q--) {
        gi(l), gi(r);
		mx = -1LL;
        if (bel[l] + 1 < bel[r]) {
            sx = pre[bel[l]], sy = pre[bel[r] - 1];
            mx = f[bel[l] + 1][bel[r] - 1];
            j = R[bel[l]];
            rep(i, l, j) if (!cnt[a[i]]++) {
				*++tp = a[i];
				cnt[*tp] += sy[*tp] - sx[*tp];
			}
            rep(i, L[bel[r]], r) if (!cnt[a[i]]++) {
				*++tp = a[i];
				cnt[*tp] += sy[*tp] - sx[*tp];
			}
        } else rep(i, l, r) if (!cnt[a[i]]++) *++tp = a[i];	
        rep(hcnt, stk + 1, tp) {
            _t = (long long)cnt[*hcnt] * hash[*hcnt];
            if (mx < _t) mx = _t;
        }
        printf("%lld\n", mx);
        wlp (stk < tp) cnt[*tp--] = 0;
    }
    return 0;
}
