#include <cstdio>
#include <cstring>
typedef int arr[100005];
arr wa,wb,ws,wv,a,sa,rk,hi,st[20],lg,cnt;
char s[100005];
inline bool cmp(int*r,int i,int j,int l) {return r[i]==r[j]&&r[i+l]==r[j+l];}
inline int min(const int&a,const int&b) {return a<b?a:b;}
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
inline void ghi(int n) {
	int i,j,k;
	for(i=0;i<n;++i)rk[sa[i]]=i;
	for(i=k=0;i<n;hi[rk[i++]]=k)
		if(rk[i])for(k?--k:0,j=sa[rk[i]-1];a[j+k]==a[i+k];++k);
}
inline void initst(int n) {
	static int i,j;
	for(i=1;i<n;++i)(*st)[i]=hi[i];
	for(i=1;i<=lg[n];++i)
		for(j=1;j+(1<<i)-1<n;++j)
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
}
inline int ask(int i,int j) {
	i=rk[i],j=rk[j];
	if(j<i)i^=j^=i^=j; ++i;
	int t=lg[j-i+1];
	return min(st[t][i],st[t][j-(1<<t)+1]);
}
int main() {
	int i,j,__,n,len,t1,t2;
	long long ans;
	for(i=2;i<60005;++i)lg[i]=lg[i>>1]+1;
	scanf("%d",&__);
	while(__--) {
		scanf("%s",s);
		memset(a,0,sizeof a);
		memset(wa,0,sizeof wa);
		memset(wb,0,sizeof wb);
		memset(cnt,0,sizeof cnt);
		for(n=0;s[n];++n)a[n]=s[n]-'a'+2;
		for(i=0;i<n;++i)a[n+i+1]=a[n-i-1];
		a[len=n]=1; n=n<<1|1;
		da(n,30); ghi(n); initst(n);
		for(i=1;i<=len;++i)
			for(j=0;j+i<n;j+=i)
				if(a[j]==a[j+i]) {
					t1=min(ask(j,j+i),i),t2=min(ask(n-i-j-1,n-j-1),i);
					if(t1+t2<=i) continue;
					++cnt[j-t2+1];--cnt[j+t1-i+1];
				}
		for(i=1;i<n;++i)cnt[i]+=cnt[i-1];
		ans=0;
		for(i=1;i<len-1;++i)ans+=(long long)cnt[i]*cnt[n-i];
		printf("%lld\n",ans);
	}
	return 0;
}
