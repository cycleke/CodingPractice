#include <bits/stdc++.h>
using namespace std;

const int Maxn = 503;
int Sum[Maxn][Maxn], a[Maxn][Maxn];
int dp[Maxn][Maxn];

int gs(const int &a, const int &b, const int &c, const int &d) {
	return Sum[c][d] - Sum[a - 1][d] - Sum[c][b - 1] + Sum[a - 1][b - 1];
}

void SelfMax(int &a, const int &b) {
	if (a < b) a = b;
}

int main() {
	//freopen("O.in","r",stdin);
	//freopen("O.out","w",stdout);
	int N, M, ans = -0x7f7f7f7f;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d", a[i] + j);
			Sum[i][j] = Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1] + a[i][j];
			dp[i][j] = a[i][j];
			//cout << Sum[i][j] << ' ';
		}
		//puts("");
	}
	for (int k = 3; k <= N && k <= M; k += 2) {
		for (int i = 1; i + k - 1 <= N; ++i)
			for (int j = 1; j + k  - 1 <= M; ++j) {
				dp[i][j] = gs(i, j, i + k - 1, j + k - 1) - dp[i + 1][j + 1] - a[i + 1][j];
				SelfMax(ans, dp[i][j]);
			}
	}
	printf("%d", ans);
	return 0;
}
