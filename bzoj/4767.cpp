#include <cstdio>
#include <algorithm>
const int maxn(505), maxm(1e6), mod(1e9 + 7);
int fac[maxm], inv[maxm], _fac[maxm];
inline void init() {
	fac[0] = _fac[0] = 1;
	fac[1] = inv[1] = _fac[1] = 1;
	for (register int i = 2; i < maxm; ++i) {
		fac[i] = (long long) fac[i - 1] * i % mod;
		inv[i] = (long long) (mod - mod / i) * inv[mod % i] % mod;
		_fac[i] = (long long) _fac[i - 1] * inv[i] % mod;
	}
}
inline int C(int n, int m) {
  if (m < 0 || n - m < 0) return 0;
	return (long long)fac[n] * _fac[m] % mod * _fac[n - m] % mod;
}
int dp[maxn], cnt;
typedef std::pair<int, int> point;
point p[maxn];
struct equation {
	int x1, y1, x2, y2;
	equation(int x1, int y1, int x2, int y2) :
		x1(x1), y1(y1), x2(x2), y2(y2) {}
	inline bool solve_equation(int x, int y, point &ans) {
		int a = x * y1 - y * x1, b = x2 * y1 - y2 * x1;
		if (a % b)
		  return false;
		ans.first = a / b;
		a = x * y2 - y * x2, b = -b;
		if (a % b)
		  return false;
		ans.second = a / b;
		return true;
	}
};
inline void solve() {
	for (register int i = 0; i < cnt; ++i) {
		dp[i] = C(p[i].first + p[i].second, p[i].second);
		for (register int j = 0; j < i; ++j)
		  if (p[i].first >= p[j].first && p[i].second >= p[j].second) {
			  dp[i] -= (long long) C(p[i].first - p[j].first + p[i].second - p[j].second, p[i].first - p[j].first) * dp[j] % mod;
			  if (dp[i] < 0) dp[i] += mod;
		  }
	}
}
int main() {
	freopen("t.in" ,"r", stdin);
	init();
	int ex, ey, n, ax, ay, bx, by;
	scanf("%d%d%d", &ex, &ey, &n);
	scanf("%d%d%d%d", &ax, &ay, &bx, &by);
	equation eq(ax, ay, bx, by);
	cnt = 0;
	if (!eq.solve_equation(ex, ey, p[cnt++]))
    return puts("0"), 0;
	for (register int i = 0; i < n; ++i) {
		scanf("%d%d", &ex, &ey);
		if (!eq.solve_equation(ex, ey, p[cnt]) || p[cnt].first > p->first || p[cnt].second > p->second)
		  continue;
		++cnt;
	}
	std::sort(p, p + cnt);
	solve();
	printf("%d\n", dp[cnt - 1]);
	return 0;
}
