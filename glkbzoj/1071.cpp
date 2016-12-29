#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 5010
#define ll long long
ll n,a,b,c,Max,Min;
//Input
ll ina; bool insign; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline ll geti() {
	for(insign=false;(inc=getc())<'0'||inc>'9';insign|=inc=='-');
	for(ina=inc-'0';(inc=getc())>='0'&&inc<='9';ina=(ina<<3)+(ina<<1)+inc-'0');
	return insign?-ina:ina;
}
struct D{
	ll s,h,sum;
	D Read() {
		h=geti();s=geti();
		sum=a*h+b*s;
		return *this;
	}
}ch[N],csum[N];
bool cmph(const D &x,const D &y) {return x.h<y.h;}
bool cmpsum(const D &x, const D &y) {return x.sum<y.sum;}
bool checkh(const int &i) {return ch[i].s<=Max&&ch[i].s>=Min;}
bool checksum(const int &i) {return csum[i].s<=Max&&csum[i].s>=Min;}
int main() {
	int i,j,k,ans=0,cnt=0,l,r; ll t;
	n=geti();a=geti();b=geti();c=geti();
	for(i=0;i<n;++i) ch[i]=csum[i].Read();
	sort(ch,ch+n,cmph); sort(csum,csum+n,cmpsum);
	for(i=0;i<n;++i) {
		l=r=-1,cnt=0;
		Min=ch[i].s; Max=Min+c/b;
		for(j=0;j<n;++j) {
			t=a*ch[j].h+b*ch[i].s+c;
			while((r+1)<n&&csum[r+1].sum<=t)
			  cnt+=checksum(++r);
			while((l+1)<n&&ch[l+1].h<ch[j].h)
			  cnt-=checkh(++l);
			(ans<cnt)?ans=cnt:1;
		}
	}return printf("%d\n",ans),0;
}
