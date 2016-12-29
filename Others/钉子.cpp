#include <cmath>
#include <cstdio>
#include <cstring>
const double pi=acos(-1.0);
double x[105],y[105];
int main() {
	double res=0,r; int n;
	scanf("%d%lf",&n,&r);
	for(int i=0;i<n;++i) scanf("%lf%lf",x+i,y+i);
	--n;
	for(int i=0;i<n;++i) 
	  res+=sqrt((x[i]-x[i+1])*(x[i]-x[i+1])+(y[i]-y[i+1])*(y[i]-y[i+1]));
	res+=sqrt((x[n]-x[0])*(x[n]-x[0])+(y[n]-y[0])*(y[n]-y[0]));
	res+=2.0*r*pi;
	printf("%.2lf\n",res);
	return 0;
}
