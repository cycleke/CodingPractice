#include <cstdio>
#include <cstring>
inline int gi() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
inline char gp() {register char c;while(c=getchar(),c<'A');return c;}
#define M 300005
#define N 100005
int f[M],val[N],d[550],ans[N];
char op[N],mark[M];
inline int gf(int u) {
	int r=u; while(f[r]^r)r=f[r];
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
inline void merge(int x,int y) {
	x=gf(x),y=gf(y);
	x<y?f[x]=y:f[y]=x;
}
inline void cmin(int&a,const int&b){if(b<a)a=b;}
int main() {
	register int n=gi(),i,j,t;
	memset(d,127,sizeof d);
	for(i=0;i<n;++i) {
		op[i]=gp(); val[i]=gi();
		if(op[i]=='A') {for(j=1;j<550;++j)cmin(d[j],val[i]%j);mark[val[i]]=1;}
		else if(val[i]<550)ans[i]=d[val[i]];
	}
	f[300001]=300001;
	for(i=300000;~i;--i)f[i]=(mark[i]?i:f[i+1]);
	for(i=n-1;~i;--i) {
		if(op[i]=='A') merge(val[i],val[i]+1);
		else if(val[i]>=550) {
			t=gf(1); ans[i]=(t^300001)?t%val[i]:(val[i]-1);
			for(j=val[i];j<300001;j+=val[i])
				cmin(ans[i],((t=gf(j))^300001)?t%val[i]:(val[i]-1));
		}
	}
	for(i=0;i<n;++i)if(op[i]=='B')printf("%d\n",ans[i]);
	return 0;
}
