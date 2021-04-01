#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100010;
typedef long long LL;
int p[Maxn], nxt[Maxn], Stack[Maxn];
LL dp[Maxn][2];

void SelfMax(LL &a, const LL &b) { if (a < b) a = b; }

int main() {
	int N, M, F;
	scanf("%d%d%d", &N, &M, &F);
	for (int i = 1; i <= N; ++i) scanf("%d", p + i);
	int top = 0; Stack[top] = N;
	for (int i = N; i; --i) {
		while (top && p[i] >= p[Stack[top]]) --top;
		if (top) nxt[i] = Stack[top];
		else nxt[i] = i;
		Stack[++top] = i;
	}
	memset(dp, 128, sizeof dp);
	dp[1][0] = M;  LL tmp, ans = 0;
	for (int i = 1; i <= N; ++i) {
		SelfMax(ans, dp[i][0]); SelfMax(ans, dp[i][1]);
		SelfMax(dp[i + 1][0], max(dp[i][0], dp[i][1]));
		SelfMax(dp[nxt[i]][0], max(dp[i][0], dp[i][1]));
		tmp = dp[i][0] - F; 
		if (tmp > 0 && nxt[i] > i) 
			SelfMax(dp[nxt[i]][1], tmp / p[i] * p[nxt[i]] + tmp % p[i] - F);
		tmp = dp[i][1] + F;
		if (tmp > 0 && nxt[i] > i) 
			SelfMax(dp[nxt[i]][1], tmp / p[i] * p[nxt[i]] + tmp % p[i] - F);
	}
	cout << ans << endl;
	return 0;
}
