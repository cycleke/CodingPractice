#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

char inb[1 << 16 | 123], *ine = inb, *ins = inb;
#define gc() ((ins == ine && (ine = (ins = inb) + fread(inb, 1, 1 << 16 | 123, stdin), ins == ine)) ? EOF : *ins++)
inline int gi(int &a) {
	static char c;
	do c = gc(); while (c < 48);
	for (a = c - 48; 47 < (c = gc()); a = (a << 3) + (a << 1) + c - '0');
}

const int MaxS = 100000 * 20 + 1, MaxM = 100000;

vector<int> row[MaxS];
long long result[2][MaxS];
int n, x, y, z, rty[MaxS];

inline void cmin(long long &a, const long long &b) {
	if (b < a) a = b;
}

inline void dp(vector<int> &v, long long *res) {
	int m = v.size(), i = -2, j = 1;
	long long ci = 0, cj = 0, cl = 1LL << 60, t;
	for (; j < m; j += 2) {
		if (j > 1) {
			t = z * abs(v[j - 2] - v[j - 1]);
			cj += t;
			cl += t;
		}
		while (i + 2 < j && x + y <= z * abs(v[j] - v[i + 2])) {
			if (i += 2) ci += z * abs(v[i] - v[i - 1]);
			cmin(cl, x + y + cj - ci + (i ? res[i - 1] : 0LL));
		}
		res[j] = min(cl, z * abs(v[j] - v[j - 1]) + (1 < j ? res[j - 2] : 0LL));
	}
}

inline long long solve(vector<int> &v, int etc) {
	int m = v.size();
	if (m < 2) return m ? etc : 0LL;
	dp(v, result[0]);
	if (m & 1) {
		reverse(v.begin(), v.end());
		dp(v, result[1]);
		reverse(result[1], result[1] + m);
		long long ret = min(result[0][m - 2], result[1][1]);
		for (int i = 2; i < m - 2; i += 2)
			cmin(ret, result[0][i - 1] + result[1][i + 1]);
		return ret + etc;
	} else
		return result[0][m - 1];
}
int main() {
	//freopen("t.in", "r", stdin);
	int a, b, m, d, ld = 0, lev = MaxM, i;
	gi(n), gi(x), gi(y), gi(z);
	for (i = 0; i < n; ++i) {
		gi(a), gi(b);
		d = (a >= b) ? 1 : -1;
		m = abs(a - b);
		while (m--) {
			if (ld == d) lev += d;
			if (!rty[lev]) rty[lev] = d;
			row[lev].push_back(i);
			ld = d;
		}
	}
	long long ans = 0LL;
	for (i = 0; i < MaxS; ++i)
		ans += solve(row[i], rty[i] > 0 ? y : x);
	printf("%lld\n", ans);
	return 0;
}
