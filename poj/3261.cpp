#include <cstdio>
#include <algorithm>
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 20005
int a[N],r[N],wa[N],wb[N],ws[N],wv[N],sa[N],rk[N],hi[N];
inline bool cmp(int*r,int i,int j,int l) {return r[i]==r[j]&&r[i+l]==r[j+l];}
inline void da(int n,int m) {
	static int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;++i)ws[i]=0;
	for(i=0;i<n;++i)++ws[x[i]=a[i]];
	for(i=1;i<m;++i)ws[i]+=ws[i-1];
	for(i=n-1;~i;--i)sa[--ws[x[i]]]=i;
	for(p=j=1;p<n;j<<=1,m=p) {
		for(p=0,i=n-j;i<n;++i)y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<m;++i)ws[i]=0;
		for(i=0;i<n;++i)++ws[wv[i]=x[y[i]]];
		for(i=1;i<m;++i)ws[i]+=ws[i-1];
		for(i=n-1;~i;--i)sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=i=1,x[sa[0]]=0;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
inline void calheight(int n) {
	static int i,j,k;
	for(i=1;i<=n;++i)rk[sa[i]]=i;
	for(i=k=0;i<n;hi[rk[i++]]=k)
		for(k?--k:0,j=sa[rk[i]-1];a[i+k]==a[j+k];++k);
}
inline bool cp(const int&i,const int&j){return a[i]<a[j];}
int main() {
	int n,k,i,j,m,la,ans;
	while(scanf("%d%d",&n,&k)^EOF) {
		for(i=0;i<n;++i)a[i]=gi(),r[i]=i;
		std::sort(r,r+n,cp);
		la=a[r[0]],a[r[0]]=m=1;
		for(i=1;i<n;++i) {
			if(a[j=r[i]]^la) la=a[j],++m;
			a[j]=m;
		}
		a[n]=0;
		da(n+1,m+1);
		calheight(n);
		ans=0;
		for(int l=1,r=n;l<=r;) {
			m=l+r>>1; la=1;
			for(i=2;i<=n&&la<k;++i)
				(hi[i]>=m)?++la:la=1;
			(la<k)?r=m-1:l=(ans=m)+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
