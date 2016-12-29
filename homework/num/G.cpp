#include <cstdio>
#include <iostream>
#include <cstring>
#include <iostream>
using namespace std;

int dig[12];
int dp[12][10][15][2];

int dfs(int pos, int per, int mod, bool ok, bool limited) {
	if (!pos) return ok && mod == 0;
	int &tmp = dp[pos][per][mod][ok];
	if (!limited && ~tmp) return tmp;
	int end = limited ? dig[pos] : 9;
	int ret = 0;
	for (int i = 0; i <= end; ++i)
		ret += dfs(pos - 1, i, (mod * 10 + i) % 13, ok || (per == 1 && i == 3), limited && i == end);
	if (!limited) tmp = ret;
	return ret;
}


int Cal(int N) {
	int tot = 0;
	while (N) {
		dig[++tot] = N % 10;
		N /= 10;
	}
	return dfs(tot, 0, 0, 0, 1);
}

int main() {
	int N;
	memset(dp, -1, sizeof(dp));
	while (scanf("%d", &N) != EOF) {
		printf("%d\n", Cal(N));
	}
	return 0;
}
