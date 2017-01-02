#include <cstdio>
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 300005
long long C[N],ans[N];
inline void add(int x,int ad) {for(;x<N;x+=x&-x)C[x]+=ad;}
inline long long sum(int x) {
	static long long r;
	for(r=0;0<x;x-=x&-x)r+=C[x];
	return r;
}
struct edge{int to;edge*nt;}MSET[N<<1],*cedge=MSET,*hd[N];
inline void adde(int a,int b){cedge->to=b,cedge->nt=hd[a],hd[a]=cedge++;}
struct quy{int id,k;quy*nt;}MQUY[N],*cq=MQUY,*hq[N];
inline void addq(int a,int b,int c) {
	cq->id=c,cq->k=b;
	cq->nt=hq[a],hq[a]=cq++;
}
inline int min(int a,int b) {return a<b?a:b;}
int dfs(int u,int dep,int fa) {
	int s=1,v;
	for(quy*it=hq[u];it;it=it->nt)
		ans[it->id]=-(sum(dep+it->k)-sum(dep));
	for(edge*it=hd[u];it;it=it->nt)
		if((v=it->to)^fa) s+=dfs(v,dep+1,u);
	for(quy*it=hq[u];it;it=it->nt) {
		long long&a=ans[it->id];
		a+=1LL*min(dep-1,it->k)*(s-1);
		a+=sum(dep+it->k)-sum(dep);
	}
	add(dep,s-1);
	return s;
}
int main() {
	freopen("3653.in","r",stdin);
	int n=gi(),q=gi(),a,b,i;
	for(i=1;i<n;++i) adde(a=gi(),b=gi()),adde(b,a);
	for(i=0;i<q;++i) {
		a=gi(),b=gi();
		addq(a,b,i);
	}
	dfs(1,1,0);
	for(i=0;i<q;++i)printf("%lld\n",ans[i]);
	return 0;
}
