#include <cstdio>
#include <cstring>
#define cmin(a,b) (b<a?a=b:1)
#define cmax(a,b) (a<b?a=b:1)
#define N 100005
int head[N],to[N],nxt[N],tote,n,root;
int mi[N],mx[N],mark[N],ans;
int dfs(int u) {
	int ret=1;mi[u]=mx[u]=u;
	for(int i=head[u];~i;i=nxt[i]) {
		ret+=dfs(to[i]);
		cmax(mx[u],mx[to[i]]);
		cmin(mi[u],mi[to[i]]);
	}
	if(mx[u]-mi[u]+1==ret) ++ans;
	return ret;
}
int main() {
	scanf("%d",&n); memset(head,-1,sizeof head);
	for(int i=1,a,b;i<n;++i) {
		scanf("%d%d",&a,&b);
		to[tote]=b,nxt[tote]=head[a];
		head[a]=tote++,mark[b]=a;
	}
	for(int i=1;i<=n;++i) if(!mark[i]) {root=i;break;}
	dfs(root); return printf("%d\n",ans),0;
}
