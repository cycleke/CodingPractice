#include <cstdio>
int main() {
	int n,i; long long res=0;
	for(scanf("%d",&n),i=1;i<=n;++i)
		res+=n/i;
	return printf("%lld\n",res);
}
