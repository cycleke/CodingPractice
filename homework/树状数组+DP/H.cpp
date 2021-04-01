#include <bits/stdc++.h>
using namespace std;

const int Mod = 1000000007;
char S[1800],num[510];
int dp[1800][3500][2][2][2];

void Add(int &a, const int &b) {
	a += b; if (a >= Mod) a %= Mod;
}

int Cal(int pos, int cnt, bool f1, bool f2, bool k) {
	if (pos < 0) return k && cnt > 1700;
	int &tmp = dp[pos][cnt][f1][f2][k];
	if (~tmp) return tmp;
	tmp = 0;
	int end1 = f1 ? 1 : S[pos];
	int end2 = f2 ? 1 : S[pos];
	for (int i = 0; i <= end1; ++i) 
		for (int j = 0; j <= end2; ++j) {
			if (!k && i > j) continue;
			Add(tmp, Cal(pos - 1, cnt + i - j , f1 || (i < end1), f2 || (j < end2), k || (i < j)));
		}
	return tmp;
}

bool check(const char &c) { return c & 1; }

int ToTwo() {
	int len1 = strlen(num), len2 = 0, l;
	l = 1;
	for (int i = len1; i; --i)
		num[i] = num[i - 1] - '0';
	while (l <= len1) {
		S[len2++] = check(num[len1]);
		for (int i = l; i <= len1; ++i) {
			num[i + 1] += 10 * (num[i] & 1);
			num[i] >>= 1;
		}
		if (num[l] == 0) ++l;
	}
	return len2;
}

int main() {
	scanf("%s", num);
	int len = ToTwo();
	
	memset(dp, -1, sizeof dp);
	printf("%d\n", Cal(len - 1, 1700, 0, 0, 0));
	return 0;
}
