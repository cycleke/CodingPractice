#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long LL;

inline int count(int sta) {
	int tot = 0;
	while (sta) {
		if (sta & 1) ++tot;
		sta >>= 1;
	}
	return tot;
}

LL dp[20][20][5][2];
#define check(a,b) ((a == 1 && b == 4) || (a == 4 && b == 1))
LL dfs(int pos, int sta, int per, bool Rigth) {
	if (!pos) return (Rigth && count(sta) >= 3) ? 1 : 0;
	LL &tmp = dp[pos][sta][per][Rigth];
	if (~tmp) return tmp;
	tmp = 0;
	for (int i = 1; i <= 4; ++i) {
		tmp += dfs(pos - 1, sta | (1 << (i - 1)), i,Rigth || check(per, i));
	}
	return tmp;
}

int main() {
	int n;
	memset(dp, -1, sizeof(dp));
	while (cin >> n) {
		if (n == -1) return 0;
		printf("%d: %lld\n", n, dfs(n, 0, 0, 0));
	}
	return 0;
}
