#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
/**********************/
#define N 100005
struct node {
	int s; bool ly;
	node*fa,*ch[2];
	void up();
	void down();
}MSET[N],*cnode=MSET,*rt,*mp[N],*nil;
void node::up() {s=1+ch[0]->s+ch[1]->s;}
void node::down() {
	if (!ly || this == nil) return;
	ly=false; swap(ch[0],ch[1]);
	ch[0]->ly^=1;ch[1]->ly^=1;
}
pair<int,int>a[N];
int rk[N];
node*build(int l,int r) {
	if(l>r) return nil;
	node*u=cnode++; int m=l+r>>1;
	u->s=1,u->ly=0;	mp[rk[m]]=u;
	if((u->ch[0]=build(l,m-1))!=nil) u->ch[0]->fa=u;
	if((u->ch[1]=build(m+1,r))!=nil) u->ch[1]->fa=u;
	return u;
}
inline void rot(node*u) {
	node*f=u->fa,*ff=f->fa;
	int d=u==f->ch[1];
	f->down(); u->down();
	if((f->ch[d]=u->ch[d^1])!=nil) f->ch[d]->fa=f;
	f->fa=u,u->ch[d^1]=f;
	if((u->fa=ff)!=nil) ff->ch[f==ff->ch[1]]=u;
	f->up(); u->up();
}
inline void splay(node*u,node*target) {
	for (node*f;u->fa!=target;) {
		if((f=u->fa)->fa==target) rot(u);
		else {
			((u==f->ch[1])^(f==f->ch[1]))?rot(u):rot(f);
			rot(u);
		}
	}
	if(target==nil) rt=u;
}
inline void del(node*u) {
	splay(u,nil);
	if(u->ch[0]==nil) rt=u->ch[1],rt->fa=nil;
	else {
		node*v=u->ch[0];
		while(v->ch[1]!=nil)v=v->ch[1];
		splay(v,u);
		v->ch[1]=u->ch[1];
		v->fa=nil;
		v->up(); rt=v;
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("3506.in","r",stdin);
#endif
	int n=gi(),i;
	for(i=1;i<=n;++i) a[i].first=gi(),a[i].second=i;
	sort(a+1,a+n+1);
	for(i=1;i<=n;++i) rk[a[i].second]=i;
	nil=new node();
	nil->s=nil->ly=0;
	nil->fa=nil->ch[0]=nil->ch[1]=nil;
	rt=build(1,n); rt->fa=nil;
	for(i=1;i<=n;++i) {
		splay(mp[i],nil);
		printf("%d ",rt->ch[0]->s+i);
		rt->ly^=1; rt->down();
		del(rt);
	}return 0;
}
