#include <cstdio>
#include <cstring>
#include <algorithm>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
char buf[10];
inline void outi(int x) {
	if(!x) {puts("0");return;}
	if(x<0) putchar('-'),x=-x;
	register char *s=buf+8;
	for(;x;x/=10)*s--=x%10+'0';
	puts(s+1);
}
inline void cmin(int&a,int b){b<a?a=b:1;}
inline void cmax(int&a,int b){a<b?a=b:1;}
const int inf=0x7f7f7f7,N=1000005;
struct D{
	int d[2],Max[2],Min[2];D*l,*r;
}t[N],*root;
int cmp_d,ans;
inline bool cmp(const D&a,const D&b){return (a.d[cmp_d]^b.d[cmp_d])?a.d[cmp_d]<b.d[cmp_d]:a.d[cmp_d^1]<b.d[cmp_d^1];}
inline void kd_upd(D*u) {
	if(u->l) {
		cmax(u->Max[0],u->l->Max[0]),cmax(u->Max[1],u->l->Max[1]);
		cmin(u->Min[0],u->l->Min[0]),cmin(u->Min[1],u->l->Min[1]);
	}
	if(u->r) {
		cmax(u->Max[0],u->r->Max[0]),cmax(u->Max[1],u->r->Max[1]);
		cmin(u->Min[0],u->r->Min[0]),cmin(u->Min[1],u->r->Min[1]);
	}
}
D*kd_build(int l,int r,int d) {
	int mi=l+r>>1;
	cmp_d=d; std::nth_element(t+l+1,t+mi+1,t+r+1,cmp);
	t[mi].Max[0]=t[mi].Min[0]=t[mi].d[0];
	t[mi].Min[1]=t[mi].Max[1]=t[mi].d[1];
	if(l^mi)t[mi].l=kd_build(l,mi-1,d^1);
	if(r^mi)t[mi].r=kd_build(mi+1,r,d^1);
	kd_upd(t+mi); return t+mi;
}
inline void kd_ins(D*ne) {
	int cd=0;D*u=root;
	while(true) {
		cmax(u->Max[0],ne->Max[0]),cmax(u->Max[1],ne->Max[1]);
		cmin(u->Min[0],ne->Min[0]),cmin(u->Min[1],ne->Min[1]);
		if(ne->d[cd]<u->d[cd]) {
			if(u->l) u=u->l;
			else {u->l=ne; return;}
		}else {
			if(u->r) u=u->r;
			else {u->r=ne; return;}
		}
		cd^=1;
	}
}
inline int dist(int x,int y,D*u) {
	int dis=0;
	if(x<u->Min[0])dis+=u->Min[0]-x;
	if(x>u->Max[0])dis+=x-u->Max[0];
	if(y<u->Min[1])dis+=u->Min[1]-y;
	if(y>u->Max[1])dis+=y-u->Max[1];
	return dis;
}
inline int ibs(int a){return a<0?-a:a;}
inline void kd_quy(D*u,const int&x,const int&y) {
	int dl,dr,d0;
	d0=ibs(u->d[0]-x)+ibs(u->d[1]-y);
	if(d0<ans)ans=d0;
	if(u->l)dl=dist(x,y,u->l);else dl=inf;
	if(u->r)dr=dist(x,y,u->r);else dr=inf;
	if(dl<dr) {
		if(dl<ans)kd_quy(u->l,x,y);
		if(dr<ans)kd_quy(u->r,x,y);
	}else {
		if(dr<ans)kd_quy(u->r,x,y);
		if(dl<ans)kd_quy(u->l,x,y);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("2648.in","r",stdin);
#endif
	int n=geti(),m=geti(),i,x,y;
	D*cur=t+n+1;
	for(i=1;i<=n;++i)t[i].d[0]=geti(),t[i].d[1]=geti();
	root=kd_build(1,n,0);
	while(m--){
		i=geti(),x=geti(),y=geti();
		if(i<2) {
			cur->Max[0]=cur->Min[0]=cur->d[0]=x;
			cur->Max[1]=cur->Min[1]=cur->d[1]=y;
			kd_ins(cur++);
		} else {
			ans=inf; kd_quy(root,x,y);
			outi(ans);
		}
	}
	return 0;
}
