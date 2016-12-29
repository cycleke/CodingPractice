#include <cstdio>
#define N 10000010
#define ll long long
int fac[N],e[N],inv[N],pri[700010],cntpri,T,n,m,mod;
bool vis[N];
void pre() {
	int i,j;
	for(i=2,cntpri=0;i<N;++i) {
		if(!vis[i]) pri[cntpri++]=i;
		for(j=0;j<cntpri&&(ll)i*pri[j]<N;++j) {
			vis[i*pri[j]]=true;
			if(i%pri[j]==0) break;
		}
	}
	fac[1]=e[1]=inv[1]=1;
	for(i=2;i<N;++i) {
		fac[i]=(ll)fac[i-1]*i%mod;
		inv[i]=((ll)mod-mod/i)*(ll)inv[mod%i]%mod;
		if(!vis[i]) e[i]=(ll)e[i-1]*(i-1LL)%mod*inv[i%mod]%mod;
		else e[i]=e[i-1];
	}
}
int main() {
	for(scanf("%d%d",&T,&mod),pre();T;--T) {
		scanf("%d%d",&n,&m);
		printf("%d\n",(int)((ll)fac[n]*(ll)e[m]%mod));
	}
	return 0;
}
