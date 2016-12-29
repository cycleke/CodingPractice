#include <cstdio>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
int m,inf=1e9;
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a<b?b:a;}
struct D{int x[20005],y[20005],tp;}a;
inline void cut(D&a,int x1,int y1,int x2,int y2) {
	int tp=0;
	for(int i=1;i<=a.tp;++i)
		if(a.x[i]<x1||a.x[i]>x2||a.y[i]<y1||a.y[i]>y2) {
			++tp;
			a.x[tp]=a.x[i];
			a.y[tp]=a.y[i];
		}a.tp=tp;
}
inline void cc(D&a,int f) {
	int x1=inf,y1=inf,x2=-inf,y2=-inf;
	for(int i=1;i<=a.tp;++i) {
		x1=min(a.x[i],x1);x2=max(a.x[i],x2);
		y1=min(a.y[i],y1);y2=max(a.y[i],y2);
	}
	if(f==1)cut(a,x1,y1,x1+m,y1+m);
	else if(f==2)cut(a,x2-m,y1,x2,y1+m);
	else if(f==3)cut(a,x1,y2-m,x1+m,y2);
	else cut(a,x2-m,y2-m,x2,y2);
}
inline bool check() {
	D b;
	for(int x=1;x<5;++x)
		for(int y=1;y<5;++y) {
			b.tp=a.tp;
			for(int i=1;i<=b.tp;++i)
				b.x[i]=a.x[i],b.y[i]=a.y[i];
			cc(b,x);cc(b,y);
			int x1=inf,y1=inf,x2=-inf,y2=-inf;
			for(int i=1;i<=b.tp;++i) {
				x1=min(b.x[i],x1);x2=max(b.x[i],x2);
				y1=min(b.y[i],y1);y2=max(b.y[i],y2);
			}
			if(x2-x1<=m&&y2-y1<=m)return true;
		}return false;
}
int main() {
	a.tp=geti();
	for(int i=1;i<=a.tp;++i)
		a.x[i]=geti(),a.y[i]=geti();
	int L=1,R=inf,ans;
	while(L<=R)
		if(m=L+R>>1,check())ans=m,R=m-1;
		else L=m+1;
	printf("%d\n",ans);
	return 0;
}
