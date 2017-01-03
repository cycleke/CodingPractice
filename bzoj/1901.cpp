#include <cstdio>
#include <algorithm>
using namespace std;
#define N 60005
#define MS 2500005
int n,m,mcnt,cnd;
int a[N],MP[N],S[N],T[N];
int sum[MS],l[MS],r[MS],st[N],vis[N],_vis;
int q[4][N]; char ts[4];
inline int g(const int&x) {return lower_bound(MP+1,MP+mcnt+1,x)-MP;}
void insert(int la,int lx,int rx,int v,int delta) {
	++cnd; l[cnd]=l[la],r[cnd]=r[la],sum[cnd]=sum[la]+delta;
	if(lx==rx) return;
	int md=lx+rx>>1;
	if(v<=md) l[cnd]=cnd+1,insert(l[la],lx,md,v,delta);
	else r[cnd]=cnd+1,insert(r[la],md+1,rx,v,delta);
}
inline int gsum(int x) {
	int r=0;
	for(;x;x-=x&-x)r+=sum[l[st[x]]];
	return r;
}
inline void modify(int x,int v,int delta) {
	for(int t;x<=n;x+=x&-x) {
		t=S[x]; S[x]=cnd+1;
		insert(t,1,mcnt,v,delta);
	}
}
inline int query(int L,int R,int k) {
	static int i,lx,rx,md,t,lt,rt;
	for(i=L-1;i;i-=i&-i)st[i]=S[i];
	for(i=R;i;i-=i&-i)st[i]=S[i];
	lt=T[L-1],rt=T[R];
	lx=1,rx=mcnt;
	while(lx<rx) {
		md=lx+rx>>1;
		t=gsum(R)-gsum(L-1)+sum[l[rt]]-sum[l[lt]];
		if(k<=t) {
			rx=md; ++_vis;
			for(i=L-1;i;i-=i&-i)st[i]=l[st[i]],vis[i]=_vis;
			for(i=R;i;i-=i&-i)if(vis[i]^_vis)st[i]=l[st[i]];
			lt=l[lt],rt=l[rt];
		} else {
			lx=md+1,k-=t; ++_vis;
			for(i=L-1;i;i-=i&-i)st[i]=r[st[i]],vis[i]=_vis;
			for(i=R;i;i-=i&-i)if(vis[i]^_vis)st[i]=r[st[i]];
			lt=r[lt],rt=r[rt];
		}
	}return MP[lx];
}
int main() {
	int i,__;
	scanf("%d",&__);
	while(__--) {
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;++i) {
			scanf("%d",a+i);
			MP[i]=a[i];
			S[i]=0;
		}
		mcnt=n;
		for(i=1;i<=m;++i) {
			scanf("%s",ts);
			if(*ts=='Q') {
				scanf("%d%d%d",q[1]+i,q[2]+i,q[3]+i);
				q[0][i]=0;
			} else {
				scanf("%d%d",q[1]+i,q[2]+i);
				q[0][i]=1;
				MP[++mcnt]=q[2][i];
			}
		}
		sort(MP+1,MP+mcnt+1);
		mcnt=unique(MP+1,MP+mcnt+1)-MP-1;
		cnd=0; T[0]=0;
		for(i=1;i<=n;++i) {
			T[i]=cnd+1;
			insert(T[i-1],1,mcnt,g(a[i]),1);
		}
		for(i=1;i<=m;++i)
			if(q[0][i]) {
				modify(q[1][i],g(a[q[1][i]]),-1);
				modify(q[1][i],g(q[2][i]),1);
				a[q[1][i]]=q[2][i];
			} else printf("%d\n",query(q[1][i],q[2][i],q[3][i]));
	}
	return 0;
}
