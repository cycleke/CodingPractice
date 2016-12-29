#include <bits/stdc++.h>
using namespace std;

const int Maxn = 503;
typedef pair<int,int> pii;
vector<pii>edge[Maxn];
int dp[Maxn][Maxn][2];

void SelfMin(int &a, const int &b) { if (b < a) a = b; }

int Cal(int u, int fa) {
	int siz = 1, v, d, sons; dp[u][1][1] = 0;
	for (int i = 0; i < edge[u].size(); ++i) {
		v = edge[u][i].first, d = edge[u][i].second;
		if (v == fa) continue;
		sons = Cal(v, u);
		for (int j = siz; j; --j)
			for (int k = sons; k; --k) {
				SelfMin(dp[u][j + k][0], dp[u][j][0] + dp[v][k][1] + (d << 1));
				SelfMin(dp[u][j + k][0], dp[u][j][1] + dp[v][k][0] + d);
				SelfMin(dp[u][j + k][0], dp[u][j][1] + dp[v][k][1] + d);
				SelfMin(dp[u][j + k][1], dp[u][j][1] + dp[v][k][1] + (d << 1));
			}
		siz += sons;
	}
	return siz;
}

int main() {
	int N, u, v, d, Q;
	scanf("%d", &N);
	memset(dp, 127, sizeof dp);
	for (int i = 1; i < N; ++i) {
		scanf("%d%d%d", &u, &v, &d);
		edge[u].push_back(make_pair(v, d));
		edge[v].push_back(make_pair(u, d));
	}
	Cal(0, -1);
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d", &d);
		u = 0;
		while (dp[0][u + 1][0] <= d || dp[0][u + 1][1] <= d) ++u;
		printf("%d\n", u);
	}
	return 0;
}
