#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int f[18][100005]; bool vis[100005];
int gf(int k,int u){return (f[k][u]^u)?f[k][u]=gf(k,f[k][u]):u;}
void Union(int k,int u,int v) {
	if(gf(k,u)^gf(k,v)) {
		f[k][f[k][u]]=f[k][v];
		if(!k--) return;
		Union(k,u,v); Union(k,u+(1<<k),v+(1<<k));
	}
}
int main() {
	register int n=geti(),m=geti(),a,b,c,d,i,j;
	for(a=0;(1<<a)<=n;++a)
		for(b=1;b+(1<<a)-1<=n;++b)
			f[a][b]=b;
	while(m--) {
		a=geti(),b=geti(),c=geti(),d=geti();
		for(i=0,j=b-a+1;(1<<i+1)<=j;++i);j=1<<i;
		Union(i,a,c); Union(i,b-j+1,d-j+1);
	}
	a=9;vis[gf(0,1)]=true;
	m=1e9+7;
	for(i=2;i<=n;++i)if(!vis[gf(0,i)])vis[gf(0,i)]=true,a=a*10LL%m;
	printf("%d\n",a); return 0;
}
