#include <cstdio>
int main() {
	int p,q,r,s,i; double ans;
	while(scanf("%d%d%d%d",&p,&q,&r,&s)^EOF) {
		(p-q<q)?q=p-q:1,(r-s<s)?s=r-s:1;
		ans=1.;
		for(i=1;i<=q||i<=s;++i) {
			(i<=q)?(ans=ans*(p-i+1)/i):1;
			(i<=s)?(ans=ans*i/(r-i+1)):1;
		}
		printf("%.5lf\n",ans);
	}
	return 0;
}
