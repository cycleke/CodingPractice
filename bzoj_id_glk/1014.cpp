#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'-');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
typedef unsigned int ui;
const int N=150000,ba=257;
ui p[N];
struct node {
	ui ha; int siz; char c;
	node *fa,*ch[2];
}CD[N],*cd=CD,*root=NULL,*nil;
inline void maintain(node *(&u)) {
	if(u==nil) return;
	u->siz=u->ch[0]->siz+u->ch[1]->siz+1;
	u->ha=u->ch[0]->ha+u->c*p[u->ch[0]->siz]+u->ch[1]->ha*p[u->ch[0]->siz+1];
}
inline void rot(node *(&u)) {
	node *f=u->fa,*ff=f->fa;
	int d=u==f->ch[1];
	if((f->ch[d]=u->ch[d^1])!=nil) f->ch[d]->fa=f;
	f->fa=u,u->ch[d^1]=f;
	if((u->fa=ff)!=nil) ff->ch[f==ff->ch[1]]=u;
	maintain(f),maintain(u);
}
inline void splay(node *(&u),node *(&tag)) {
	while(u->fa!=tag) {
		if(u->fa->fa==tag) {rot(u);break;}
		if((u==u->fa->ch[1])==(u->fa==u->fa->fa->ch[1])) rot(u->fa);
		else rot(u); rot(u);
	}if(tag==nil) root=u;
}
inline node *kth(int k) {
	node *u=root;
	while(k&&u!=nil) {
		if(u->ch[0]->siz>=k) u=u->ch[0];
		else if(u->ch[0]->siz+1==k) return u;
		else k-=u->ch[0]->siz+1,u=u->ch[1];
	}return u;
}
inline void ins(int k, char ch) {
	node *l=kth(k); cd->c=ch;
	cd->ch[0]=nil,cd->ch[1]=l->ch[1];
	cd->fa=l,cd->ch[1]->fa=cd;
	l->ch[1]=cd;
	maintain(cd);
	while(l!=nil) maintain(l),l=l->fa;
	++cd;//splay(cd++,nil);
}
inline void upd(int k,char ch) {
	node *l=kth(k),*u; l->c=ch;
	for(u=l;u!=nil;u=u->fa) maintain(u);
	//splay(l,nil);
}
inline ui quy(int l,int r) {
	node *lu=kth(l-1),*ru=kth(r+1);
	splay(lu,nil); splay(ru,lu);
	return ru->ch[0]->ha;
}
char initstring[N];
node *build(int l,int r) {
	if(l>r) return nil;
	int m=l+r>>1; node *u=cd++;
	u->c=initstring[m];
	if((u->ch[0]=build(l,m-1))!=nil) u->ch[0]->fa=u;
	if((u->ch[1]=build(m+1,r))!=nil) u->ch[1]->fa=u;
	maintain(u); return u;
}
void PRINT(node *u) {
	if(u==nil) return;
	PRINT(u->ch[0]);
	putchar(u->c);
	PRINT(u->ch[1]);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("1014.in","r",stdin);
//	freopen("1014.out","w",stdout);
#endif
	initstring[1]='~';
	scanf("%s",initstring+2);
	register int cl=strlen(initstring+2),i,j,mi,l,r,m,an;
	for(p[0]=i=1;i<N;++i) p[i]=p[i-1]*ba;
	initstring[cl+2]='!';
	cd->fa=cd->ch[0]=cd->ch[1]=cd;
	cd->ha=cd->siz=cd->c=0; nil=cd++;
	root=build(1,cl+2); root->fa=nil;
	register char ch;
	for(m=geti();m;--m) {
		while(ch=getchar(),ch<'A');
		if(ch=='Q') {
			i=geti()+1,j=geti()+1;
//			if(m==1) PRINT(root),puts("");
			if(kth(i)->c!=kth(j)->c) {puts("0"); continue;}
			for(an=l=1,r=cl-(i<j?j:i)+2;l<=r;) {
				mi=l+r>>1;
				if(quy(i,i+mi-1)==quy(j,j+mi-1)) l=(an=mi)+1;
				else r=mi-1; //PRINT(root); puts("");
			}printf("%d\n",an);
		} else {
			j=ch=='R'; cl+=j^1;
			i=geti()+1; while(ch=getchar(),ch<'a');
			(j)?upd(i,ch):ins(i,ch);
		}
//		PRINT(root),puts("");
	}
}
