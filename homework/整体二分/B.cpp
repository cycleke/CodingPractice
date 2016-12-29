#include <cstdio>
#include <cstring>
#define N 100005
#define M 5005
struct OP{int t,x,y,k;}q[N+M],q1[N+M],q2[N+M];
int ans[M],c[N],t[N+M];
inline void add(int x,int v){for(;x<N;x+=x&-x)c[x]+=v;}
inline int sum(int x){int r=0;for(;0<x;x-=x&-x)r+=c[x];return r;}
void divide(int l,int r,int L,int R) {
	if(l>r) return;
	if(L>=R) {
		for(int i=l;i<=r;++i) ans[q[i].t]=L;
		return;
	}
	int mid=L+R>>1;
	for(int i=l;i<=r;++i)
		if(q[i].t) t[i]=sum(q[i].y)-sum(q[i].x-1);
		else if(q[i].y<=mid) add(q[i].x,1);
	for(int i=l;i<=r;++i)
		if(!q[i].t&&q[i].y<=mid) add(q[i].x,-1);
	int l1=0,l2=0;
	for(int i=l;i<=r;++i)
		if(q[i].t) {
			if(q[i].k<=t[i]) q1[++l1]=q[i];
			else q[i].k-=t[i],q2[++l2]=q[i];
		} else {
			if(q[i].y<=mid) q1[++l1]=q[i];
			else q2[++l2]=q[i];
		}
	for(int i=1;i<=l1;++i) q[l+i-1]=q1[i];
	for(int i=1;i<=l2;++i) q[l+l1+i-1]=q2[i];
	divide(l,l+l1-1,L,mid); divide(l+l1,r,mid+1,R);
}
int main() {
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i) {
		scanf("%d",&j);
		q[i].t=0;
		q[i].x=i,q[i].y=j;
	}
	j=n+1;
	for(i=1;i<=m;++i) {
		scanf("%d%d%d",&q[j].x,&q[j].y,&q[j].k);
		q[j].t=i;++j;
	}
	divide(1,n+m,-1e9,1e9);
	for(i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
