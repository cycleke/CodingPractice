#include <bits/stdc++.h>
using namespace std;

int dp[1003][1003], Max[1003][1003];

pair<int, int>d[1003];

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	return a.first > b.first;
}

int main() {
	int N, M, ans = 0;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) 
		scanf("%d", &d[i].second);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &d[i].first);
	sort(d + 1, d + N + 1, cmp);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			dp[i][j] = Max[i - 1][j - 1] + max(0, d[i].second - (j - 1) * d[i].first);
			Max[i][j] = max(Max[i - 1][j], dp[i][j]);
			if (Max[i][j] > ans) ans = Max[i][j];
		}
	}
	printf("%d\n", ans);
	return 0;
}
