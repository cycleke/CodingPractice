#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100100
int C[N],ans[N];
#define lb(a) (a&-a)
inline void add(int x){for(;x<N;x+=lb(x))++C[x];}
inline int sum(int x){int r=0;for(;x;x-=lb(x))r+=C[x];return r;}
inline void clr(int x){for(;x<N;x+=lb(x))C[x]=0;}
struct D{int x,y,z,id;}p[N],t[N];
bool cmp(const D&a,const D&b){
	if(a.x^b.x)return a.x<b.x;
	if(a.y^b.y)return a.y<b.y;
	return a.z<b.z;
}
bool cp(const D&a,const D&b){return(a.y^b.y)?a.y<b.y:a.z<b.z;}
void solve(int l,int r) {
	if(l>=r)return;
	int m=l+r>>1,i,j;
	solve(l,m);
	for(i=l;i<=r;++i)t[i]=p[i];
	sort(t+l,t+m+1,cp);
	sort(t+m+1,t+r+1,cp);
	for(i=m+1,j=l;i<=r;++i){
		while(j<=m&&t[j].y<=t[i].y)add(t[j].z),++j;
		ans[t[i].id]+=sum(t[i].z);
	}
	for(i=l;i<=m;++i)clr(t[i].z);
	solve(m+1,r);
}
int main() {
	int __,n;
	scanf("%d",&__);
	while(__--) {
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
			p[i].id=i;
		}
		sort(p+1,p+n+1,cmp);
		memset(ans,0,sizeof ans);
		memset(C,0,sizeof C);
		solve(1,n);
		for(int i=n-1;i;--i)
			if(p[i].x==p[i+1].x&&p[i].y==p[i+1].y&&p[i].z==p[i+1].z)
				ans[p[i].id]=ans[p[i+1].id];
		for(int i=1;i<=n;++i)
			printf("%d\n",ans[i]);
	}return 0;
}
