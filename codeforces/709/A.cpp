#include <cstdio>
int main() {
	int n,b,d,a,cur=0,cnt=0;
	scanf("%d%d%d",&n,&b,&d);
	while(n--) {
		scanf("%d",&a);
		if(a>b) continue;
		if((cur+=a)>d) cur=0,++cnt;
	}return printf("%d\n",cnt),0;
}
