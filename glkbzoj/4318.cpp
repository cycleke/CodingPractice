#include <cstdio>
#define ld long double
int main() {
	int n; ld res=0,el1=0,el2=0,p;
	for(scanf("%d",&n);n;--n) {
		scanf("%Lf",&p);
		res+=p*(3*el2+3*el1+1);
		el2=p*(el2+2*el1+1);
		el1=p*(el1+1);
	}return printf("%.1Lf\n",res),0;
}
