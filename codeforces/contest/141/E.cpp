#include <bits/stdc++.h>
using namespace std;
#define N 1005
#define M 100005
int fa[N]; bool used[M];
struct E {
	int u,v,id,w;
	bool operator < (const E&a) const {return w<a.w;}
}edge[M];
int find(int a) {return (fa[a]^a)?fa[a]=find(fa[a]):a;}
int main() {
	int n,m; char ts[3]; scanf("%d%d",&n,&m);
	if(~n&1) return puts("-1"),0;
	for(int i=1;i<=m;++i) {
		scanf("%d%d%s",&edge[i].u,&edge[i].v,ts);
		edge[i].w=*ts=='M'; edge[i].id=i;
	}sort(edge+1,edge+m+1);
	for(int i=1;i<=n;++i) fa[i]=i;
	int totw=0;
	for(int i=1;i<=m;++i) {
		int x=find(edge[i].u),y=find(edge[i].v);
		if(x==y) continue; used[edge[i].id]=true;
		totw+=edge[i].w; fa[x]=y;
	}
	if(n<totw*2+1) return puts("-1"),0;
	if(totw*2+1<n) {
		for(int i=1;i<=n;++i) fa[i]=i;
		for(int i=1;i<=m;++i) 
		if(used[edge[i].id]&&edge[i].w){
			fa[find(edge[i].u)]=find(edge[i].v);
		}else used[edge[i].id]=0;
		for(int i=1;i<=m;++i)
		  if(!used[edge[i].id]&&edge[i].w) {
			int x=find(edge[i].u),y=find(edge[i].v);
			if(x==y) continue; used[edge[i].id]=true;
			fa[x]=y; if((++totw)*2+1==n) break;
		  }
		for(int i=1;i<=m;++i)
		  if(!used[edge[i].id]&&!edge[i].w) {
			int x=find(edge[i].u),y=find(edge[i].v);
			if(x==y) continue; used[edge[i].id]=true;
			fa[x]=y;
		  }
		for(int i=2;i<=n;++i) if(find(i)^find(1)) return puts("-1"),0;
	} if(totw*2+1<n) return puts("-1"),0;
	printf("%d\n",n-1);
	for(int i=1;i<=m;++i) if(used[i]) printf("%d ",i);
	return 0;
}
