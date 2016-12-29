#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mk make_pair
#define fir first
#define sec second
pii p[200005];

int main() {
	int n,i,x,w,ans=1;
	for(scanf("%d",&n),i=0;i<n;++i) {
		scanf("%d%d",&x,&w);
		p[i]=mk(x,w);
	}
	sort(p,p+n);
	x=p->fir,w=p->sec;
	for(i=1;i<n;++i) {
		if(p[i].fir-x>=p[i].sec+w) {
			++ans;
			x=p[i].fir;
			w=p[i].sec;
		} else {
			if(p[i].fir+p[i].sec<w+x) {
				x=p[i].fir;
				w=p[i].sec;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
