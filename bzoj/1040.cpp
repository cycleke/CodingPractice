#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 1000005
long long f[N],g[N];
inline long long max(long long a,long long b){return a<b?b:a;}
int to[N<<1],nt[N<<1],hd[N],x,y,val[N];
bool vis[N],ban[N<<1];
//f[i] chose i
//g[i] don't chose i
void dfs(const int&u,const int&fa) {
	vis[u]=true;
	int v,it;
	for(it=hd[u];(~it)&&!x;it=nt[it])
		if(!vis[v=to[it]]) dfs(v,u);
		else if(v^fa) x=u,y=v,ban[it]=ban[it^1]=true;
}
void dp(const int&u,const int&fa) {
	if(u^y) f[u]=val[u];
	else f[u]=0;
	int v,it; g[u]=0;
	vis[u]=true;
	for(it=hd[u];~it;it=nt[it])
		if((v=to[it])^fa&&!ban[it]) {
			dp(v,u);
			f[u]+=g[v];
			g[u]+=max(f[v],g[v]);
		}
}
int main() {
	int n=geti();
	memset(hd,-1,(n+1)*sizeof(int));
	for(register int i=1,te=0,h;i<=n;++i) {
		val[i]=geti(); h=geti();
		to[te]=i,nt[te]=hd[h],hd[h]=te++;
		to[te]=h,nt[te]=hd[i],hd[i]=te++;
	}
	long long ans=0,t1,t2;
	for(register int i=1;i<=n;++i)
		if(!vis[i]) {
			x=y=0;
			dfs(i,0);
			dp(x,0); t1=max(f[x],g[x]);
			x^=y^=x^=y;
			dp(x,0); t2=max(f[x],g[x]);
			ans+=max(t1,t2);
		}
	printf("%lld\n",ans);
	return 0;
}
