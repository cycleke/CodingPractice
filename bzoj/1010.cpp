#include <cstdio>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 50005
long long g[N],dp[N],C; int q[N];
inline long long S(int i,int j){return (g[i]-g[j])<<1;}
inline long long G(int i,int j){return dp[i]-dp[j]+(g[i]-g[j])*(g[i]+g[j]+(C<<1));}
int main() {
	register int n=geti(),i,j,l=1,r=1;
	C=geti()+1;
	register long long s=0;
	q[1]=0;
	for(i=1;i<=n;++i) {
		s+=geti(); g[i]=s+i;
		while(l<r&&G(q[l+1],q[l])<=S(q[l+1],q[l])*g[i])++l;
		j=q[l];
		dp[i]=dp[j]+(g[i]-g[j]-C)*(g[i]-g[j]-C);
		while(l<r&&G(i,q[r])*S(q[r],q[r-1])<=G(q[r],q[r-1])*S(i,q[r]))--r;
		q[++r]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
