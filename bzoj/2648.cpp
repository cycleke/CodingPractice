#include <cstdio>
#include <algorithm>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
char buf[10];
inline void outi(int x) {
	if(!x){puts("0");return;}
	if(x<0)putchar('-'),x=-x;
	register char *s=buf+8;
	while(x)*s--=x%10+'0',x/=10;
	puts(s+1);
}
#define N 1000005
#define inf 0x7f7f7f7f
inline void cmin(int&a,int b){b<a?a=b:1;}
inline void cmax(int&a,int b){a<b?a=b:1;}
inline int ibs(int a){return a<0?-a:a;}
struct D{int d[2],mx0,mx1,mi0,mi1;D*l,*r;}t[N],*rt;
int cpd,ans;
inline bool cmp(const D&a,const D&b){return(a.d[cpd]^b.d[cpd])?a.d[cpd]<b.d[cpd]:a.d[cpd^1]<b.d[cpd^1];}
inline void kd_upd(D*u) {
	if(u->l) {
		cmax(u->mx0,u->l->mx0);cmax(u->mx1,u->l->mx1);
		cmin(u->mi0,u->l->mi0);cmin(u->mi1,u->l->mi1);
	}
	if(u->r) {
		cmax(u->mx0,u->r->mx0);cmax(u->mx1,u->r->mx1);
		cmin(u->mi0,u->r->mi0);cmin(u->mi1,u->r->mi1);
	}
}
D*kd_bld(int l,int r,int d) {
	int m=l+r>>1;
	cpd=d; std::nth_element(t+l+1,t+m+1,t+r+1,cmp);
	t[m].mx0=t[m].mi0=t[m].d[0];
	t[m].mx1=t[m].mi1=t[m].d[1];
	if(l^m)t[m].l=kd_bld(l,m-1,d^1);
	if(r^m)t[m].r=kd_bld(m+1,r,d^1);
	kd_upd(t+m);return t+m;
}
inline void kd_ins(D*ne) {
	int cd=0;D*u=rt;
	while(true) {
		cmax(u->mx0,ne->mx0),cmin(u->mi0,ne->mi0);
		cmax(u->mx1,ne->mx1),cmin(u->mi1,ne->mi1);
		if(ne->d[cd]<u->d[cd]) {
			if(u->l)u=u->l;
			else{u->l=ne;return;}
		}else{
			if(u->r)u=u->r;
			else{u->r=ne;return;}
		}
		cd^=1;
	}
}
inline int dist(int x,int y,D*u) {
	int r=0;
	if(x<u->mi0)r=u->mi0-x;
	else if(x>u->mx0)r=x-u->mx0;
	if(y<u->mi1)r+=u->mi1-y;
	else if(y>u->mx1)r+=y-u->mx1;
	return r;
}
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
int main() {
	int n=geti(),m=geti(),i,x,y;
	D*cur=t+n+1;
	for(i=1;i<=n;++i)t[i].d[0]=geti(),t[i].d[1]=geti();
	rt=kd_bld(1,n,0);
	while(m--){
		i=geti(),x=geti(),y=geti();
		if(i<2) {
			cur->mx0=cur->mi0=cur->d[0]=x;
			cur->mx1=cur->mi1=cur->d[1]=y;
			kd_ins(cur++);
		} else {
			ans=inf;kd_quy(rt,x,y);
			outi(ans);
		}
	}return 0;
}
