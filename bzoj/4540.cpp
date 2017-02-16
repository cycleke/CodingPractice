#include <cstdio>
#include <algorithm>
#define N 100003
#define wlp while
#define rep(i, l, r) for (register int i = l, _R = (r); i <= _R; ++i)
typedef int arr[N];
typedef long long arr64[N];
arr a, bel, ST[19], stk, lg;
arr64 SL, SR, Ans;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline void geti(int &ina) {
	static char inc,inb[1<<16], *ins=inb, *ine=inb, insign;
	for(insign = 0; (inc = getc()) < '0'; insign |= inc == '-');
	for(ina = inc-'0'; '-' < (inc=getc()); ina = (ina << 3) + (ina<<1) + inc - '0');
	if (insign) ina = -ina;
}
inline int Min(const int &i, const int &j) {
	return a[i] < a[j] ? i : j;
}
struct Q {
	int l, r, id;
	void Input(int i) {
		geti(l), geti(r);
		id = i;
	}
}q[N];
bool operator < (const Q &a, const Q &b) {
	return (bel[a.l] ^ bel[b.l]) ? bel[a.l] < bel[b.l] : bel[a.r] < bel[b.r];
}
inline void Init(const int &n) {
	*lg = -1;
	rep(i, 1, n) {
		ST[0][i] = i;
		lg[i] = lg[i >> 1] + 1;
	}
	rep(i, 1, lg[n])
		rep(j, 1, n - (1 << i) + 1)
		ST[i][j] = Min(ST[i - 1][j], ST[i - 1][j + (1 << i - 1)]);
	int *tp = stk;
	*tp = 0;
	rep(i, 1, n) {
		wlp (stk < tp && a[*tp] >= a[i]) --tp;
		SL[i] = SL[*tp] + (long long)a[i] * (i - *tp);
		*++tp = i;
	}
	*(tp = stk) = n + 1;
	for (register int i = n; i; --i) {
		wlp (stk < tp && a[*tp] >= a[i]) --tp;
		SR[i] = SR[*tp] + (long long)a[i] * (*tp - i);
		*++tp = i;
	}
}

inline int gmin(const int &l, const int &r) {
	static int t;
	t = lg[r - l + 1];
	return Min(ST[t][l], ST[t][r - (1 << t) + 1]);
}

inline long long cl(int l, int r) {
	static int t;
	t = gmin(l, r);
	return (r - t + 1) * (long long)a[t] + SR[l] - SR[t];
}

inline long long cr(int l, int r) {
	static int t;
	t = gmin(l, r);
	return (t - l + 1) * (long long)a[t] + SL[r] - SL[t];
}

int main() {
	int n, m, rm;
	geti(n), geti(m);
	for (rm = 1; rm * rm <= n; ++rm);
	rep(i, 1, n) {
		bel[i] = (i - 1) / rm;
		geti(a[i]);
	}
	Init(n);

	rep(i, 1, m) q[i].Input(i);

	std::sort(q + 1, q + m + 1);

	int l = 1, r = 0, _l, _r;
	long long ct = 0;
	rep(i, 1, m) {
		_l = q[i].l, _r = q[i].r;
		wlp (_l < l) ct += cl(--l, r);
		wlp (r < _r) ct += cr(l, ++r);
		wlp (l < _l) ct -= cl(l++, r);
		wlp (_r < r) ct -= cr(l, r--);
		Ans[q[i].id] = ct;
	}
	rep(i, 1, m)
		printf("%lld\n", Ans[i]);

	return 0;
}
