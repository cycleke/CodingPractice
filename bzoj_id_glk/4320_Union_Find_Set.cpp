#include <cstdio>
#include <cstring>
#define M 300005
#define N 100005
int fa[M],ans[N],val[N],d[550];
char op[N],ts[4],mark[M];
int find(int u) {return (fa[u]^u)?(fa[u]=find(fa[u])):u;}
void Union(int x,int y) {
	x=find(x),y=find(y);
	(x<y)?fa[x]=y:fa[y]=x;
}
int main() {
	int n,i,j,t; memset(d,127,sizeof d);
	for(scanf("%d",&n),i=1;i<=n;++i) {
		scanf("%s%d",ts,val+i);
		if((op[i]=*ts)=='A') {
			for(j=1;j<550;++j) ((t=val[i]%j)<d[j])?d[j]=t:1;
			mark[val[i]]=1;
		} else ans[i]=d[val[i]];
	}fa[300001]=300001;
	for(i=300000;i;--i) (mark[i])?fa[i]=i:fa[i]=find(fa[i+1]);
	for(i=n;i;--i) {
		if(op[i]=='A') Union(val[i],val[i]+1);
		else if(val[i]>=550) {
			t=find(1),ans[i]=(t==300001)?val[i]-1:(t%val[i]);
			for(j=val[i];j<300001;j+=val[i])
			  (((t=find(j))==300001)?t=val[i]-1:t%=val[i]),(t<ans[i])?ans[i]=t:1;
		}
	}
	for(i=1;i<=n;++i)
	  if(op[i]=='B') printf("%d\n",ans[i]);
	return 0;
}
