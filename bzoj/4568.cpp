#include <cstdio>
#include <cstring>
char inb[1<<16],*ins=inb,*ine=inb;
#define getc (((ins==ine)&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
inline long long getll() {
	register long long a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 20002
#define Q 200002
long long a[N][61],t[61],val[N],ans[Q];
inline void add_val(long long val,long long*c) {
	for(register int i=59;(~i)&&val;--i)
		if(val>>i&1) (c[i])?(val^=c[i]):(c[i]=val,val=0);
}
inline long long quy(long long*c) {
	long long r=0;
	for(register int i=59;~i;--i)
		if((r^c[i])>r)r^=c[i];
	return r;
}
int to[N<<1],nt[N<<1],hd[N],te;
#define adde(a,b) (to[te]=b,nt[te]=hd[a],hd[a]=te++)
int tq[Q<<5],nq[Q<<5],hq[N],cq,U[Q],V[Q];
#define addq(a,b) (tq[cq]=b,nq[cq]=hq[a],hq[a]=cq++)
int siz[N],rt,mif,all,ps[N],st[Q]; bool vis[N];
void getroot(const int&u,const int&fa) {
	int f=0;siz[u]=1;
	for(int i=hd[u];~i;i=nt[i])
		if(!vis[i>>1]&&(to[i]^fa)) {
			getroot(to[i],u);
			siz[u]+=siz[to[i]];
			if(siz[to[i]]>f) f=siz[to[i]];
		}
	if(all-siz[u]>f) f=all-siz[u];
	if(f<mif) rt=u,mif=f;
}
#define mst(a) memset(a,0,sizeof a)
#define mcp(a,b) memcpy(a,b,sizeof a)
void dfs(const int&u,const int&fa,const int&anc) {
	ps[u]=anc; mcp(a[u],a[fa]);
	add_val(val[u],a[u]);
	for(int i=hd[u];~i;i=nt[i])
		if(!vis[i>>1]&&(to[i]^fa))dfs(to[i],u,anc);
}
void cal(const int&u) {
	if(!(~hq[u]))return;
	mif=all=siz[u];
	getroot(u,rt=0);
	ps[rt]=rt; mst(a[rt]);
	add_val(val[rt],a[rt]);
	for(int i=hd[rt];~i;i=nt[i])if(!vis[i>>1])dfs(to[i],rt,to[i]);
	int tp=0,x,y,i,j;
	for(i=hq[u];~i;i=nq[i])st[++tp]=tq[i];hq[u]=-1;
	for(i=1;i<=tp;++i)
		if(ps[x=U[st[i]]]==ps[y=V[st[i]]])addq(ps[x],st[i]);
		else {
			mcp(t,a[x]);
			for(j=59;~j;--j)if(a[y][j])add_val(a[y][j],t);
			ans[st[i]]=quy(t);
		}
	for(i=hd[rt];~i;i=nt[i])if(!vis[i>>1])vis[i>>1]=1,cal(to[i]);
}
int main() {
	register int n=geti(),q=geti(),i,a,b;
	for(i=1;i<=n;++i)val[i]=getll(),hq[i]=hd[i]=-1;
	for(i=1;i<n;++i){
		a=geti(),b=geti();
		adde(a,b);adde(b,a);
	}
	for(i=1;i<=q;++i) {
		U[i]=geti(),V[i]=geti();
		if(U[i]^V[i])addq(1,i);
		else ans[i]=val[U[i]];
	}
	siz[1]=n;cal(1);
	for(i=1;i<=q;++i)printf("%lld\n",ans[i]);
	return 0;
}
