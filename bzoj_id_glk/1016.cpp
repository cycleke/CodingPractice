#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ina; char inc; bool insign;
inline int geti() {
	for(insign=0;(inc=getchar())<'0'||inc>'9';insign|=inc=='-');
	for(ina=inc-'0';(inc=getchar())>='0'&&inc<='9';ina=(ina<<3)+(ina<<1)+inc-'0');
	return insign?-ina:ina;
}
#define mod 31011
#define N 105
#define M 1005
struct E{int u,v,w;}e[M];
int fa[N],L[M],R[M],C[M],n,m,sum,ans;
bool operator < (const E&a,const E&b) {return a.w<b.w;}
int find(int a) {return (a^fa[a])?find(fa[a]):a;}
void dfs(int x,int cur,int t) {
	if(R[x]<cur) { 
		if(t==C[x]) ++sum;
		return;
	}
	int p=find(e[cur].u),q=find(e[cur].v);
	if(p^q) {
		fa[p]=q; 
		dfs(x,cur+1,t+1); 
		fa[p]=p;fa[q]=q;
	}
	dfs(x,cur+1,t);
}
int main() {
	int i,j,cnt=0,cedge=0,p,q;
	n=geti(),m=geti(),ans=1;
	for(i=1;i<=m;++i) e[i]=(E){geti(),geti(),geti()};
	sort(e+1,e+m+1); 
	for(i=1;i<=n;++i) fa[i]=i;
	for(i=1;i<=m;++i) {
		if(e[i-1].w<e[i].w) R[cnt]=i-1,L[++cnt]=i;
		if((p=find(e[i].u))^(q=find(e[i].v)))
		  fa[p]=q,++C[cnt],++cedge;
	}R[cnt]=m;
	if(cedge<n-1) return puts("0"),0;
	for(i=1;i<=n;++i) fa[i]=i;
	for(i=1;i<=cnt;++i) {
		sum=0; dfs(i,L[i],0);
		ans=ans*sum%mod;
		for(j=L[i];j<=R[i];++j) {
			p=find(e[j].u),q=find(e[j].v);
			if(p^q) fa[p]=q;
		}
	}return printf("%d\n",ans),0;
}
