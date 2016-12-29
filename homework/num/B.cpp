#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
LL dp[22][22][2010];
int dig[22];
template<class T>
T readint(T& a) {
	a = 0; char c = getchar();
	while (c <'0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

LL dfs(const int& pos, const int& npos, const int& sum, const bool& limited) {
	if (!(~pos)) return sum == 0;
	if (sum < 0) return 0;
	LL &tmp = dp[pos][npos][sum];
	if (!limited && ~tmp) return tmp;
	int end = limited?dig[pos]:9;
	LL ret = 0;
	for (int i = 0; i <= end; ++i)
		ret += dfs(pos - 1,npos, sum + (pos - npos) * i,limited && i == end);
	if (!limited) tmp = ret;
	return ret;
}

LL Cal(LL n) {
	if (n < 0) return 0L;
	int tot = 0; LL ret = 0;
	while (n) {
		dig[tot++] = n % 10;
		n /= 10;
	}
	for (int i = 0; i < tot; ++i)
		ret += dfs(tot - 1, i, 0, 1);
	return ret - (tot - 1);
}

int main() {
	int T; LL l, r;
	readint(T);
	memset(dp, -1, sizeof(dp));
	while (T--) {
		readint(l); readint(r);
		cout << Cal(r) - Cal(l - 1) << endl;
	}
	return 0;
}
