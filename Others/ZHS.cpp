#include <cstdio>
int fac[]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800};
int main() {
	int n; scanf("%d",&n);
	return printf("%d\n",fac[n]/2),0;
}
