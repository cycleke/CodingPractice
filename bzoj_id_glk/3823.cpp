#include <cstdio>
#define N 10000005
#define ll long long
int n,p,i,j,k,inv[N],a[N];
ll ans,x,y; char e[N];
int main() {
	if(scanf("%d%d",&n,&p),p==2) return puts("1"),0;
	for(inv[1]=a[1]=1,i=2;i<=n;++i)
	  if(i%p) {
		if((a[i]=i)>=p) inv[i]=inv[i%p];
		else inv[i]=-(ll)inv[p%i]*(p/i)%p;
		while(inv[i]<0) inv[i]+=p;
	  } else {
		  for(j=i;j%p==0;j/=p) ++e[i];
		  inv[i]=inv[a[i]=j];
	  }
	for(ans=x=i=1;i<=n;++i) {
		x=x*a[n-i+1]%p*2%p*inv[i]%p; y+=e[n-i+1]-e[i];
		if(!y) ans^=x;
	}
	return printf("%lld\n",ans), 0;
} 
