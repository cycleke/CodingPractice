#include <cstdio>
int main() {
	int n,k,i,j;
	scanf("%d%d",&n,&k);
	if(k>=n) return puts("-1"),0;
	printf("%d",j=n-k);
	for(i=1;i<j;++i) printf(" %d",i);
	for(i=j+1;i<=n;++i) printf(" %d",i);
	return 0;
}
