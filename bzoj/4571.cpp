#include <cstdio>
inline int geti() {
	register int a;register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 200005
#define M 10000005
int tnd,rt[N],s[M],ls[M],rs[M];
void upd(int l,int r,int la,int&cu,int v) {
	cu=++tnd;
	s[cu]=s[la]+1,ls[cu]=ls[la],rs[cu]=rs[la];
	if(l>=r)return;
	int m=l+r>>1;
	if(v<=m)upd(l,m,ls[la],ls[cu],v);
	else upd(m+1,r,rs[la],rs[cu],v);
}
bool quy(int l,int r,int la,int cu,int x,int y) {
	if(!(s[cu]-s[la]))return false;
	if(x<=l&&r<=y)return true;
	bool ret=0; int m=l+r>>1;
	if(x<=m)ret=ret||quy(l,m,ls[la],ls[cu],x,y);
	if(y >m)ret=ret||quy(m+1,r,rs[la],rs[cu],x,y);
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("4571.in","r",stdin);
#endif
	register int n=geti(),m=geti(),l,r,x,L,R,i,mi,b;
	for(x=1;x<=n;++x)upd(0,N,rt[x-1],rt[x],geti());
	while(m--) {
		b=geti(),x=geti(),l=geti(),r=geti();
		L=0,R=(1<<19)-1;
		for(i=18;~i;--i) {
			mi=L+R>>1;
			if(b&(1<<i))quy(0,N,rt[l-1],rt[r],L-x,mi-x)?(R=mi):(L=mi+1);
			else quy(0,N,rt[l-1],rt[r],mi-x+1,R-x)?(L=mi+1):(R=mi);
		}
		printf("%d\n",b^L);
	}return 0;
}
