#include <bits/stdc++.h>
using namespace std;
#define N 110
queue<int>q;
bool vis[N];
vector<int>g[N];
long long d[2][N];
int n,m;
void bfs(int s) {
	while(!q.empty())q.pop();
	memset(d,0,sizeof d);
	memset(vis,0,sizeof vis);
	int u,v,di; q.push(s); d[1][s]=1;
	while(!q.empty()) {
		u=q.front(); q.pop();
		for(int i=0;i<g[u].size();++i)
			if(!vis[v=g[u][i]]) {
				d[0][v]=d[0][u]+1;
				d[1][v]=d[1][u];
				q.push(v); vis[v]=true;
			} else if(d[0][u]+1==d[0][v])
				d[1][v]+=d[1][u];
	}
}

int main() {
	double ans=1.0; long long md,cns;
	scanf("%d%d",&n,&m);
	int i,a,b;
	while(m--) {
		scanf("%d%d",&a,&b);
		g[a].push_back(b),g[b].push_back(a);
	}bfs(1); md=d[0][n]; cns=d[1][n];
	for(i=2;i<n;++i) {
		bfs(i);
		if(d[0][1]+d[0][n]==md)
			ans=max(ans,2.0*d[1][1]*d[1][n]/cns);
	}
	return printf("%.12lf\n",ans),0;
}
