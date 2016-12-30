#include <cstdio>
inline int gi() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
typedef long long i64;
const int MaxN=1000005;
i64 s[MaxN],dp[MaxN],y[MaxN];
int que[MaxN];
#define f(x) a*(x)*(x)+b*(x)+c
inline long double gk(int i,int j) {
	return (long double)(y[i]-y[j])/(long double)(s[i]-s[j]);
}
int main() {
	register int n=gi(),a=gi(),b=gi(),c=gi(),i;
	int *l=que,*r=que; *r=0;
	for(i=1;i<=n;++i) {
		s[i]=s[i-1]+gi();
		while(l<r&&gk(*l,l[1])>2*a*s[i])++l;
		dp[i]=dp[*l]+f(s[i]-s[*l]);
		y[i]=dp[i]+a*s[i]*s[i]-b*s[i];
		while(l<r&&gk(r[-1],*r)<gk(*r,i))--r;
		*++r=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
