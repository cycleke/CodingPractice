#include <bits/stdc++.h>
using namespace std;

const int MaxN = 3011;
const long long mod = 1e9 + 7;

typedef long long arr2[MaxN][MaxN], arr[MaxN];

#define rep(i, r, _r) for (i = 0, _r = (r); i < _r; ++i)

arr x;
arr2 dp, dp2;

class PalindromicSubseq {
	public:
	int solve(string s) {
		long long tmp;
		int n = s.length();
		int d, i, j, _d, _i, _j;
		for (d = n; d; --d)
			rep(i, n - d + 1, _i) {
				j = i + d;
				
				if (i == 0 || j == n) {
					dp[i][j] = 1LL;
					continue;
				}
				
				tmp = dp[i - 1][j] + dp[i][j + 1] - (s[i - 1] == s[j] ? 0LL : dp[i - 1][j + 1] ) + mod;
				dp[i][j] = tmp % mod;
			}
		rep(d, n + 1, _d)
			rep(i, n - d + 1, _i) {
			j = i + d;
			if (d < 2)
				dp2[i][j] = d + 1LL;
			else {
				tmp = dp2[i + 1][j] + dp2[i][j - 1] - (s[i] == s[j - 1] ? 0LL : dp2[i + 1][j - 1]) + mod;
				dp2[i][j] = tmp % mod;
			}
		}
		rep(i, n, _i) x[i] = dp[i][i + 1];
		rep(i, n, _i) rep(j, n, _j)
			if (i < j && s[i] == s[j]) {
				tmp = dp[i][j + 1] * dp2[i + 1][j];
				x[i] = (x[i] + tmp) % mod;
				x[j] = (x[j] + tmp) % mod;
			}
		long long ans = 0LL;
		rep(i, n, _i)
			ans ^= x[i] * (i + 1) % mod;
		return (int)ans;
	}
};



