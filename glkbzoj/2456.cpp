#include <cstdio>
#define geti(x) {\
	for(;(c=getchar())<'0'||c>'9';);\
	for(x=c-'0';(c=getchar())>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0');\
}
int main() {
	int n,zs,cnt=0,a; char c;
	geti(n);
	while(n--) {
		geti(a);
		(cnt==0)?zs=a:1;
		(zs^a)?--cnt:++cnt;
	}return printf("%d\n",zs),0;
}
