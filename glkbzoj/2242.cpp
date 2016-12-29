#include <map>
#include <cmath>
#include <cstdio>
using namespace std;
#define ll long long
#define ni (c<'0'|'9'<c)
inline ll geti() {
	register ll a; register char c;
	while(c=getchar(),ni);a=c-'0';
	while(c=getchar(),!ni)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
char buf[20];
template<class T>
inline void output(T a) {
	if(a==0) {puts("0"); return;}
	register char *s=buf+18;
	while(a) *s--=a%10+'0',a/=10;
	puts(s+1);
}
/*template*/
#define CANT "Orz, I cannot find x!"
inline ll pow(ll a,ll b,ll p) {
	ll ret=1; a%=p;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
void exgcd(ll a,ll b,ll &x,ll &y,ll &g) {
	if(!b) {x=1,y=0,g=a; return;}
	exgcd(b,a%b,y,x,g); y-=a/b*x;
}
map<ll,ll>mp;
int main() {
	ll y,z,p,i,j,g,x,m,inv,e; int K,T;
	T=geti(),K=geti();
	if(K==1) while(T--) {
			y=geti(),z=geti(),p=geti();
			output(pow(y,z,p));
		}
	else if(K==2) while(T--) {
			y=geti(),z=geti(),p=geti();
			exgcd(y,p,i,j,g);
			if(z%g) {puts(CANT); continue;}
			x=z/g*i,p/=g;
			output((x%p+p)%p);
		}
	else while(T--){
		y=geti(),z=geti(),p=geti(); y%=p,z%=p;
		if(!y&&!z) {puts("1"); continue;}
		if(!y) {puts(CANT); continue;}
		m=sqrt(p);inv=pow(y,p-m-1,p),e=1LL;
		mp.clear(); mp[1]=m+1;
		for(i=1;i<=m;++i) mp[e=(ll)e*y%p]=i;
		for(x=-1,i=0;i<m&&x<0;++i) {
			if(j=mp[z]) {
				if(j>m) j=0; x=i*m+j;
			} z=z*inv%p;
		}
		if(~x) output(x); else puts(CANT);
	}
	return 0;
}
