#include <cstdio>
#include <algorithm>
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
inline void oi(int x) {
	static char buf[13],*s;
	if(x==0){puts("0");return;}
	for(s=buf;x;x/=10)*s++=x%10+'0';
	while(buf<s)putchar(*(--s));
}
typedef int arr[7000010];
int a[100010],n,m,q,u,v,t;
arr x,y,z;
//p=u/v;
int main() {
	register int i,mx,type,delta=0;
	bool flag;
	int *xl,*xr,*yl,*yr,*zl,*zr;
	n=gi(),m=gi(),q=gi(),u=gi(),v=gi(),t=gi();
	for(i=1;i<=n;++i)a[i]=gi();
	std::sort(a+1,a+n+1);
	xl=xr=x;
	yl=yr=y;
	zl=zr=z;
	for(i=n;i;--i)*xr++=a[i];
	for(i=0,flag=false;m;--m) {
		mx=-2000000000;
		if(xl<xr&&mx<*xl)mx=*xl,type=1;
		if(yl<yr&&mx<*yl)mx=*yl,type=2;
		if(zl<zr&&mx<*zl)mx=*zl,type=3;
		if(type<2)++xl;
		else if(type^3)++yl;
		else ++zl;
		mx+=delta; delta+=q;
		if((++i)>=t) {
			if(flag)putchar(' ');else flag=true;
			oi(mx); i=0;
		}
		type=(long long)mx*u/v;
		*yr++=type-delta,*zr++=mx-type-delta;
	}
	putchar('\n');
	for(flag=false,i=0;xl<xr||yl<yr||zl<zr;) {
		mx=-2000000000;
		if(xl<xr&&mx<*xl)mx=*xl,type=1;
		if(yl<yr&&mx<*yl)mx=*yl,type=2;
		if(zl<zr&&mx<*zl)mx=*zl,type=3;
		if(type<2)++xl;
		else if(type^3)++yl;
		else ++zl;
		if(++i>=t) {
			if(flag)putchar(' ');else flag=true;
			oi(mx+delta); i=0;
		}
	}
	return 0;
}
