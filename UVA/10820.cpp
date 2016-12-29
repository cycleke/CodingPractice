#include <cstdio>
const int N=50005;
int phi[N];

int main() {
	int n,ans,i,j;
	for(phi[1]=1,i=2;i<N;++i)
	  if(!phi[i]) for(j=i;j<N;j+=i) {
		  phi[j]?1:phi[j]=j;
		  phi[j]=phi[j]/i*(i-1);
	  }
	while(scanf("%d",&n)!=EOF&&n) {
		for(ans=1,i=2;i<=n;++i) 
		  ans+=phi[i]<<1;
		printf("%d\n",ans);
	}
	return 0;
}
