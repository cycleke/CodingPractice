#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define ls u<<1
#define rs u<<1|1
#define MID int mid=l+r>>1
struct D{bool a0,a1,b0,b1,c0,c1;}C[200005];
bool edge[3][100005]; char ts[10];
void build(int u,int l,int r) {
	if(l>=r) {
		C[u].b0=C[u].b1=true;
		return;
	}
	MID;
	build(ls,l,mid);build(rs,mid+1,r);
}
D pluse(const D&a,const D&b,const bool&x,const bool&y) {
	D r;
	r.a0=a.a0||(a.b0&&a.b1&&x&&y&&b.a0);
	r.a1=b.a1||(b.b0&&b.b1&&x&&y&&a.a1);
	r.b0=(a.b0&&x&&b.b0)||(a.c0&&y&&b.c1);
	r.b1=(a.b1&&y&&b.b1)||(a.c1&&x&&b.c0);
	r.c0=(x&&a.b0&&b.c0)||(y&&a.c0&&b.b1);
	r.c1=(y&&a.b1&&b.c1)||(x&&a.c1&&b.b0);
	return r;
}
void upd(int u,int l,int r,int p) {
	if(l>=r) {
		C[u].a0=C[u].a1=C[u].c0=C[u].c1=edge[2][p];
		return;
	}
	MID;
	if(p<=mid)upd(ls,l,mid,p);else upd(rs,mid+1,r,p);
	C[u]=pluse(C[ls],C[rs],edge[0][mid],edge[1][mid]);
}
D quy(int u,int l,int r,int x,int y) {
	if(l>=x&&r<=y)return C[u];
	MID;
	if(y<=mid)return quy(ls,l,mid,x,y);
	if(x>mid)return quy(rs,mid+1,r,x,y);
	return pluse(quy(ls,l,mid,x,mid),quy(rs,mid+1,r,mid+1,y),edge[0][mid],edge[1][mid]);
}
int main() {
	register int c=geti(),r1,c1,r2,c2;
	build(1,1,c);
	register D t1,t2,t3;
	register bool ok;
	while(scanf("%s",ts)^EOF) {
		if(*ts=='E')break;
		r1=geti()-1,c1=geti(),r2=geti()-1,c2=geti();
		if(c2<c1)r1^=r2^=r1^=r2,c1^=c2^=c1^=c2;
		if(*ts=='O') {
			if(r1>r2)r1^=r2^=r1^=r2,c1^=c2^=c1^=c2;
			if(r1<r2)edge[2][c1]=1;
			else edge[r1][c1]=1;
			upd(1,1,c,c1);
		} else if(*ts=='C') {
			if(r1>r2)r1^=r2^=r1^=r2,c1^=c2^=c1^=c2;
			if(r1<r2)edge[2][c1]=0;
			else edge[r1][c1]=0;
			upd(1,1,c,c1);
		} else {
			t1=quy(1,1,c,1,c1);
			t2=quy(1,1,c,c1,c2);
			t3=quy(1,1,c,c2,c);
			if(r1&&r2) {
				ok=t2.b1||(t1.a1&&t2.c0)||(t2.c1&&t3.a0);
				ok|=t1.a1&&t2.b0&&t3.a0;
			}else if(!r1^r2) {
				ok=t2.b0||(t1.a1&&t2.c1)||(t2.c0&&t3.a0);
				ok|=t1.a1&&t2.b1&&t3.a0;
			}else if(r1) {
				ok=t2.c1||(t1.a1&&t2.b0)||(t2.b1&&t3.a0);
				ok|=t1.a1&&t2.c0&&t3.a0;
			}else {
				ok=t2.c0||(t1.a1&&t2.b1)||(t2.b0&&t3.a0);
				ok|=t1.a1&&t2.c1&&t3.a0;
			}
			puts(ok?"Y":"N");
		}
	}
	return 0;
}
