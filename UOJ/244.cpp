#include <cstdio>
typedef long long i64,arr[100005];
inline void cmin(i64&a,i64 b) {if(b<a)a=b;}
arr a,f,s;
int main() {
	int n,bestchoice=0;
	i64 ans=1e18,t1,t2;
	scanf("%d",&n);
	for(int i=n;~i;--i)scanf("%lld",a+i),s[i]=s[i+1]+a[i];
	f[0]=a[0];
	for(int i=1;i<=n;++i) {
		t1=f[bestchoice]+(i-bestchoice)*a[bestchoice]+s[bestchoice+1]-s[i+1];
		t2=f[i-1]+a[i-1]+a[i];
		if(t2<t1) t1=t2,bestchoice=i-1;
		f[i]=t1;
	}
	for(int i=n;~i;--i)cmin(ans,f[i]*2+a[i]*((n-i)*4-1));
	printf("%lld\n",ans);
	return 0;
}
