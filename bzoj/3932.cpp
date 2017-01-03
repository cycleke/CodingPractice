#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
const int N=1e5+5,MS=N*40;
pair< int, pair< int,int> >p[N<<1];
int ls[MS],rs[MS],cnt[MS],rt[N],cnd;
long long sum[MS];
int MP[N],mcnt;
inline int g(const int&x){return lower_bound(MP+1,MP+mcnt+1,x)-MP;}
void insert(int&x,int y,int l,int r,const int&v,const int&delta) {
	x=++cnd;ls[x]=ls[y],rs[x]=rs[y],sum[x]=sum[y]+MP[v]*delta,cnt[x]=cnt[y]+delta;
	if(l==r)return; int m=l+r>>1;
	if(v<=m)insert(ls[x],ls[y],l,m,v,delta);
	else insert(rs[x],rs[y],m+1,r,v,delta);
}
inline long long query(int x,int k) {
	static long long r;
	for(r=0;;) {
		if(k>=cnt[x]) return r+sum[x];
		if(!ls[x]&&!rs[x]) return r+sum[x]/cnt[x]*k;
		if(k==cnt[ls[x]])return r+sum[ls[x]];
		if(k<cnt[ls[x]])x=ls[x];
		else k-=cnt[ls[x]],r+=sum[ls[x]],x=rs[x];
	}
}
int main() {
	int n,m,a,b,c,i,j,k,t,x;
	long long las=1;
	m=gi(),n=gi();
	for(k=i=0;i<m;++i) {
		a=gi(),b=gi(),c=gi();
		p[k++]=make_pair(a,make_pair(c,1));
		if(b<n)p[k++]=make_pair(b+1,make_pair(c,-1));
		MP[++mcnt]=c;
	}
	sort(p,p+k);
	sort(MP+1,MP+mcnt+1);
	mcnt=unique(MP+1,MP+mcnt+1)-MP-1;
	for(i=1,j=0;i<=n;++i) {
		rt[i]=rt[i-1];
		while(j<k&&p[j].first==i) {
			t=(j&&p[j-1].first==i)?rt[i]:rt[i-1];
			insert(rt[i],t,1,mcnt,g(p[j].second.first),p[j].second.second);
			++j;
		}
	}
	for(i=0;i<n;++i) {
		x=gi(),a=gi(),b=gi(),c=gi();
		k=1+(las*a+b)%c;
		printf("%lld\n",las=query(rt[x],k));
	}
	return 0;
}
