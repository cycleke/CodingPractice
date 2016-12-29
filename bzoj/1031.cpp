#include <cstdio>
#include <cstring>
#define N 200010
char s[N];
int sa[N],ws[N],wv[N],ta[N],tb[N],n;
inline void da() {
	register int i,j,*x=ta,*y=tb,*t,m=256,p;
	for(i=0;i<m;++i)ws[i]=0;
	for(i=0;i<n;++i)++ws[x[i]=s[i]];
	for(i=1;i<m;++i)ws[i]+=ws[i-1];
	for(i=n-1;~i;--i)sa[--ws[x[i]]]=i;
	for(p=j=1;p<n;j<<=1,m=p) {
		for(p=0,i=n-j;i<n;++i)y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<n;++i)wv[i]=x[y[i]];
		for(i=0;i<m;++i)ws[i]=0;
		for(i=0;i<n;++i)++ws[wv[i]];
		for(i=1;i<m;++i)ws[i]+=ws[i-1];
		for(i=n-1;~i;--i)sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[*sa]=0,i=1;i<n;++i)
			x[sa[i]]=((y[sa[i-1]]^y[sa[i]])||(y[sa[i-1]+j]^y[sa[i]+j]))?p++:p-1;
	}
}
int main() {
	scanf("%s",s);
	register int k=strlen(s);
	for(register int i=0;i<k;++i)s[i+k]=s[i];
	n=k<<1|1;da();
	for(register int i=1;i<n;++i)
		if(sa[i]<k) putchar(s[sa[i]+k-1]);
	return 0;
}
