#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char S[110];
int dp[110][110];

int getw(int x) {
	int tot = 0;
	while (x) { x /= 10; ++tot; }
	return tot;
}

bool IsSame(const int &l, const int &r, const int &x, const int& y) {
	//判断 l ~ r 可不可以重叠为 x ~ y
	int len1 = r - l + 1, len2 = y - x + 1;
	if (len2 < len1 || len2 % len1) return false;
	for (int i = l, j = x; j <= y;++j) {
		if (S[i] ^ S[j]) return false;
		if (++i > r) i = l;
	}
	return true;
	
}

int Cal(const int &l, const int &r) {
	if (~dp[l][r]) return dp[l][r];
	int &tmp = dp[l][r];
	tmp = r - l + 1;
	for (int i = l; i < r; ++i) {
		tmp = min(tmp, Cal(l, i) + Cal(i + 1, r));
		if (IsSame(l, i, i + 1, r)) 
			tmp = min(tmp, Cal(l,i) + getw((r - i) / (i - l + 1) + 1) + 2);
	}
	return tmp;
}

int main() {
	gets(S);
	int len = strlen(S) - 1;
	memset(dp, -1, sizeof dp);
	printf("%d", Cal(0,len));
	return 0;
}
