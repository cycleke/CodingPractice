#include <cmath>
#include <cstdio>
#include <cstring>
#define ll long long
ll n,m;
ll a[3][3],b[3][3],c[3][3];

void mul(ll x[3][3],ll y[3][3]) {
	int i,j,k;
	for(i=0;i<3;++i)
	  for(j=0;j<3;++j)
		for(c[i][j]=k=0;k<3;++k)
		  c[i][j]=(c[i][j]+x[i][k]*y[k][j])%m;
	for(i=0;i<3;++i)
	  for(j=0;j<3;++j)
		x[i][j]=c[i][j];
}

int main() {
	scanf("%lld%lld",&n,&m);
	a[0][0]=a[1][1]=a[2][2]=1LL;
	ll t,g;
	for(t=10LL,g;t<=n;t*=10LL) {
		b[0][0]=t%m;
		b[1][0]=b[1][1]=b[2][0]=b[2][1]=b[2][2]=1LL;
		for(g=(t-1)-t/10+1;g;g>>=1) {
			(g&1)?mul(a,b),1:1; mul(b,b);
		}
	}
	b[0][0]=t%m;
	b[1][0]=b[1][1]=b[2][0]=b[2][1]=b[2][2]=1LL;
	for(g=n-t/10+1;g;g>>=1) {
		(g&1)?mul(a,b),1:1; mul(b,b);
	}return printf("%lld\n",a[2][0]),0;
}
