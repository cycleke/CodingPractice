#include <cmath>
#include <cstdio>
#define N 105
#define M 1000010
int a[N],pri[M],cnp,e[M],id[M],cnop;
bool vis[M];
void pre() {
	for(int i=2,j;i<M;++i) {
		if(!vis[i]) id[i]=cnp,pri[cnp++]=i;
		for(j=0;j<cnp&&(long long)pri[j]*i<M;++j) {
			vis[pri[j]*i]=true;
			if(i%pri[j]==0) break;
		}
	}
}
void fac(int x) {
	if(id[x]) {++e[id[x]]; return;}
	int ha=sqrt(x+0.5),i,t;
	for(i=0,t=x;i<cnp&&pri[i]<=ha&&t>1;++i)
	  if(t%pri[i]==0) for(;t%pri[i]==0;t/=pri[i]) ++e[i];
	if(t>1) ++e[id[t]];
}
int pow(int a,int b) {
	int ret=1;
	for(;b;b>>=1) {
		if(b&1) ret*=a; a*=a;
	}return ret;
}

void cal(int x) {
	int i,j,t=x;
	for(i=0;i<cnp;++i) {
		for(j=0;t%pri[i]==0;t/=pri[i]) ++j;
		if(j<e[i]) cnop+=e[i]-j;
	}
}

int main() {
	int n,i,j,k,gcd=1; pre();
	for(scanf("%d",&n),i=0;i<n;++i) {
		scanf("%d",a+i); fac(a[i]);
	}
	if(n==1) return printf("%d 0\n",a[0]),0;
	for(i=0;i<cnp;++i) gcd*=pow(pri[i],e[i]/=n);
	for(cnop=i=0;i<n;++i) cal(a[i]);
	return printf("%d %d\n",gcd,cnop),0;
}
