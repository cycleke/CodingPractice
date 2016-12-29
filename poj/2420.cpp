#include <cmath>
#include <cstdio>
#define eps 1e-9
#define delta 0.98
double x[105],y[105];
int n;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
inline double dis(int a,int b) {
	return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
inline double sumdis() {
	double ret=0;
	for(int i=1;i<=n;++i)
		ret+=dis(0,i);
	return ret;
}
int main() {
	while(scanf("%d",&n)^EOF) {
		for(int i=1;i<=n;++i)
			scanf("%lf%lf",x+i,y+i);
		double _x=x[1],_y=y[1];
		double t=100,an=1e99,_t;
		bool flag;
		while(eps<t) {
			flag=1;
			while(flag) {
				flag=0;
				for(int i=0;i<4;++i) {
					*x=_x+dx[i]*t;
					*y=_y+dy[i]*t;
					_t=sumdis();
					if(_t<an) {
						an=_t;
						_x=*x,_y=*y;
						flag=1;
					}
				}
			}
			t*=delta;
		}
		printf("%.0lf\n",an);
	}
	return 0;
}
