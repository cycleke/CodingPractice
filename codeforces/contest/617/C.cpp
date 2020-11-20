#include <cstdio>
#include <algorithm>
using namespace std;
#define pll pair<long long,long long>
#define p2(a) ((a)*(a))
pll p[2010];
int main() {
	int n,i,j;long long x1,x2,y1,y2,x,y,ans,t;
	scanf("%d%lld%lld%lld%lld",&n,&x1,&y1,&x2,&y2);
	for(i=1;i<=n;++i) {
		scanf("%lld%lld",&x,&y);
		p[i].first=p2(x-x1)+p2(y-y1);
		p[i].second=p2(x-x2)+p2(y-y2);
	}
	sort(p+1,p+n+1); ans=1LL<<60;
	for(i=0;i<=n;++i) {
		t=0LL;
		for(j=i+1;j<=n;++j)
		  (t<p[j].second)?t=p[j].second:1;
		((t+=p[i].first)<ans)?ans=t:1;
	}return printf("%lld\n",ans),0;
}
