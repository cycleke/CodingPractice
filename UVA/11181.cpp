#include <cstdio>
int n,r,i,j,k,ca,t;
double p[22],ans[22],tmp,tot;
int main() {
	while(scanf("%d%d",&n,&r)^EOF) {
		if(!n&&!r) break;
		printf("Case %d:\n",++ca);
		for(i=0;i<n;++i) scanf("%lf",p+i),ans[i]=0.;
		if(r) for(tot=0.,i=0,k=1<<n;i<k;++i) {
			for(j=t=0;j<n;++j) ((1<<j)&i)?(++t):1;
			if(t^r) continue;
			for(tmp=1.,j=0;j<n;++j)
			  ((1<<j)&i)?(tmp*=p[j]):(tmp*=(1.-p[j]));
			tot+=tmp;
			for(j=0;j<n;++j)
			  ((1<<j)&i)?(ans[j]+=tmp):1;
		} else tot=1.;
		for(i=0;i<n;++i) printf("%.6lf\n",ans[i]/tot);
	}
	return 0;
}
