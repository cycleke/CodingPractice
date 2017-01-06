#include <cstdio>
#include <algorithm>
typedef int arr[7000010];
int a[100010],n,m,q,u,v,t;
arr x,y,z;
//p=u/v;
int main() {
	register int i,mx,type,delta=0;
	int *xl,*xr,*yl,*yr,*zl,*zr;
	scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
	for(i=1;i<=n;++i)scanf("%d",a+i);
	std::sort(a+1,a+n+1);
	xl=xr=x;
	yl=yr=y;
	zl=zr=z;
	for(i=n;i;--i)*xr++=a[i];
	for(i=1;i<=m;++i) {
		mx=-2147483647;
		if(xl<xr&&mx<*xl)mx=*xl,type=1;
		if(yl<yr&&mx<*yl)mx=*yl,type=2;
		if(zl<zr&&mx<*zl)mx=*zl,type=3;
		if(type<2)++xl;
		else if(type^3)++yl;
		else ++zl;
		mx+=delta; delta+=q;
		if(i%t==0)printf(i+t>m?"%d":"%d ",mx);
		type=(long long)mx*u/v;
		*yr++=type-delta,*zr++=mx-type-delta;
	}
	puts("");
	for(i=1;i<=n+m;++i) {
		mx=-2147483647;
		if(xl<xr&&mx<*xl)mx=*xl,type=1;
		if(yl<yr&&mx<*yl)mx=*yl,type=2;
		if(zl<zr&&mx<*zl)mx=*zl,type=3;
		if(type<2)++xl;
		else if(type^3)++yl;
		else ++zl;
		if(i%t==0) printf(i+t>n+m?"%d":"%d ",mx+delta);
	}
	return 0;
}
