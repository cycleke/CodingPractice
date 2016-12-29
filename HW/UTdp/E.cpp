#include <bits/stdc++.h>
using namespace std;

const int Mod = 1000000007, Maxn = 305;
char S[Maxn];
long long dp[Maxn][Maxn];

inline bool check(const int &a, const int &b) { return (S[a] == '(' && S[b] == ')') || (S[a] == '[' && S[b] == ']'); }

long long Cal(int l, int r) {
	if (l >= r) return 1;
	if (~dp[l][r]) return dp[l][r];
	long long &ret = dp[l][r] = 0;
	ret = Cal(l + 1, r);
	for (int i = l; i <= r; ++i) 
		if (check(l, i)) ret = (ret + (long long)Cal(l + 1, i - 1) * Cal(i + 1, r)) % Mod;
	return ret;
}

int main() {
	int N;
	scanf("%d", &N);
	scanf("%s", S);
	memset(dp, -1, sizeof dp);
	long long ans = Cal(0, N - 1);
	ans = (ans - 1 + Mod) % Mod;
	printf("%lld\n", ans);
	return 0;
}



