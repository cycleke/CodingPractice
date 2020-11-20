#include <cstdio>
#include <cstring>
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9');ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9')ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
#define N 400005
int to[N<<1],nxt[N<<1],head[N],tote,n,fa[N],can[N],siz[N],root;
#define adde(a,b) (to[++tote]=b,nxt[tote]=head[a],head[a]=tote)
void getroot(int u) {
	int i,v,b=1; siz[u]=1;
	for(i=head[u];i;i=nxt[i])
		if((v=to[i])^fa[u]) {
			fa[v]=u; getroot(v);
			(n>>1)<siz[v]?b=0:1;
			siz[u]+=siz[v];
		}
	if(b&&siz[u]>=(n-1)/2+1) root=u;
}
int fir,sec,pfir,psec;
void fir_sec() {
	int u=root,i;
	for(i=head[u];i;i=nxt[i])
		if(siz[to[i]]>fir) fir=siz[pfir=to[i]];
	for(i=head[u];i;i=nxt[i])
		if((to[i]^pfir)&&siz[to[i]]>sec) sec=siz[psec=to[i]];
}
void getans(int u,bool b) {
	if(u==pfir) b=1;
	siz[u]+=b?sec:fir;
	if(siz[u]>=(n-1)/2+1) can[u]=1;
	if(b&&fir*2==n) can[u]=1;
	for(int i=head[u];i;i=nxt[i])
		if(to[i]^fa[u]) getans(to[i],b);
}
int main() {
	int i,a,b;
	for(n=geti(),i=1;i<n;++i) {
		a=geti(),b=geti();
		adde(a,b),adde(b,a);
	}getroot(1);
	if(root^1) memset(fa,0,sizeof fa),getroot(root);
	fir_sec(); getans(root,0);
	for(int i=1;i<=n;++i)
		printf("%d ",can[i]);
	return 0;
}
