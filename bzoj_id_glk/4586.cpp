#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
//Input
int ina; char inc,inb[1<<16],*ine=inb,*ins=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
const int N=100000,M=N*10,MS=N*20+1;
int n,x,y,z,rty[MS];
ll re1[MS],re2[MS];
vector<int>row[MS];
inline void dp(vector<int>&v,ll *res) {
	int m=v.size(),i=-2,j; ll ci=0,cj=0,cl=1LL<<60;
	for(j=1;j<m;j+=2) {
		if(j>1) cj+=z*abs(v[j-2]-v[j-1]),cl+=z*abs(v[j-2]-v[j-1]);
		while(i+2<j&&x+y<=z*abs(v[j]-v[i+2])) {
			if(i+=2) ci+=z*abs(v[i]-v[i-1]);
			cl=min(cl,x+y+cj-ci+(i?res[i-1]:0));
		}
		res[j]=min(cl,z*abs(v[j]-v[j-1])+(1<j?res[j-2]:0));
	}
}
ll solve(vector<int>&v,int ec) {
	int m=v.size(); ll be;
	if(m<2) return m?ec:0;
	dp(v,re1);
	if(m&1) {
		reverse(v.begin(),v.end());
		dp(v,re2);
		reverse(re2,re2+m);
		be=ec+min(re1[m-2],re2[1]);
		for(int i=2;i<m-2;i+=2) be=min(be,re1[i-1]+ec+re2[i+1]);
	} else be=re1[m-1];
	return be;
}
int main() {
	n=geti(),x=geti(),y=geti(),z=geti();
	int a,b,m,d;
	for(int ld=0,lev=M,i=0;i<n;++i) {
		a=geti(),b=geti();
		d=(a>=b)?1:-1;
		m=abs(a-b);
		while(m--) {
			if(d==ld) lev+=d;
			if(!rty[lev]) rty[lev]=d;
			row[lev].push_back(i);
			ld=d;
		}
	}
	ll ans=0;
	for(int i=0;i<MS;++i)
	  ans+=solve(row[i],rty[i]>0?y:x);
	return printf("%lld\n",ans),0;
}
