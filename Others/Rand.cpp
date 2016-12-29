#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
vector<int>ve[10005];
int rint(int a) {return (double)rand()/(RAND_MAX-1)*a;}
int co[300010];
int main() {
	freopen("T.in","r",stdin); freopen("TT.out","w",stdout);
	int i,j,n,l,r,m,len,p,t,c;
	for(scanf("%d%d",&n,&c),i=1;i<=n;++i) {
		scanf("%d",co+i);
		ve[co[i]].push_back(i);
	}
	for(scanf("%d",&m);m;--m) {
		scanf("%d%d",&l,&r);
		len=r-l+1;
		for(i=20;i;--i) {
			p=l+rint(len); c=co[p];
			t=upper_bound(ve[c].begin(),ve[c].end(),r)-lower_bound(ve[c].begin(),ve[c].end(),l);
			if(t>len/2) {printf("yes %d\n",c);i=22;break;}
		}if(i==0) puts("no");
	}return 0;
}
