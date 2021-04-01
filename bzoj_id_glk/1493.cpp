#include <cstdio>
#include <cstring>
int ina; char inc;
inline int geti() {
	for(;(inc=getchar())<'0'||inc>'9';);
	for(ina=inc-'0';(inc=getchar())>='0'&&inc<='9';ina=(ina<<3)+(ina<<1)+inc-'0');
	return ina;
}
#define ls u<<1
#define rs u<<1|1
#define N 500010
struct D{
	int lc,rc,pa;
	D operator + (const D&a) const {
		D ret; ret.lc=lc,ret.rc=a.rc;
		ret.pa=pa+a.pa; if(rc==a.lc) --ret.pa;
		return ret;
	}
	inline void ch(int a)  {lc=rc=a; pa=1;}
}C[N<<2];
int ly[N<<2],n,c,dis,q; bool d;
inline void Down(int u){
	if(!ly[u]) return;
	ly[ls]=ly[rs]=ly[u];
	C[ls].ch(ly[u]),C[rs].ch(ly[u]);
	ly[u]=0;
}
void Update(int u,int l,int r,int x,int y,int op) {
	if(x<=l&&r<=y) {
		ly[u]=op; C[u].ch(op);
		return;
	}Down(u);
	int m=l+r>>1;
    if(y<=m) Update(ls,l,m,x,y,op);
	else if(x>m) Update(rs,m+1,r,x,y,op);
	else {Update(ls,l,m,x,m,op);Update(rs,m+1,r,m+1,y,op);}
	C[u]=C[ls]+C[rs];
}
inline void cal(int &x,int &y) {
	if(d){
		x=(n+2-x-dis+n)%n;
		y=(n+2-y-dis+n)%n;
		x^=y^=x^=y;
	}else x=(x-dis+n)%n,y=(y-dis+n)%n;
	(!x)?x=n:1,(!y)?y=n:1;
}
int find(int u,int l,int r,int p) {
	if(l==r) return C[u].lc;
	Down(u); int m=l+r>>1;
	return (p<=m)?find(ls,l,m,p):find(rs,m+1,r,p);
}
D Query(int u,int l,int r,int x,int y){
	if(x<=l&&r<=y) return C[u];
	Down(u); int m=l+r>>1;
	if(y<=m) return Query(ls,l,m,x,y);
	if(x>m) return Query(rs,m+1,r,x,y);
	return Query(ls,l,m,x,m)+Query(rs,m+1,r,m+1,y);
}
void Build(int u,int l,int r) {
	if(l==r) {C[u].ch(geti()); return;}
	int m=l+r>>1; Build(ls,l,m); Build(rs,m+1,r);
	C[u]=C[ls]+C[rs];
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("T.in","r",stdin);
#endif
	char ts[3]; int x,y,z,cx,cy;
	n=geti(),c=geti(); Build(1,1,n);
	for(q=geti();q;--q) {
		scanf("%s",ts);
		if(*ts=='R') {
			z=geti();
			if(d)dis=(dis+n-z)%n;
			else dis=(dis+z)%n;
		}
		else if(*ts=='F') d=!d;
		else if(*ts=='P') {
			x=geti(),y=geti(),z=geti(); cal(x,y);
			if(x>y) Update(1,1,n,x,n,z),Update(1,1,n,1,y,z);
			else Update(1,1,n,x,y,z);
		} else if(*ts=='S') {
			x=geti(),y=geti(); cal(x,y);
			cx=find(1,1,n,x),cy=find(1,1,n,y);
			Update(1,1,n,x,x,cy); Update(1,1,n,y,y,cx);
		} else if(ts[1]=='S') {
			x=geti(),y=geti(); cal(x,y);
			if(x>y) printf("%d\n",(Query(1,1,n,x,n)+Query(1,1,n,1,y)).pa);
			else printf("%d\n",Query(1,1,n,x,y).pa);
		} else {
			z=Query(1,1,n,1,n).pa-(C[1].lc==C[1].rc); (z<1)?z=1:0;
			printf("%d\n",z);
		}
	}return 0;
}
