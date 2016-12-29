#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 300010
#define SC 10005
int co[N],C[SC<<1],pre,blo,ans[SC],cnt[SC];
struct D{ 
	int l,r,id;
	void Read(int i) {scanf("%d%d",&l,&r),id=i;}
	bool operator < (const D &a) const {
		if(l/blo == a.l/blo) return r<a.r;
		return l/blo<a.l/blo;
	}
}op[SC];

void Update(int x,int v) {
	cnt[x]+=v; x=(x+pre)>>1;
	for(;x;x>>=1) 
	  if(cnt[C[x<<1]]<cnt[C[x<<1|1]]) C[x]=C[x<<1|1];
	  else C[x]=C[x<<1];
}

int main() {
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	int i,j,t,n,m,c,l,r;
	scanf("%d%d",&n,&c); blo=sqrt(n);
	for(pre=1;pre<=(c+1);pre<<=1);
	for(i=1;i<=c;++i) C[i+pre]=i;
	for(i=1;i<=n;++i) scanf("%d",co+i);
	for(scanf("%d",&m),i=1;i<=m;++i) (op+i)->Read(i);
	sort(op+1,op+m+1);
	l=1,r=0;
	for(i=1;i<=m;++i) {
		while(l>op[i].l) Update(co[--l],1);
		while(r<op[i].r) Update(co[++r],1);
		while(l<op[i].l) Update(co[l++],-1);
		while(r>op[i].r) Update(co[r--],-1);
		t=C[1];
		if(cnt[t]<=(op[i].r-op[i].l+1)/2) ans[op[i].id]=0;
		else ans[op[i].id]=t;
	}
	for(i=1;i<=m;++i)
	  ans[i]?printf("yes %d\n",ans[i]),1:puts("no"),1;
	return 0;
}
