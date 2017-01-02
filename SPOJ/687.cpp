#include <cstdio>
int ina; char inc;
inline int gi() {
	while(inc=getchar(),inc<'0');ina=inc-'0';
	while(inc=getchar(),'-'<inc)ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
inline char gc() {
	while(inc=getchar(),inc<'a');
	return inc;
}
inline bool cmp(int*r,int i,int j,int l) {return r[i]==r[j]&&r[i+l]==r[j+l];}
typedef int arr[50002];
arr a,wa,wb,ws,wv,sa,rk,he,st[20],mm;
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
	for(i=k=0;i<n;he[rk[i++]]=k)
		for(k?--k:0,j=sa[rk[i]-1];a[i+k]==a[j+k];++k);
}
inline int min(int a,int b){return a<b?a:b;}
inline void initst(int n) {
	static int i,j;
	for(i=1;i<=n;++i)st[0][i]=he[i];
	for(i=1;i<=mm[n];++i)
		for(j=1;j+(1<<i)-1<=n;++j)
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
}
inline int quy(int l,int r) {
	int t=mm[r-l+1];
	return min(st[t][l],st[t][r-(1<<t)+1]);
}
inline int Fun(int i,int j) {
	i=rk[i],j=rk[j];
	if(i>j) i^=j^=i^=j;
	return quy(i+1,j);
}
int main() {
	int __=gi(),i,j,k,n,ans,mx;
	for(*mm=-1,i=1;i<50002;++i)
		mm[i]=((i)&(i-1))?mm[i-1]:(mm[i-1]+1);
	while(__--) {
		for(n=gi(),i=0;i<n;++i)a[i]=gc();
		a[n]=0; da(n+1,128); cal(n); initst(n);
		mx=-1;
		for(i=1;i<=n;++i)
			for(j=0;j+i<n;j+=i) {
				ans=Fun(j,j+i);
				k=j-(i-ans%i);
				ans=ans/i+1;
				if(k>=0&&Fun(k,k+i)>=i)++ans;
				if(ans>mx)mx=ans;
			}
		printf("%d\n",mx);
	}
}
