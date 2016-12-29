#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=500010,Q=2000010;
//Input && Output
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
#define geti(a) {\
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';\
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';\
	a=ina;\
}
char oub[1<<24],*ous=oub,*oue=oub+(1<<24),ousta[20]; int outo;
#define putc(a) ((ous==oue)?(fwrite(oub,1,1<<24,stdout),ous=oub,1):1,*ous++=a)
#define output() fwrite(oub,1,ous-oub,stdout)
#define outi(x) {\
	if(!x) putc('0'); else {\
		for(outo=0;x;ousta[++outo]=x%10+'0',x/=10);\
		for(;outo;putc(ousta[outo--]));\
	}putc('\n');\
}
unsigned int ha[N],p[N],fac[N];
int i,j,l,r,n,q,x,y,z,t;
char s[N];
#define gethash(a,b) (ha[b]-ha[a-1]*p[b-(a)+1])
int main() {
	freopen("seq.in","r",stdin); freopen("seq.out","w",stdout);
	for(scanf("%d\n",&n),gets(s+1),p[0]=i=1;i<=n;++i)
	  if(ha[i]=ha[i-1]*137+s[i],p[i]=p[i-1]*137,fac[i]==0&&1<i)
		for(j=i;j<=n;j+=i) fac[j]=i;
	geti(q);
	for(;q;--q) {
		geti(l);geti(r);
		for(x=y=r-l+1;z=fac[x];) {
			while(y%z==0&&(t=y/z,gethash(l+t,r)==gethash(l,r-t)))y=t;
			while(x%z==0)x/=z;
		}
		outi(y);
	}
	output();
	return 0;
}
