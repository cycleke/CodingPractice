#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c,f;
	for(f=0;(c=getchar())<'0';f|=c=='-');a=c-'0';
	while('-'<(c=getchar()))a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 20005
#define MS 800000
struct data{int sum,lm,rm;}tr[MS];
data operator + (const data&a,const data&b){return (data){a.sum+b.sum,max(a.lm,a.sum+b.lm),max(b.rm,a.rm+b.sum)};}
int ls[MS],rs[MS],cnd,rt[N],q[4],n;
pair<int,int>a[N];
void build(int&u,int l,int r) {
	if(u=++cnd,l==r) {tr[u]=(data){1,1,1};return;}
	int m=l+r>>1;
	build(ls[u],l,m); build(rs[u],m+1,r);
	tr[u]=tr[ls[u]]+tr[rs[u]];
}
void insert(int la,int&cu,int l,int r,int v) {
	cu=++cnd; ls[cu]=ls[la],rs[cu]=rs[la];
	if(l==r) {tr[cu]=(data){-1,-1,-1};return;}
	int m=l+r>>1;
	if(v<=m) insert(ls[la],ls[cu],l,m,v);
	else insert(rs[la],rs[cu],m+1,r,v);
	tr[cu]=tr[ls[cu]]+tr[rs[cu]];
}
data quy(int x,int y,int l,int r,int u) {
	if(x>y) return (data){0,0,0};
	if(x<=l&&r<=y) return tr[u];
	int m=l+r>>1;
	if(y<=m) return quy(x,y,l,m,ls[u]);
	if(x >m) return quy(x,y,m+1,r,rs[u]);
	return quy(x,y,l,m,ls[u])+quy(x,y,m+1,r,rs[u]);
}
inline bool check(int x) {
	return quy(q[0],q[1],0,n-1,rt[x]).rm+quy(q[1]+1,q[2]-1,0,n-1,rt[x]).sum+quy(q[2],q[3],0,n-1,rt[x]).lm>=0;
}
int main() {
	int ans=0,i,qq,l,r,m;
	for(i=0,n=gi();i<n;++i)a[a[i].second=i].first=gi();
	sort(a,a+n); build(rt[0],0,n-1);
	for(i=1;i<n;++i)insert(rt[i-1],rt[i],0,n-1,a[i-1].second);
	for(qq=gi();qq;--qq) {
		for(i=0;i<4;++i)q[i]=(gi()+ans)%n;
		sort(q,q+4);
		for(l=0,r=n-1;l<=r;)
			(check(m=l+r>>1))?(l=m+1):(r=m-1);
		printf("%d\n",ans=a[l-1].first);
	}
	return 0;
}
