#include <cstdio>
#include <cstring>
#include <algorithm>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define mo 31011
struct E{int u,v,w;}e[1002];
inline bool operator < (const E&a,const E&b){return a.w<b.w;}
int L[1002],R[1002],C[1002],f[102],sum,x;
inline int gf(int u) {
	while(f[u]^u)u=f[u];
	return u;
}
void dfs(int cur,int t) {
	if(R[x]<cur){sum+=t==C[x];return;}
	int p=gf(e[cur].u),q=gf(e[cur].v);
	if(p^q){
		f[p]=q;
		dfs(cur+1,t+1);
		f[p]=p,f[q]=q;
	}
	dfs(cur+1,t);
}
int main() {
	register int i,cnt=0,cedge=0,p,q;
	register int n=geti(),m=geti(),ans=1;
	for(i=0;i<m;++i)e[i].u=geti(),e[i].v=geti(),e[i].w=geti();
	std::sort(e,e+m);
	for(i=1;i<=n;++i)f[i]=i;
	for(i=0;i<m;++i) {
		if(e[i-1].w<e[i].w)R[cnt]=i-1,R[++cnt]=i;
		if((p=gf(e[i].u))^(q=gf(e[i].v)))
			f[p]=q,++C[cnt],++cedge;
	}R[cnt]=m;
	if(cedge<n-1)return puts("0"),0;
	for(i=1;i<=n;++i)f[i]=i;
	for(x=1;x<=cnt;++x) {
		sum=0; dfs(L[x],0);
		ans=ans*sum%mo;
		for(i=L[x];i<=R[x];++i)
			if((p=gf(e[i].u))^(q=gf(e[i].v)))f[p]=q;
	}
	return printf("%d\n",ans),0;
}
