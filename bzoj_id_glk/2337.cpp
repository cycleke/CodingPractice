#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 205
#define M 20005
#define eps 1e-10
int n,m,head[N],nxt[M],to[M],deg[N],w[M],tote;
double a[N][N],ans;
inline void gauss() {
	int i,j,k,o; double mx,t;
	for(i=1;i<=n;++i) {
		for(j=o=i,mx=0;j<=n;++j) (fabs(a[j][i])>mx)?mx=fabs(a[j][i]),o=j:1;
		if(i^o) for(j=1;j<=n+1;++j) swap(a[o][j],a[i][j]);
		t=a[i][i]; for(j=1;j<=n+1;++j) a[i][j]/=t;
		for(j=1;j<=n;++j) 
		if(i^j){
			for(t=a[j][i],k=1;k<=n+1;++k) a[j][k]-=t*a[i][k];
		}
	}
}
#define adde(a,b,c) (to[tote]=b,w[tote]=c,nxt[tote]=head[a],head[a]=tote++,++deg[a])
int main() {
	int i,j,k,o; scanf("%d%d",&n,&m);
	memset(head,-1,sizeof head);
	while(m--) {
		scanf("%d%d%d",&i,&j,&k);
		adde(i,j,k); if(i^j) adde(j,i,k);
	}
	for(i=0;i<31;++i) {
		memset(a,0,sizeof a);
		for(j=1;j<n;++j){
			a[j][j]=1.;
			for(k=head[j];~k;k=nxt[k])
			  if(w[k]&(1<<i)) a[j][to[k]]+=1.0/deg[j],a[j][n+1]+=1.0/deg[j];
			  else a[j][to[k]]-=1.0/deg[j];
		}
		a[n][n]=1;gauss(),ans+=a[1][n+1]*(1<<i);
	}return printf("%.3lf\n",ans),0;
}
