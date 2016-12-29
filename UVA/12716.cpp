#include <cstdio>
const int N=3e7+10;
int pr[N];
int main() {
	int n,i,j;
	for(i=1;i<N;++i) {
		for(j=i<<1;j<N;j+=i)
		  (((j-i)^j)==i)?++pr[j]:1;
		pr[i]+=pr[i-1];
	}
	for(scanf("%d",&i),j=1;j<=i;++j) {
		scanf("%d",&n);
		printf("Case %d: %d\n",j,pr[n]);
	}
	return 0;
}
