#include <cstdio>
#include <cstring>
#define MS 100010
#define mod 1000000
#define ni (c<'0'|'9'<c)
char Inb[1<<16],*Ine=Inb,*Ins=Inb;
#define getc() ((Ins==Ine&&(Ine=(Ins=Inb)+fread(Inb,1,1<<16,stdin),Ins==Ine))?EOF:*Ins++)
inline int geti() {
	register int a; register char c;
	while(c=getc(),ni);a=c-'0';
	while(c=getc(),!ni)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct node {
	int v; node *fa,*ch[2];
}CD[MS],*root=NULL,*cd=CD,*t1,*t2;
inline void rot(node *u) {
    node *f=u->fa,*ff=f->fa;
	int d=u==f->ch[1];
	if(f->ch[d]=u->ch[d^1]) f->ch[d]->fa=f;
	f->fa=u; u->ch[d^1]=f;
	if(u->fa=ff) ff->ch[f==ff->ch[1]]=u;
}
inline void splay(node *u,node *tag) {
	while(u->fa!=tag) {
		if(u->fa->fa==tag) {rot(u); break;}
		if((u==u->fa->ch[1])==(u->fa==u->fa->fa->ch[1])) rot(u->fa);
		else rot(u);
		rot(u);
	}
	if(tag==NULL) root=u;
}
inline void ins(const int&val) {
	if(root==NULL) {
		cd->v=val; root=cd++;
		return;
	}
	register node *u=root;
	register int d;
	while(u) {
		d=(val<u->v)?0:1;
		if(u->ch[d]) u=u->ch[d];
		else {
			cd->v=val; cd->fa=u;
			u->ch[d]=cd++;
			break;
		}
	}
	splay(cd-1,NULL);
}
inline void pred(const int&val) {
	node *u=root; t1=NULL;
	while(u) {
		if(val<u->v) u=u->ch[0];
		else t1=u,u=u->ch[1];
	}if(t1) splay(t1,NULL);
}
inline void succ(const int&val) {
	node *u=root; t2=NULL;
	while(u) {
		if(u->v<val) u=u->ch[1];
		else t2=u,u=u->ch[0];
	}if(t2) splay(t2,NULL);
}
inline void del(node*u) {
	splay(u,NULL);
	if(root->ch[0]==NULL) {
		root=root->ch[1];
		if(root) root->fa=NULL;
	} else {
		register node *c=root->ch[0];
		while(c->ch[1]) c=c->ch[1];
		splay(c,root); c->ch[1]=root->ch[1];c->fa=NULL;
		if(root->ch[1]) root->ch[1]->fa=c;
		root=c;
	}
}
inline int query(const int&val) {
	succ(val); pred(val);
	if(t1&&t2) {
		if(val-t1->v<=t2->v-val) return del(t1),val-t1->v;
		return del(t2),t2->v-val;
	} else if(t1) return del(t1),val-t1->v;
	return del(t2),t2->v-val;
}
int main() {
	register int T,flag=0,a,b,ans=0;
	for(T=geti();T;--T) {
		a=geti(),b=geti();
		if(!a) a=-1;
		if(a*flag>=0) ins(b);
		else ans+=query(b);
		flag+=a; while(ans>=mod) ans-=mod;
	}
	printf("%d",ans);
	return 0;
}
