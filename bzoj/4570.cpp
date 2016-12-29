#include <cmath>
#include <cstdio>
#include <algorithm>
/*
  s(a,b)
  =max(atk(a,b))+max(dnf(a,b))
  =atk+a/b*dnf+dnf+b/a*atk
  (let k b/a)
  =atk+dnf+k*atk+dnf/k
  for const S=s(a,b)
  (1+k)*atk=S-(1+1/k)*dnf
  atk=S/(1+k)-(1+1/k)/(1+k)*dnf
  for const K
  to-let S/(1+K) -> min
*/
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct P{int x,y;P(int _x=0,int _y=0):x(_x),y(_y){}}p[1000005],st[1000005];
inline P operator - (const P&a,const P&b) {return P(a.x-b.x,a.y-b.y);}
inline bool operator < (const P&a,const P&b) {return (a.x^b.x)?a.x<b.x:a.y<b.y;}
inline long long operator * (const P&a,const P&b) {return (long long)a.x*b.y-(long long)a.y*b.x;}
const double oo=1e20;
inline double g(const P&a){return -sqrt((double)a.y/a.x);}
inline double gk(const P&a,const P&b) {return (a.x^b.x)?(double)(a.y-b.y)/(double)(a.x-b.x):oo;}
inline double cal(const P&a,const double&k) {return k>=0?oo:a.x+a.y-k*a.x-a.y/k;}
inline double cmin(double&a,const double&b){if(b<a)a=b;}
int main() {
	register int n=geti(),i,tp=0;
	for(i=0;i<n;++i)p[i]=(P){geti(),geti()};
	std::sort(p,p+n);
	st[++tp]=*p;
	for(i=1;i<n;++i) {
		while(1<tp&&(st[tp]-st[tp-1])*(p[i]-st[tp-1])>=0)--tp;
		st[++tp]=p[i];
	}
	if(tp<2) printf("%.4lf\n",cal(st[1],g(st[1]))),0;
	double ans=oo,k,k1,k2;
	k2=gk(st[1],st[2]),k=g(st[1]);
	if(k>=k2)cmin(ans,cal(st[1],k));
	k1=gk(st[tp-1],st[tp]),k=g(st[tp]);
	if(k<=k1)cmin(ans,cal(st[tp],k));
	cmin(ans,cal(st[tp],k1));
	for(i=2;i<tp;++i) {
		k1=gk(st[i-1],st[i]),k2=gk(st[i],st[i+1]),k=g(st[i]);
		cmin(ans,cal(st[i],k1));
		if(k<=k1&&k>=k2)cmin(ans,cal(st[i],k));
	}
	printf("%.4lf\n",ans);
	return 0;
}
