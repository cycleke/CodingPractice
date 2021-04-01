#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int dig[12];
int dp[12][10][2];

int Try(const int &pos, const int &pre, const bool &Zero, const bool &Limited) {
	if (!pos) return !Zero;
	int &tmp = dp[pos][pre][Zero];
	if (!Limited && ~tmp) return tmp;
	int end = Limited ? dig[pos] : 9;
	int ret = 0;
	if (Zero) ret = Try(pos - 1, 0, 1, !end);
	else if(pre >= 2) ret = Try(pos - 1, 0, 0, !end);
	for (int i = 1; i <= end; ++i) {
		if (Zero || abs(i - pre) >= 2) 
			ret += Try(pos - 1, i, 0, Limited && i == end);
	}
	if (!Limited) tmp = ret;
	return ret;
}

int Cal(int a) {
	int cnt = 0;
	while (a) {
		dig[++cnt] = a % 10;
		a /= 10;
	}
	return Try(cnt, 0, 1, 1);
}

int main() {
	int L, R;
	scanf("%d%d", &L, &R);
	memset(dp, -1, sizeof dp);
	//printf ("%d %d\n", Cal(L - 1), Cal(R));
	printf("%d", Cal(R) - Cal(L - 1));
	return 0;
}