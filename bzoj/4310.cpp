#include <cstdio>
typedef int arr[100005];
arr wa,wb,sa,ws,wv,rk,hi,st[18],lg;
int n,ls,rs,k; char a[100005];
inline bool cmp(int*r,int i,int j,int l) {
	return r[i]==r[j]&&r[i+l]==r[j+l];
}
inline void da(int n,int m) {
	int i,j,p,*x=wa,*y=wb,*t;
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
		for(t=x,x=y,y=t,i=p=1,x[sa[0]]=0;i<n;++i)
			x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
	}
}
inline void gehi(int n) {
	int i,j,k;
	for(i=1;i<=n;++i)rk[sa[i]]=i;
	for(i=k=0;i<n;hi[rk[i++]]=k)
		for(k?--k:0,j=sa[rk[i]-1];a[i+k]==a[j+k];++k);
}
inline int min(const int&a,const int&b) {return a<b?a:b;}
inline void initst() {
	int i,j;
	for(i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(i=1;i<=n;++i)st[0][i]=hi[i];
	for(i=1;i<=lg[n];++i)
		for(j=1;j+(1<<i)-1<=n;++j)
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
}
inline int rmq(int i,int j) {
	int t=lg[j-i+1];
	return min(st[t][i],st[t][j-(1<<t)+1]);
}
inline int lcp(int a,int b) {
	if(a==b) return n-a;
	a=rk[a],b=rk[b];
	if(b<a)a^=b^=a^=b;
	return rmq(a+1,b);
}
inline bool cmp_str(int l1,int r1,int l2,int r2) {
	int len1=r1-l1+1,len2=r2-l2+1,com=lcp(l1,l2);
	if(len1<=len2&&com>=len1) return true;
	if(len1>len2&&com>=len2) return false;
	if(com>=len1&&com>=len2) return len1<=len2;
	return a[l1+com] <= a[l2+com];
}
inline void gkth(long long k) {
	static long long temp;
	for(int i=1;i<=n;++i) {
		temp=n-sa[i]-hi[i];
		if(temp<k) k-=temp;
		else {ls=sa[i],rs=ls+hi[i]+k-1; break;}
	}
}
inline bool check() {
	static int cnt,las,i;
	cnt=1,las=n-1;
	for(i=n-1;~i;--i)
		if(a[i]>a[ls]) return false;
		else if(!cmp_str(i,las,ls,rs)) {
			if(++cnt>k) return false;
			las=i;
		}
	return true;
}
int main() {
	freopen("4310.in","r",stdin);
	scanf("%d\n",&k);
	for(char ch=getchar();(ch^'\n')&&(ch^'\r')&&(ch^EOF);ch=getchar())a[n++]=ch;
	da(n+1,128); gehi(n);
	initst();
	long long L=1,R=0,ANS,MD;
	for(int i=1;i<=n;++i)R+=n-sa[i]-hi[i];
	while(L<=R)
		if(gkth(MD=L+R>>1),check())R=(ANS=MD)-1;
		else L=MD+1;
	gkth(ANS);
	for(int i=ls;i<=rs;++i)putchar(a[i]);
	return 0;
}
