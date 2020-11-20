#include <cstdio>
int ans[100005];
int main() {
	int n,k,i,d,f,x;
	scanf("%d%d",&n,&k);
	for(d=k,x=f=i=1;i<=n&&d;++i) {
		ans[i]=x,x=x+d*f,f*=-1,--d;
	}ans[i]=x;
	for(i=k+2;i<=n;++i) ans[i]=i;
	for(i=1;i<=n;++i) printf("%d ",ans[i]);
	return 0;
}
