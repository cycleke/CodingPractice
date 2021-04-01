#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int Maxn = 205;


int ls[Maxn], rs[Maxn], dp[Maxn][Maxn], v[Maxn], last[Maxn];

#define clr(a,b) memset(a,b,sizeof(a))

int dfs(const int& u, const int& cur) {
	if (!(~u) || cur <= 0) return 0;
	if (~dp[u][cur]) return dp[u][cur];
	int &tmp = dp[u][cur];
	tmp = dfs(rs[u],cur);
	for (int i = 0; i < cur; ++i)
		tmp = max(tmp,dfs(rs[u],i) + dfs(ls[u],cur - i - 1) + v[u]);
	return tmp;
}

int main() {
	int N, M, a;
	while (scanf("%d%d", &N, &M)) {
		if (N == 0) return 0;
		clr(dp,-1); clr(ls,-1); clr(rs,-1); clr(last,-1);
		for (int i = 1; i <= N; ++i) {
			scanf("%d%d", &a, v + i);
			if (~last[a]) {
				rs[last[a]] = i; last[a] = i;
			} else {
				ls[a] = last[a] = i;
			}
		}
		printf("%d\n", dfs(0,M + 1));
	}
}
