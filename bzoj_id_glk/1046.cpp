#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 10005
int a[N],dp[N],d[N];
int main() {
#ifndef ONLINE_JUDGE
	freopen("T.in","r",stdin);
#endif
	int n,i,j,k,len,m,pre,l,r,mid,res;
	for(scanf("%d",&n),i=n;i;--i) scanf("%d",a+i),d[i]=-0x7f7f7f7f;
	len=1,d[0]=0x7f7f7f7f,d[1]=a[1],dp[1]=1;
	for(i=2;i<=n;++i) {
		l=0,r=len+1;
		while(l<=r) {
			mid=l+r>>1;
			if(d[mid]>a[i]) l=(res=mid)+1;
			else r=mid-1;
		}(len<res+1)?len=res+1:1;
		d[res+1]<a[i]?d[res+1]=a[i]:1;
		dp[i]=res+1;
	}
	for(i=1,j=n>>1;i<=j;++i)
		a[i]^=a[n+1-i]^=a[i]^=a[n+1-i],dp[i]^=dp[n+1-i]^=dp[i]^=dp[n+1-i];
	for(scanf("%d",&m);m;--m) {
		scanf("%d",&l);
		if(len<l) {puts("Impossible"); continue;}
		for(i=1,pre=-0x7f7f7f7f;i<=n&&l;++i)
			if(dp[i]>=l&&a[i]>pre) printf("%d%c",pre=a[i],(--l)?' ':'\n');
	}return 0;
}
