#include <cstdio>
inline void cmin(int&a,int b){b<a?a=b:1;}
int main() {
	int n,m,x=0x7f7f7f7f,l,r;
	scanf("%d%d",&n,&m);
	while(m--) {
		scanf("%d%d",&l,&r);
		cmin(x,r-l+1);
	}
	printf("%d\n",x);
	for(int i=0;i<n;++i) printf("%d ",i%x);
	return 0;
}
