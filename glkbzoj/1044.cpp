#include <cstdio>
#include <cstring>
#define N 50005
#define mod 10007
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define noti(a) (a<'0'||'9'<a)
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while(inc=getc(),noti(inc));ina=inc-'0';
	while(inc=getc(),!noti(inc))ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
int n,m,L[N],dp[N],sd[N],sum[N];
bool check(int mid) {
	int tot=0,s=0;
	for(int i=1;i<=n;++i) {
		if(s+L[i]>mid) {s=L[i];if(++tot>m)return false;}
		else s+=L[i];
	}return true;
}
inline void mov(int&a,int b) {
	for(a=b;a>=mod;a-=mod);
	while(a<0)a+=mod;
}
int main() {
	int l=-1,r=0,mid,ans;
	n=geti(),m=geti();
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+(L[i]=geti()),l<L[i]?l=L[i]:1;
	for(r=sum[n];l<=r;){
		if(check(mid=l+r>>1)) r=(ans=mid)-1;
		else l=mid+1;
	}
	for(int i=0;i<=n;++i)
		if(ans>=sum[i]) dp[i]=1; else break;
	for(int j=1;j<=m;++j) {
		int k=0;sd[0]=dp[0];
		for(int i=1;i<=n;++i) mov(sd[i],dp[i]+sd[i-1]);
		for(int i=1;i<=n;++i) {
			while(k<i&&sum[i]-sum[k]>ans)++k;
			mov(dp[i],sd[i-1]-sd[k-1]);
		}
	}return printf("%d %d\n",ans,dp[n]),0;
}
