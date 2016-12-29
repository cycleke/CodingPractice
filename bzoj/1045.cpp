#include <cstdio>
#include <algorithm>
char inb[1<<17],*ins=inb,*ine=inb;
#define getc ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<17,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	register int a; register char c;
	while(c=getc,c<'0');a=c-'0';
	while(c=getc,'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 1000000
int a[N],b[N];
int main() {
	register int n=geti(),i;
	register long long avg=0;
	for(i=0;i^n;++i)avg+=(a[i]=geti());
	avg/=n;
	for(i=1;i^n;++i)b[i]=b[i-1]+a[i]-avg;
	std::sort(b,b+n);
	i=b[n>>1];avg=0;
	for(--n;~n;--n)avg+=(b[n]<i?i-b[n]:b[n]-i);
	printf("%lld\n",avg);
	return 0;
}
