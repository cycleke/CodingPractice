#include <cstdio>
#include <cstring>
#define N 300005
struct query{
	int type,x,y,k,id;
}q[N],q1[N],q2[N];
int a[N],c[N],t[N],ans[N];
inline void add(int x,int v) {for(;x<N;x+=x&-x)c[x]+=v;}
inline int sum(int x) {	int r=0;for(;0<x;x-=x&-x) r+=c[x];return r;}
void divide(int l,int r,int L,int R) {
	if(l>r) return;
	if(L==R) {
		for(int i=l;i<=r;++i)if(!q[i].type) ans[q[i].id]=L;
		return;
	}
	int mid=L+R>>1;
	for(int i=l;i<=r;++i)
		if(!q[i].type) t[i]=sum(q[i].y)-sum(q[i].x-1);
		else if(q[i].y<=mid) add(q[i].x,q[i].type);
	for(int i=l;i<=r;++i)
		if(q[i].type&&q[i].y<=mid) add(q[i].x,-q[i].type);
	int l1=0,l2=0;
	for(int i=l;i<=r;++i)
		if(q[i].type) {
			if(q[i].y<=mid) q1[++l1]=q[i];
			else q2[++l2]=q[i];
		} else {
			if(q[i].k<=t[i]) q1[++l1]=q[i];
			else {
				q[i].k-=t[i];
				q2[++l2]=q[i];
			}
		}
	for(int i=1;i<=l1;++i)q[l+i-1]=q1[i];
	for(int i=1;i<=l2;++i)q[l+l1+i-1]=q2[i];
	divide(l,l+l1-1,L,mid); divide(l+l1,r,mid+1,R);
}
int main() {
	int n,Q,i,cnt,qs,t,x,y,z;
	while(~scanf("%d",&n)){
		qs=cnt=0;
		for(i=1;i<=n;++i) {
			scanf("%d",a+i);
			q[++cnt].type=1;
			q[cnt].x=i;
			q[cnt].y=a[i];
		}
		for(scanf("%d",&Q);Q;--Q) {
			scanf("%d",&t);
			if(t<2) {
				scanf("%d%d",&x,&y);
				q[++cnt].type=-1;
				q[cnt].x=x;
				q[cnt].y=a[x];
				q[++cnt].type=1;
				q[cnt].x=x;
				q[cnt].y=y;
				a[x]=y;
			} else {
				scanf("%d%d%d",&x,&y,&z);
				q[++cnt].type=0;
				q[cnt].x=x;
				q[cnt].y=y;
				q[cnt].id=qs++;
				q[cnt].k=z;
			}
		}
		divide(1,cnt,1,1e9);
		for(i=0;i<qs;++i) printf("%d\n",ans[i]);
	}
	return 0;
}
