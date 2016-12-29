#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
#define N 100005
int to[N<<1],nxt[N<<1],head[N],tote,w[N<<1];
inline void adde(int a,int b,int c) {to[tote]=b,nxt[tote]=head[a],w[tote]=c,head[a]=tote++;}
int n,m,flag,cir[N],tot,idx[N],pre[N],nex[N],fa[N],son[N];
double len[25][25],up[N],down[N];
bool vis[N];
#define FOR(a,b) for(int a=head[b];~a;a=nxt[a])
void findcir(int u,int f) {
    vis[u]=true;
    FOR(i,u) if(to[i]^f) {
        if(vis[to[i]]) {flag=to[i]; return;}
        findcir(to[i],u);
        if(flag>0) {if(flag==u) flag=-1; return;}
        if(flag<0) break;
    }vis[u]=false;
}

void dfscir(int u,int f) {
    if(idx[u]) return;
    cir[++tot]=u,idx[u]=tot,fa[u]=2;
    FOR(i,u) if((to[i]^f)&&vis[to[i]]) {
        pre[to[i]]=u;
        nex[u]=to[i];
        dfscir(to[i],u);
        len[idx[u]][idx[to[i]]]=len[idx[to[i]]][idx[u]]=w[i];
		break;
    }
}

void dfsdown(int u,int f) {
	FOR(i,u) if(!vis[to[i]]&&(to[i]^f)) {
		fa[to[i]]=1; dfsdown(to[i],u);
		++son[u]; down[u]+=down[to[i]]+w[i];
	}(son[u])?down[u]/=son[u]:1.;
}
void dfsup(int u,int f,int e) {
	up[u]=e;
	if(fa[f]+son[f]>1)
		up[u]+=(fa[f]*up[f]+son[f]*down[f]-down[u]-e)/(fa[f]+son[f]-1.);
	FOR(i,u) if(to[i]^f) dfsup(to[i],u,w[i]);
}
int main() {
	n=geti(),m=geti();
	memset(head,-1,sizeof head);
	for(int i=0;i<m;++i) {
		int a=geti(),b=geti(),c=geti();
		adde(a,b,c); adde(b,a,c);
	}
	if(m<n) {
		dfsdown(1,0);
		FOR(i,1) dfsup(to[i],1,w[i]);
	} else {
		findcir(1,0);
		for(int i=1;i<=n;++i) if(vis[i]) {dfscir(i,0); break;}
		for(int i=1;i<=tot;++i) dfsdown(cir[i],0);
		for(int i=1;i<=tot;++i) {
			int u=cir[i]; double k=1.;
			for(int j=nex[u];j^u;j=nex[j]){
				if(nex[j]^u)
					up[u]+=k*(len[idx[pre[j]]][idx[j]]+down[j]*son[j]/(son[j]+1.0));
				else
					up[u]+=k*(len[idx[pre[j]]][idx[j]]+down[j]);
				k/=son[j]+1.0;
			} k=1;
			for(int j=pre[u];j^u;j=pre[j]) {
				if(pre[j]^u)
					up[u]+=k*(len[idx[nex[j]]][idx[j]]+down[j]*son[j]/(son[j]+1.0));
				else
					up[u]+=k*(len[idx[nex[j]]][idx[j]]+down[j]);
				k/=son[j]+1.0;
			}
			up[u]/=2.0;
		}
		for(int j=1;j<=tot;++j)
			FOR(i,cir[j]) if(!idx[to[i]]) dfsup(to[i],cir[j],w[i]);
	}
	double ans=0;
	for(int i=1;i<=n;++i)
		ans+=(up[i]*fa[i]+down[i]*son[i])/(fa[i]+son[i]);
	return printf("%.5lf\n",ans/n),0;
}
