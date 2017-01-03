#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const double eps=1e-9;
typedef pair<double,double>point;
point p[500];
double disc(const point&a,const point&b) {
	return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}
point center(const point&a,const point&b,const point&c) {
	point o;
	double a1=b.first-a.first,b1=b.second-a.second,c1=(a1*a1+b1*b1)/2;
	double a2=c.first-a.first,b2=c.second-a.second,c2=(a2*a2+b2*b2)/2;
	double d = a1*b2 - a2*b1;
	o.first = a.first + (c1 * b2 - c2 * b1) / d;
	o.second = a.second + (a1 * c2 - a2 * c1) / d;
	return o;
}
void min_cover_circle(point*p,int n,point&o,double&r) {
	random_shuffle(p,p+n);
	o=p[0]; r=0;
	for(int i=1;i<n;++i)
		if(disc(p[i],o) > r + eps) {
			o=p[i]; r=0;
			for(int j=0;j<i;++j)
				if(disc(p[j],o) > r + eps) {
					o=make_pair((p[i].first+p[j].first)/2,(p[i].second+p[j].second)/2);
					r=disc(p[j],o);
					for(int k=0;k<j;++k)
						if(disc(p[k],o) > r +eps) {
							o = center(p[i],p[j],p[k]);
							r = disc(p[i],o);
						}
				}
		}
}
int main() {
	int n;
	point o;
	double r;
	while (scanf("%d",&n)!=EOF && n) {
		for (int i=0;i<n;++i) {
			double x,y;
			scanf("%lf%lf",&x,&y);
			p[i]=make_pair(x,y);
		}
		min_cover_circle(p,n,o,r);
		printf("%.2lf %.2lf %.2lf\n",o.first,o.second,r);
	}
	return 0;
}
