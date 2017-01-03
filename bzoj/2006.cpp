#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c,f;
	for(f=0;(c=getchar())<'0';f|=c=='-');a=c-'0';
	while('-'<(c=getchar()))a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 500005
#define MS 10000000
int s[N],rt[N],MP[N],mcnt;
inline int g(const int&x) {return lower_bound(MP+1,MP+mcnt+1,x)-MP;}
int ls[MS],rs[MS],cnt[MS],cnd;
struct node {
	int y,kth,delta;
	node(int _y,int _k,int _delta) : y(_y),kth(_k),delta(_delta){}
	bool operator < (const node&a) const {return delta < a.delta;}
};
priority_queue<node>heap;
void insert(int&x,int y,int l,int r,const int&v) {
	x=++cnd; ls[x]=ls[y],rs[x]=rs[y],cnt[x]=cnt[y]+1;
	if(l >= r) return; int m=l+r>>1;
	(v<=m)?(insert(ls[x],ls[y],l,m,v),0):(insert(rs[x],rs[y],m+1,r,v),0);
}
inline int query(int ln,int rn,int k) {
	int l=1,r=mcnt,t,md;
	if(ln)ln=rt[ln-1];else ln=0;
	rn=rt[rn];
	while(l^r) {
		md=l+r>>1;
		t=cnt[ls[rn]]-cnt[ls[ln]];
		if(t>=k)ln=ls[ln],rn=ls[rn],r=md;
		else k-=t,ln=rs[ln],rn=rs[rn],l=md+1;
	}return l;
}
int main() {
	int n=gi(),K=gi(),L=gi(),R=gi(),i,k,tmp,l,r;
	long long ans=0;
	node lala(0,0,0);
	MP[++mcnt]=s[0]=0;
	for(i=1;i<=n;++i)MP[++mcnt]=s[i]=s[i-1]+gi();
	sort(MP+1,MP+mcnt+1);
	mcnt=unique(MP+1,MP+mcnt+1)-MP-1;
	insert(rt[0],0,1,mcnt,g(s[0]));
	for(i=1;i<n;++i)insert(rt[i],rt[i-1],1,mcnt,g(s[i]));
	for(i=L;i<=n;++i) {
		l=max(0,i-R),r=i-L;
		heap.push(node(i,1,s[i]-MP[query(l,r,1)]));
	}
	while(K) {
		lala=heap.top(); heap.pop();
		i = lala.y,k=lala.kth;
		ans+=lala.delta;
		--K; l=max(0,i-R),r=i-L;
		if(k<r-l+1) heap.push(node(i,k+1,s[i]-MP[query(l,r,k+1)]));
	}
	printf("%lld\n",ans);
	return 0;
}
