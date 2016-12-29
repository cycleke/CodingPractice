#include <cstdio>
#include <cstring>
#define N 30005
const int mo=1000000097;
char s[N];
int ha[N],p[N],f[N],g[N];
inline int hash(int l,int r){return(ha[r]-1LL*ha[l]*p[r-l]%mo+mo)%mo;}
inline int min(int a,int b){return a<b?a:b;}
int main() {
	register int i,j,n,l,r,x,y,m;
	int t;
	register long long ans;
	for(*p=i=1;i^N;++i)p[i]=p[i-1]*223LL%mo;
	for(scanf("%d",&t);t;--t) {
		scanf("%s",s+1);
		n=strlen(s+1);
		for(i=1;i<=n;++i)
			f[i]=g[i]=0,ha[i]=(ha[i-1]*223LL+s[i])%mo;
		for(i=1;(i<<1)<=n;++i)
			for(j=1;j+i<=n;j+=i) {
				l=0,r=min(i,j);
				while(l^r)
					if(m=(l+r+1>>1),hash(j+i-m,j+i)==hash(j-m,j))
						l=m;
					else r=m-1;
				x=j-l+1;
				l=0,r=min(i-1,n-j-i);
				while(l^r)
					if(m=(l+r+1>>1),hash(j+i,j+i+m)==hash(j,j+m))
						l=m;
					else r=m-1;
				y=j+l+1;
				if(x+i<=y) {
					++f[x],--f[y-i+1];
					++g[x+i*2-1],--g[y+i];
				}
			}
		ans=0;
		for(i=1;i<=n;++i) {
			f[i]+=f[i-1];
			g[i]+=g[i-1];
			ans+=f[i]*g[i-1];
		}
		printf("%lld\n",ans);
	}
}
