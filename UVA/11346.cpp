#include <cmath>
#include <cstdio>
int main() {
	int t; double a,b,s,m,ans;
	for(scanf("%d",&t);t;--t) {
		scanf("%lf%lf%lf",&a,&b,&s);
		if(s>a*b) puts("0.000000%");
		else if(s<1e-9) puts("100.000000%");
		else {
			m=a*b; ans=(m-s-s*log(m/s))/m;
			printf("%.6lf%%\n",ans*100.);
		}
	}return 0;
}
