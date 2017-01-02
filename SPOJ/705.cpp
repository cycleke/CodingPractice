#include <cstdio>
#include <cstring>
#define N 50005
int wa[N],wb[N],ws[N],wv[N],sa[N],rk[N],hi[N];
char a[N];
inline bool cmp(int*r,int i,int j,int l){return r[i]==r[j]&&r[i+l]==r[j+l];}
inline void da(int n,int m) {
	static int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;++i)ws[i]=0;
	for(i=0;i<n;++i)++ws[x[i]=a[i]];
	for(i=1;i<m;++i)ws[i]+=ws[i-1];
	for(i=n-1;~i;--i)sa[--ws[x[i]]]=i;
	for(j=p=1;p<n;j<<=1,m=p) {
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
inline void cal(int n) {
	static int i,j,k;
	for(i=1;i<=n;++i)rk[sa[i]]=i;
	for(i=k=0;i<n;hi[rk[i++]]=k)
		for(k?--k:0,j=sa[rk[i]-1];a[i+k]==a[j+k];++k);
}
int main() {
	int __,n,ans,i;
	scanf("%d",&__);
	while(__--) {
		scanf("%s",a);
		n=strlen(a);
		da(n+1,256);
		cal(n);
		ans=0;
		for(i=1;i<=n;++i)
			ans+=n-sa[i]-hi[i];
		printf("%d\n",ans);
	}
	return 0;
}
