#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
char inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	register int a; register char c;
	while(c=getc(),c<'0');a=c-'0';
	while(c=getc(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 2000000
struct E{int to,v;E*nxt;}CD[N*5],*cd=CD,*head[N];
#define adde(a,b,c) (cd->v=c,cd->to=b,cd->nxt=head[a],head[a]=cd++)
int d[N];
#define pr pair<int,int>
priority_queue< pr, vector< pr >,greater < pr > >heap;
int main() {
	int n,m; scanf("%d%d",&n,&m);
	register int S=0,T=(n-1)*(m-1)*2+1;
	if(n==1|m==1) {
		register int ans=1<<30,a;
		while(scanf("%d",&a)==1) if(a<ans) ans=a;
		printf("%d\n",ans);
		return 0;
	}
	register int e=1,f=2,i,j,a,b,c;
	for(i=0;i^n;++i)
		for(j=1;j^m;++j) {
			c=geti();
			if(!i) a=T,b=f,f+=2;
			else if(i==n-1) a=e,b=0,e+=2;
			else a=e,b=f,e+=2,f+=2;
			adde(a,b,c);adde(b,a,c);
		}
	e=1,f=2;
	for(i=1;i^n;++i)
		for(j=0;j^m;++j) {
			c=geti();
			if(!j) a=0,b=e,e+=2;
			else if(j==m-1) a=f,b=T,f+=2;
			else a=e,b=f,e+=2,f+=2;
			adde(a,b,c);adde(b,a,c);
		}
	e=1,f=2;
	for(i=1;i^n;++i)
		for(j=1;j^m;++j) {
			c=geti();
			adde(e,f,c);adde(f,e,c);
			e+=2,f+=2;
		}
	memset(d,127,sizeof d);
	while(!heap.empty()) heap.pop();
	heap.push(make_pair(*d=0,0));
	E*it;
	while(!heap.empty()) {
		a=heap.top().second,c=heap.top().first; heap.pop();
		if(c^d[a]) continue;
		for(it=head[a];it;it=it->nxt)
			if(c+it->v<d[b=it->to]) heap.push(make_pair(d[b]=c+it->v,b));
	}
	printf("%d\n",d[T]);
	return 0;
}
