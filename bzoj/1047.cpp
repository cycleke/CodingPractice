#include <cstdio>
inline int min(int a,int b){return a<b?a:b;}
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int v[1005][1005],q[1005],mx[1005][1005],mi[1005][1005],t1[1005],t2[1005];
int main() {
#ifndef ONLINE_JUDGE
	freopen("1047.in","r",stdin);
#endif
	register int a=geti(),b=geti(),n=geti(),*l,*r;
	for(register int i=0,j;i<a;++i)
		for(j=0;j<b;++j)v[i][j]=geti();
	for(register int i=0,j;i<a;++i) {
		for(j=0,l=r=q;j<b;++j) {
			while(l<r&&v[i][*(r-1)]<=v[i][j])--r;
			*r++=j;
			while(*l+n<=j)++l;
			if(j+2>n)mx[i][j]=v[i][*l];
		}
		for(j=0,l=r=q;j<b;++j) {
			while(l<r&&v[i][*(r-1)]>=v[i][j])--r;
			*r++=j;
			while(*l+n<=j)++l;
			if(j+2>n)mi[i][j]=v[i][*l];
		}
	}
	int ans=0x7f7f7f7f;
	for(register int i=n-1,j;i<b;++i) {
		for(j=0,l=r=q;j<a;++j) {
			while(l<r&&mx[*(r-1)][i]<=mx[j][i])--r;
			*r++=j;
			while(*l+n<=j)++l;
			if(j+2>n)t1[j]=mx[*l][i];
		}
		for(j=0,l=r=q;j<a;++j) {
			while(l<r&&mi[*(r-1)][i]>=mi[j][i])--r;
			*r++=j;
			while(*l+n<=j)++l;
			if(j+2>n)t2[j]=mi[*l][i];
		}
		for(j=n-1;j<a;++j)ans=min(ans,t1[j]-t2[j]);
	}
	printf("%d\n",ans);
	return 0;
}
