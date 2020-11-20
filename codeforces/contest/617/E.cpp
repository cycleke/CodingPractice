#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 1000005
#define MXOR 2000000
#define ll long long
int a[N],blo,bel[N],k,n,m;
struct D{
	int l,r,id;
	bool operator < (const D&a) const {
		return (bel[l]^bel[a.l])?bel[l]<bel[a.l]:r<a.r;
	}
}Q[N];
ll cnt[MXOR],ans[N],tmp;
inline void Ins(int a) {tmp+=cnt[k^a];++cnt[a];}
inline void Del(int a) {--cnt[a];tmp-=cnt[k^a];}

int main() {
	int i,j,o,l,r;
	scanf("%d%d%d",&n,&m,&k); blo=sqrt(n+0.5);
	for(i=1;i<=n;++i) scanf("%d",&o),a[i]=a[i-1]^o,bel[i]=(i-1)/blo;
	for(i=1;i<=m;++i) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i,--Q[i].l;
	sort(Q+1,Q+m+1); l=1,r=0,tmp=0LL;
	for(i=1;i<=m;++i) {
		while(l>Q[i].l) Ins(a[--l]);
		while(r<Q[i].r) Ins(a[++r]);
		while(l<Q[i].l) Del(a[l++]);
		while(r>Q[i].r) Del(a[r--]);
		ans[Q[i].id]=tmp;
	}
	for(i=1;i<=m;++i) printf("%lld\n",ans[i]);
	return 0;
}
