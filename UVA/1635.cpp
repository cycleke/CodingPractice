#include <cmath>
#include <cstdio>
#include <cstring>
const int N=100000+10;
int pri[110],fac[110],ans[N],cnt,cntpri,tp;

int main() {
	int n,m,i,j,k,a,b;
	while(scanf("%d%d",&n,&m)!=EOF) {
		tp=cntpri=0; k=sqrt(m);
		for(i=2;i<=k&&m>1;++i)
		  if(m%i==0) {
			  fac[cntpri]=0;
			  while(m%i==0) ++fac[cntpri],m/=i;
			  pri[cntpri]=i; ++cntpri;
		  }
		if(m>1) {pri[cntpri]=m;fac[cntpri]=1; ++cntpri;}
		cnt=cntpri;
		for(i=1;i<n;++i) {
			a=n-i,b=i;
			for(j=0;j<cntpri;++j) {
				while(a%pri[j]==0) {
					a/=pri[j]; --fac[j];
					if(fac[j]==0) --cnt;
				}
				while(b%pri[j]==0) {
					b/=pri[j]; ++fac[j];
					if(fac[j]==1) ++cnt;
				}
			}
			if(cnt==0) ans[tp++]=i+1;

		}
		printf("%d\n",tp);
		if(tp==0) {puts(""); continue;}
		for(i=0;i<tp;++i)
		  printf("%d%c",ans[i],i==tp-1?'\n':' ');
	}
	return 0;
}
