#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1004
#define M 10004
inline ll geti() {
	register ll a; register char c;
	while((c=getchar())<'0'||'9'<c);a=c-'0';
	while((c=getchar())>='0'&&c<='9')a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int n,m,S,T,to[M<<1],nxt[M<<1],head[N],tote;
ll L,d[N],dd[N],w[M<<1]; bool vis[N];
inline void adde(int a,int b,ll c) {
	to[tote]=b,nxt[tote]=head[a],w[tote]=c;
	head[a]=tote++;
}
inline void dijstra(bool fl) {
	int i,j,k,u,v; ll t;
	memset(vis,0,N),memset(d,62,sizeof d);
	for(d[fl?S:T]=i=0;i<n;++i) {
		for(j=0,u=n;j<n;++j) (!vis[j]&&d[j]<d[u])?u=j:1;
		vis[u]=true;
		for(j=head[u];~j;j=nxt[j]) {
			v=to[j],t=w[j];
			if(fl) {
				if(!t) t=max(L-d[u]-dd[v],1LL);
				w[j]=w[j^1]=t; d[v]=min(d[v],d[u]+t);
			}else if(t) d[v]=min(d[v],d[u]+t);
		}
	}
}
int main() {
	int i,j,k,a,b,c;
	n=geti(),m=geti(),L=geti(),S=geti(),T=geti();
	memset(head,-1,sizeof head);
	while(m--) {
		a=geti(),b=geti(),c=geti();
		adde(a,b,c),adde(b,a,c);
	}dijstra(0);
	if(d[S]<L) return puts("NO"),0;
	memcpy(dd,d,sizeof d); dijstra(1);
	if(d[T]>L) return puts("NO"),0;
	puts("YES");
	for(i=0;i<tote;i+=2)
		printf("%d %d %I64d\n",to[i^1],to[i],w[i]);
	return 0;
}
