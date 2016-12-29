#include <cmath>
#include <cstdio>
#include <cstring>
#define N 10000005
#define ll long long
int ina; char inc;
inline int geti() {
	while((inc=getchar())<'0'||inc>'9');ina=inc-'0';
	while((inc=getchar())>='0'&&inc<='9')ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
int phi[N],f[N];
int getphi(int i) {
	if(phi[i]) return phi[i];
	int t=sqrt(i),j,res=i;
	for(j=2;j<=t;++j) 
	if(i%j==0){
		res=res/j*(j-1);
		while(i%j==0) i/=j;
	}(i>1)?res=res/i*(i-1):1;
	return phi[i]=res;
}
int mod_pow(ll a,ll b,int p) {
	ll ret=1LL; a%=p;
	for(;b;b>>=1,a=a*a%p) (b&1)?ret=ret*a%p:1;
	return ret;
}
int cal(int p) {
	if(~f[p]) return f[p];
	int k=0,ph=getphi(p),res,t=p;
	while(~t&1) t>>=1,++k;
	res=cal(ph); res=(res+ph-k%ph)%ph;
	res=mod_pow(2,res,t)%t;
	return f[p]=(res<<k);
}
int main() {
	memset(f,-1,sizeof f); f[1]=0;
	for(int i=geti();i;--i) printf("%d\n",cal(geti()));
	return 0;
}
