#include <cstdio>
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
typedef int array[100000];
array a,wa,wb,sa,rk,hi,wv,ws;
inline bool cmp(int*r,int i,int j,int l) {
	return r[i]==r[j]&&r[i+l]==r[j+l];
}
inline void da(int n,int m) {
	static int i,j,k,p,*x=wa,*y=wb,*t;
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
inline void calheight(int n) {
	static int i,j,k;
	for(i=1;i<=n;++i)rk[sa[i]]=i;
	for(i=k=0;i<n;hi[rk[i++]]=k)
		for(k?--k:0,j=sa[rk[i]-1];a[i+k]==a[j+k];++k);
}
int main() {
	int i,l,r,m,n,ans,mx,mi; bool flag;
	while(n=gi()) {
		for(i=0;i<n;++i)a[i]=gi();
		for(i=0,--n;i<n;++i)a[i]=a[i]-a[i+1]+100;
		a[n]=0;
		da(n+1,200);
		calheight(n);
		ans=0;
		for(l=0,r=n>>1;l<=r;) {
			m=l+r>>1;
			flag=false;
			mx=mi=sa[1];
			for(i=1;i<=n;++i)
				if(hi[i]<m)mx=mi=sa[i];
				else {
					if(sa[i]>mx)mx=sa[i];
					if(sa[i]<mi)mi=sa[i];
					if(mx-mi>=m){flag=true;break;}
				}
			flag?(l=(ans=m)+1):(r=m-1);
		}
		if(n<9||ans<4)ans=0;else ++ans;
		printf("%d\n",ans);
	}
	return 0;
}
