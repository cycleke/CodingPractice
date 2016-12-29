#include <cstdio>
int main() {
	int a,x,y;
	scanf("%d%d%d",&a,&x,&y);
	if(y<=0) return puts("-1"),0;
	int t=y/a;
	if(y%a==0) return puts("-1"),0;
	if(!t) {
		if(x*2>=a||x*2<=-a) puts("-1");
		else puts("1");
	} else {
		int s;
		if(t&1) {
			if(x*2>=a||x*2<=-a) s=-1; 
			else s=2+(t>>1)*3;
		} else {
			if(x>=a||x<=-a||x==0) s=-1;
			else s=1+(t>>1)*3-(x<0);
		}
		printf("%d\n",s);
	}return 0;
}
