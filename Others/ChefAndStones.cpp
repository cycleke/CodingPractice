#include <cstdio>
int a[100005];

int main() {
	int T,n,k,b,i; long long t,mx;
	for(scanf("%d",&T);T;--T) {
		for(scanf("%d%d",&n,&k),mx=i=0;i<n;++i) scanf("%d",a+i);
		for(i=0;i<n;++i) {
			scanf("%d",&b);
			t=(long long)k/a[i]*b,(mx<t)?mx=t:1;
		}printf("%lld\n",mx);
	}return 0;
}
