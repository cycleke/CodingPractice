#include <bits/stdc++.h>
#define rep(i, l, r) for (register int i = l; i < r; ++i)
inline void cmax(long long &a, const long long &b) {
	if (a < b) a = b;
}
struct enemy {
	int a, t;
	long long sa, st;
	void Input(const int &atk) {
		scanf("%d%d", &a, &t);
		t = (t - 1) / atk + 1;
	}
	bool operator < (const enemy &b) const {
		return (long long)b.a * t < (long long)a * b.t;
	}
}e[300001];
std::pair<long long, long long>line[35001];
#define K first
#define B second
void upd(int u, int l, int r, std::pair<long long, long long> nl) {
	if (line[u].K == nl.K) 
	  return cmax(line[u].B, nl.B);
	int m = l + r >> 1;
	double k = -(double)(nl.B - line[u].B) / (nl.K - line[u].K);
	if (k < l || r < k || !(l ^ r)) {
		if (line[u].K * m + line[u].B < nl.K * m + nl.B)
		  line[u] = nl;
		return;
	}
	if (k < m + 0.5) {
		if (line[u].K * r + line[u].B < nl.K * r + nl.B)
		  std::swap(line[u], nl);
		upd(u << 1, l, m, nl);
	} else {
		if (line[u].K * l + line[u].B < nl.K * l + nl.B)
		  std::swap(line[u], nl);
		upd(u << 1 | 1, m + 1, r, nl);
	}
}
long long ask(const int &x) {
	static long long rt;
	static int u, l, r, m;
	u = 1, l = 1, r = 10000;
	rt = line[1].K * x + line[1].B;
	while (l ^ r) {
		m = l + r >> 1;
		cmax(rt, line[u].K * x + line[u].B);
		if (x <= m)
		  u = u << 1, r = m;
		else
		  u = u << 1 | 1, l = m + 1;
	}
	return rt;
}
int main() {
	int n, atk;
	scanf("%d%d", &n, &atk);
	rep(i, 0, n) e[i].Input(atk);
	std::sort(e, e + n);
	rep(i, 1, n) e[i].st = e[i - 1].st + e[i - 1].t;
	e[n - 1].sa = e[n - 1].a;
	for (register int i = n - 2; ~i; --i)
	  e[i].sa = e[i + 1].sa + e[i].a;
	rep(i, 0, 35001)
		line[i].B = -1e18;
	long long mx = 0, ans = 0, t;
	for (register int i = n - 1; ~i; --i) {
		t = e[i].sa * e[i].t + e[i].st * e[i].a - e[i].a;
		cmax(mx, ask(e[i].t) + t);
		upd(1, 1, 10000, std::make_pair(-e[i].a, t));
	}
	rep(i, 0, n)
		ans += e[i].sa * e[i].t - e[i].a;
	ans -= mx;
	printf("%lld\n", ans);
	return 0;
}
