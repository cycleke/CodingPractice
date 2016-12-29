#include <cstdio>
int main() {
	int a,b,c;
	while(scanf("%d%d%d",&a,&b,&c)^EOF)
	  if(a^c)printf("%.5lf\n",(a*b+b*(b-1.))/((a+b)*(a+b-c-1.)));
	  else puts("1.00000");
	return 0;
}
