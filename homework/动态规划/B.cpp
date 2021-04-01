#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int Maxn = 2010;
typedef long long ll;
int Size[Maxn], totedge = -1, N, M;
ll dp[Maxn][Maxn];
struct edge {
	int to,wei; edge *next;
}E[Maxn << 1], *head[Maxn];

inline void adde(const int& a,const int& b,const int& c) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->wei = c;
	ne->next = head[a]; head[a] = ne;
}

void dfs(const int& u,const int& fa) {
	Size[u] = 1; dp[u][0] = dp[u][1] = 0;
	int v, k, j; ll a, b;
	for (edge *i = head[u]; i; i = i->next) {
		if (i->to == fa) continue;
		v = i->to;
		dfs(v,u); Size[u] += Size[v];
		for (j = min(Size[u],M); ~j; --j) 
			for (k = 0; k <= min(Size[v],j); ++k) {
				a = (ll)k*(M-k) + ((ll)Size[v]-k)*((ll)N-M-(Size[v]-k));
				b = a * (ll)(i->wei);
				dp[u][j] = max(dp[u][j],dp[u][j-k] + b + dp[v][k]);
			}
	}
}

int main() {
	int a, b, c;
	scanf("%d%d", &N, &M);
	memset(head,0,sizeof(head));
	memset(dp,128,sizeof(dp));
	for (int i = 1; i < N; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		adde(a,b,c); adde(b,a,c);
	}
	dfs(1,0);
	cout << dp[1][M];
	return 0;
}
