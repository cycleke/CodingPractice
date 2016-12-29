#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50005
#define ll long long
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9')ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
struct D {
	int x,y;
	bool operator < (const D&a) const {
		return (x^a.x)?x>a.x:y>a.y;
	}
}p[N];
int n,q[N],a[N],b[N];
ll f[N];
#define X(i,j) (a[i]-a[j])
#define Y(i,j) (f[(j)-1]-f[(i)-1])
int main() {
	int i,j,m,l,r,t;
	for(n=geti(),i=0;i<n;++i) p[i].x=geti(),p[i].y=geti();
	sort(p,p+n);
	for(m=t=i=0;i<n;++i)
		if(t<p[i].y) a[++m]=p[i].x,b[m]=p[i].y,t=p[i].y;
	q[l=r=1]=1; f[1]=(ll)a[1]*b[1];
	for(i=2;i<=m;++i) {
		while(l<r&&Y(q[l],q[l+1])<(ll)b[i]*X(q[l],q[l+1])) ++l;
		j=q[l];
		f[i]=min(f[j-1]+(ll)a[j]*b[i],f[i-1]+(ll)a[i]*b[i]);
		while(l<r&&Y(q[r-1],q[r])*X(q[r],i)>=Y(q[r],i)*X(q[r-1],q[r])) --r;
		q[++r]=i;
	}return printf("%lld\n",f[m]),0;
}
