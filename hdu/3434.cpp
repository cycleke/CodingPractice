#include <cstdio>
long long max(const long long&a,const long long&b) {return a<b?b:a;}
int abs(const int&a) {return a<0?-a:a;}
int main() {
	int _,n,i,j,__,last,current,begin;
	long long c1,c2;
	scanf("%d",&_);
	for(__=1;__<=_;++__) {
		printf("Case %d: ",__);
		scanf("%d%d",&n,&last);
		begin=last;
		c1=c2=0LL;
		for(i=1;i<n;++i) {
			scanf("%d",&current);
			if(current > last) c1+=current - last;
			else c2+=last - current;
			last = current;
		}
		printf("%lld %d\n",max(c1,c2),abs(last-begin)+1);
	}
	return 0;
}
