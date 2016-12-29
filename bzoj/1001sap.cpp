#include <cstdio>
#include <cstring>
const int M=1000*1000*6+20,N=1000*1000+10;
char inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
    register int a; register char c;
    while(c=getc(),c<'0');a=c-'0';
    while(c=getc(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return a;
}
int to[M],nxt[M],C[M],head[N],tote;
#define adde(a,b,c) {							\
		to[tote]=b,nxt[tote]=head[a],C[tote]=c;	\
		head[a]=tote++;							\
	}
#define min(a,b) (a<b?a:b)
int S,T,d[N],dt[N];
int dfs(int u,int flow) {
    if(u==T||!flow) return flow;
    int r=0,t,v;
    for(int i=head[u];~i;i=nxt[i])
        if(d[v=to[i]]+1==d[u]&&C[i]) {
            t=dfs(v,min(C[i],flow));
            r+=t,flow-=t;
            C[i]-=t,C[i^1]+=t;
            if(!flow||d[S]>T) return r;
        }
    if(!(--dt[d[u]])) d[S]=T+1;
    ++dt[++d[u]]; return r;
}
inline int SAP() {
    int *l=dt,*r=dt;
    register int ans=0,i;
    *r++=T; d[T]=1;
    while(l<r) {
        for(i=head[*l];~i;i=nxt[i])
            if(!d[to[i]]) d[*r++=to[i]]=d[*l]+1;
        ++l;
    }
    memset(dt,0,T+2<<2);
    for(i=S;i<=T;++i)
        ++dt[d[i]];
    while(d[S]<T+1) ans+=dfs(S,0x7f7f7f7f);
    return ans;
}
int main() {
    register int n=geti(),m=geti(),i,j,k;
    S=1,T=n*m;
    memset(head,-1,T+1<<2);
    for(i=1;i<=n;++i)
        for(j=1;j^m;++j) {
            k=geti();
            adde((i-1)*m+j,(i-1)*m+j+1,k);
            adde((i-1)*m+j+1,(i-1)*m+j,k);
        }
    for(i=1;i^n;++i)
        for(j=1;j<=m;++j) {
            k=geti();
            adde((i-1)*m+j,i*m+j,k);
            adde(i*m+j,(i-1)*m+j,k);
        }
    for(i=1;i^n;++i)
        for(j=1;j^m;++j) {
            k=geti();
            adde((i-1)*m+j,i*m+j+1,k);
            adde(i*m+j+1,(i-1)*m+j,k);
        }
    printf("%d\n",SAP());
    return 0;
}
