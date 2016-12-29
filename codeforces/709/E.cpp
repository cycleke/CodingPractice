#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define N 400005
int to[N<<1],nxt[N<<1],head[N],fa[N],siz[N],can[N],tote,n,root;
#define adde(a,b) (to[tote]=b,nxt[tote]=head[a],head[a]=tote++)
void getroot(int u) {
	int b=1,v; siz[u]=1;
	for(int i=head[u];~i;i=nxt[i])
		if((v=to[i])^fa[u]) {
			fa[v]=u; getroot(v);
			(n>>1)<siz[v]?b=0:1;
			siz[u]+=siz[v];
		}
	if(b&&siz[u]>=(n-1)/2+1) root=u;
}
int fir,sec,pfir,psec;
void fir_sec() {
	for(int i=head[root];~i;i=nxt[i])
		if(siz[to[i]]>fir) fir=siz[pfir=to[i]];
	for(int i=head[root];~i;i=nxt[i])
		if(siz[to[i]]>sec&&to[i]!=pfir) sec=siz[psec=to[i]];
}
void getans(int u,bool flag) {
	if(u==pfir) flag=true;
	siz[u]+=flag?sec:fir;
	if(siz[u]>=(n-1)/2+1) can[u]=1;
	if(flag&&fir*2==n) can[u]=1;
	for(int i=head[u];~i;i=nxt[i])
		if(to[i]^fa[u]) getans(to[i],flag);
}
int main() {
	int a,b;
	scanf("%d",&n);
	memset(head,-1,sizeof head);
	for(int i=1;i<n;++i) {
		scanf("%d%d",&a,&b);
		adde(a,b),adde(b,a);
	}getroot(1);
	if(root^1) memset(fa,0,sizeof fa),getroot(root);
	fir_sec(); getans(root,0);
	for(int i=1;i<=n;++i) printf("%d ",can[i]);
	return 0;
}
