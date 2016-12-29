#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 100005
struct node {
	int id,v,r,s;
	node *ch[2];
	void maintain() {
		s=1+ch[0]->s+ch[1]->s;
	}
}MSET[N],*rt[N],*nil;
int f[N];
inline int gf(int u) {
	int r=u; while(f[r]^r)r=f[r];
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
void rot(node*(&o),const int&d) {
	node*u=o->ch[d^1];o->ch[d^1]=u->ch[d];
	u->ch[d]=o; o->maintain(); u->maintain();o=u;
}
void insert(node*(&u),node*(&v)) {
	if(u==nil) u=v,u->s=1,u->ch[0]=u->ch[1]=nil;
	else {
		int k=v->v < u->v?0:1; ++u->s;
		insert(u->ch[k],v);
		if(u->r < u->ch[k]->r)rot(u,k^1);
	}
}
inline int kth(node*u,int k) {
	if(u->s < k) return -1;
	for(int ls;;){
		ls=u->ch[0]->s;
		if(ls+1==k)return u->id;
		if(k>ls)k-=ls+1,u=u->ch[1];
		else u=u->ch[0];
	}
}
void merge(node*(&u),node*(&v)) {
	if(v->ch[0]!=nil) merge(u,v->ch[0]);
	if(v->ch[1]!=nil) merge(u,v->ch[1]);
	insert(u,v);
}
inline void Union(int u,int v) {
	if(u==v) return;
	if(rt[u]->s < rt[v]->s) u^=v^=u^=v;
	merge(rt[u],rt[v]); f[v]=u;
}
int main() {
	nil=new node();
	nil->ch[0]=nil->ch[1]=nil;
	nil->s=0; nil->r=-100000;
	register int n=geti(),m=geti();
	node*cnd=MSET;
	for(int i=1;i<=n;++i) {
		f[i]=i;
		cnd->s=1,cnd->v=geti(),cnd->id=i,cnd->r=rand();
		cnd->ch[0]=cnd->ch[1]=nil;
		rt[i]=cnd++;
	}
	while(m--) Union(gf(geti()),gf(geti()));
	register int x,y; register char ch;
	for(m=geti();m;--m) {
		while(ch=getchar(),ch<'A');
		x=geti(),y=geti();
		if(ch=='Q') printf("%d\n",kth(rt[gf(x)],y));
		else Union(gf(x),gf(y));
	}
	return 0;
}
