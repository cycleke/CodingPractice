#include <cstdio>
#include <queue>
using namespace std;
#define N 500005
int s[N],lg[N],st[20][N];
inline int gi() {
	static int a; static char c,f;
	for(f=0;(c=getchar())<'0';f|=c=='-');a=c-'0';
	while('-'<(c=getchar()))a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
struct node {int i,l,r,m;};
bool operator < (const node&a,const node&b) {
	return s[a.i]-s[a.m] < s[b.i]-s[b.m];
}
priority_queue<node>heap;
inline int ms(const int&a,const int&b) {return s[a]<s[b]?a:b;}
inline int rmq(int i,int j) {
	int t=lg[j-i+1];
	return ms(st[t][i],st[t][j-(1<<t)+1]);
}
int main() {
	int n=gi(),K=gi(),L=gi(),R=gi(),i,j,k,t;
	node lala; long long ans=0;
	for(i=1;i<=n;++i)s[i]=s[i-1]+gi();
	for(i=2,t=n+2;i<t;++i)lg[i]=lg[i>>1]+1;
	for(i=0;i<=n;++i)(*st)[i]=i;
	for(i=1,t=lg[n+1]+1;i<t;++i)
		for(j=0,k=n-(1<<i)+2;j<k;++j)
			st[i][j]=ms(st[i-1][j],st[i-1][j+(1<<i-1)]);
	for(i=L;i<=n;++i) {
		j=(i-R)<0?0:(i-R),k=i-L;
		heap.push((node){i,j,k,rmq(j,k)});
	}
	while(K--) {
		lala=heap.top(); heap.pop();
		i=lala.i,j=lala.l,k=lala.r,t=lala.m;
		ans+=s[i]-s[t];
		if(j^t) heap.push((node){i,j,t-1,rmq(j,t-1)});
		if(t^k) heap.push((node){i,t+1,k,rmq(t+1,k)});
	}
	printf("%lld\n",ans);
	return 0;
}
