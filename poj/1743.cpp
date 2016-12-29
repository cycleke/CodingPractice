#include <cstdio>
#include <cstring>
#define N 100000
#define cmax(a,b) ((a<(__t=(b)))?a=__t:1)
#define cmin(a,b) (((__t=(b))<a)?a=__t:1)

int a[N],wa[N],wb[N],wv[N],wn[N],sa[N],rank[N],h[N],__t;
int cmp(int *r,int a,int b,int l) {
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void DA(int *r,int n,int m) {
	int i,j,k,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;++i) wn[i]=0;
	for(i=0;i<n;++i) ++wn[x[i]=r[i]];
	for(i=1;i<m;++i) wn[i]+=wn[i-1];
	for(i=n-1;~i;--i) sa[--wn[x[i]]]=i;
	for(j=1,p=1;p<n;j<<=1,m=p) {
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;++i) wv[i]=x[y[i]];
		for(i=0;i<m;++i) wn[i]=0;
		for(i=0;i<n;++i) ++wn[wv[i]];
		for(i=1;i<m;++i) wn[i]+=wn[i-1];
		for(i=n-1;~i;--i) sa[--wn[wv[i]]]=y[i];
		t=x,x=y,y=t;p=1;
		for(x[sa[0]]=0,i=1;i<n;++i)
		  x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
void calheight(int *r,int n) {
	int i,j,k=0;
	for(i=1;i<=n;++i) rank[sa[i]]=i;
	for(i=0;i<n;h[rank[i++]]=k)
	  for(k?--k:1,j=sa[rank[i]-1];r[i+k]==r[j+k];++k);
}
int main(){
	int i,j,l,r,ans,mid,n,mx,mi; bool flag;
	while(scanf("%d",&n)!=EOF&&n) {
		for(i=0;i<n;++i) scanf("%d",a+i);
		for(i=0,--n;i<n;++i) a[i]=a[i]-a[i+1]+100;
		a[n]=0;
		DA(a,n+1,200);
		calheight(a,n); ans=0;
		for(l=0,r=n/2;l<=r;) {
			mid=l+r>>1;
			flag=false;mx=mi=sa[1];
			for(i=2;i<=n&&!flag;++i)
			  if(h[i]<mid) mi=mx=sa[i];
			  else {
				  cmin(mi,sa[i]);
				  cmax(mx,sa[i]);
				  if(mx-mi>=mid) flag=true;
			  }
			flag?(l=(ans=mid)+1):r=mid-1;
		}
		if(n<9||ans<4) ans=0; else ++ans;
		printf("%d\n",ans);
	}
}
