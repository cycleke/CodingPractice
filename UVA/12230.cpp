#include <cstdio>
int main() {
	int n,ca=0; double d,p,l,v;
	while(scanf("%d%lf",&n,&d)^EOF) {
		if(n==0&&d==0.) break;
		while(n--) scanf("%lf%lf%lf",&p,&l,&v), d=d-l+l*2/v;
		printf("Case %d: %.3lf\n\n",++ca,d);
	} return 0;
}
