#include <cstdio>
#include <bitset>
using namespace std;
inline int rd() {
	register char c;
	while(c=getchar(),c<'0');
	return c-'0';
}
bitset<1002>a[2003];
int n,m;
inline int guass() {
	int r=0;
	for(register int i=0,j;i<n;++i) {
		for(j=i;j<m&&!a[j][i];++j);
		if(j==m)return -1;
		if(r<j)r=j;
		if(i^j)swap(a[i],a[j]);
		for(j=0;j<m;++j)
			if((i^j)&&a[j][i])a[j]^=a[i];
	}return r;
}
int main() {
	scanf("%d%d",&n,&m);
	for(register int i=0,j;i<m;++i)
		for(j=0;j<=n;++j)
			a[i][j]=rd();
	int k=guass();
	if(~k) {
		printf("%d\n",k+1);
		for(register int i=0;i<n;++i)
			puts(a[i][n]?"?y7M#":"Earth");
	}else puts("Cannot Determine");
	return 0;
}
