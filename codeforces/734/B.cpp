#include <cstdio>
inline void cmax(long long&a,long long b){a<b?a=b:1;}
inline int min(int a,int b){return a<b?a:b;}
int main() {
	int k2,k3,k5,k6;
	long long ans=0;
	scanf("%d%d%d%d",&k2,&k3,&k5,&k6);
	for(int i=0;i<=k2;++i) {
		int c32=min(k3,i);
		int c256=min(k2-i,min(k5,k6));
		cmax(ans,32LL*c32+256LL*c256);
	}
	printf("%I64d\n",ans);
	return 0;
}
