#include <cstdio>
#include <cstring>
#define N 505
int a[N],b[N],f[N],n,m;
int main() {
	int i,j,T,mx,ans;
	for(scanf("%d",&T);T--;) {
		for(scanf("%d",&n),i=1;i<=n;++i)
			scanf("%d",a+i);
		for(scanf("%d",&m),i=1;i<=m;++i)
			scanf("%d",b+i),f[i]=0;
		for(i=1;i<=n;++i) {
			mx=0;
			for(j=1;j<=m;++j)
				if(a[i]>b[j]) (mx<f[j])?mx=f[j]:1;
				else if(a[i]>=b[j]) f[j]=mx+1;
		}
		for(ans=0,i=1;i<=m;++i) (ans<f[i])?ans=f[i]:1;
		printf("%d\n",ans); T?puts(""),0:0;
	}return 0;
}
