#include <cstdio>
#include <cstring>
#include <iostream>
const int INF = 0x3f7f7f7f;

int dp[55][55][2];
char S[55];

bool IsSame(const int &l, const int &r) {
	if ((l & 1) ^ (r & 1)) {
		int Mid = (l + r) >> 1;
		for (int i = l, j = Mid + 1; i <= Mid; ++i, ++j) {
			if (S[i] != S[j])
				return false;
		}
		return true;
	} else return false;
}

void SelfMin(int &a, const int &b) {
	if (a > b) a = b;
}

int Cal(const int &l, const int &r, const int &k) {
	if (~dp[l][r][k]) return dp[l][r][k];
	if (l == r) return dp[l][r][k] = (k ? INF : 1);
	int &tmp = dp[l][r][k];
	tmp = INF;
	if (k) {
		for (int i = l; i < r; ++i){
			SelfMin(tmp, Cal(l,i,0) + Cal(i+1,r,0) + 1);
			SelfMin(tmp, Cal(l,i,0) + Cal(i+1,r,1) + 1);
			SelfMin(tmp, Cal(l,i,1) + Cal(i+1,r,0) + 1);
			SelfMin(tmp, Cal(l,i,1) + Cal(i+1,r,1) + 1);
		}
	}
	if (IsSame(l,r))
		SelfMin(tmp, Cal(l, (l + r)>>1, 0) + 1);
	for (int i = l; i < r; ++i)
		SelfMin(tmp, Cal(l, i, 0) + r - i);
	return tmp;
}

int main() {
	scanf("%s", S);
	memset(dp, -1, sizeof dp);
	int len = strlen(S) - 1;
	printf("%d", std::min(Cal(0,len,0), Cal(0,len,1)));
	return 0;
}
