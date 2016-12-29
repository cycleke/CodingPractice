#include <cstdio>
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
    while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	    while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
		    return ina;
}
#define N 100005
int pgcd[N],bgcd[N],a[N];
inline int gcd(int a,int b){
	for(int t;b;) {
		t=a%b;
		a=b;b=t;
	}return a;
}
int main() {
	int T,q,n,i,j;
	for(T=geti();T;--T) {
		for(n=geti(),q=geti(),i=1;i<=n;++i) a[i]=geti();
		for(i=2,pgcd[1]=a[1];i<=n;++i) pgcd[i]=gcd(pgcd[i-1],a[i]);
		for(i=n-1,bgcd[n]=a[n];i;--i) bgcd[i]=gcd(bgcd[i+1],a[i]);
		while(q--) {
			i=geti(),j=geti();
			if(i>j) i^=j^=i^=j;
			if(i==1) printf("%d\n",bgcd[j+1]);
			else if(j==n) printf("%d\n",pgcd[i-1]);
			else printf("%d\n",gcd(pgcd[i-1],bgcd[j+1]));
		}
	}return 0;
}
