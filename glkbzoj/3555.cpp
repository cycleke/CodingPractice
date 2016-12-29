#include <cstdio>
#include <cstring>
#include <algorithm>
typedef unsigned long long ul;
char ts[203];
ul h1[30003][203],h2[30003][203],r[30003];
int main() {
	register int n,l,ans=0,i,j,k,cnt; register ul *f;
	register char *s;
	scanf("%d%d%d",&n,&l,&k);
	for(i=0;i<n;++i) {
		scanf("%s",ts+1);
		for(s=ts+1,j=1;j<=l;++j) h1[i][j]=h1[i][j-1]*255+*s++;
		for(s=ts+l,j=l;j;--j) h2[i][j]=h2[i][j+1]*307+*s--;
	}
	for(k=1;k<=l;++k) {
		for(f=r,i=0;i<n;++i) *f++=h1[i][k-1]*137+h2[i][k+1]*271;
		std::sort(r,f); cnt=1;
		for(f=r+1,i=1;i<n;++i,++f)
			if(*f^*(f-1)) cnt=1;
			else ans+=cnt++;
	}
	return printf("%d",ans),0;
}
