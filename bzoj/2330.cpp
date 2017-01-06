#include <cstdio>
#include <cstring>
inline int gi() {
    static int a; static char c;
    while(c=getchar(),c<'0');a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return a;
}
inline void cmin(int&a,const int&b) {if(b<a)a=b;}
inline void cmax(int&a,const int&b) {if(a<b)a=b;}
#define N 100005
struct edge{int to;edge*nt;}ME[N<<1],*CE=ME,*h1[N],*h2[N];
inline void add1(int a,int b) {//a<b
    CE->to=b,CE->nt=h1[a],h1[a]=CE++;
}
inline void add2(int a,int b) {//a<=b
    CE->to=b,CE->nt=h2[a],h2[a]=CE++;
}
struct e{int to,v;e*nt;}me[N<<1],*ce=me,*he[N];
inline void adde(int a,int b,int c) {
    ce->to=b,ce->nt=he[a],ce->v=c,he[a]=ce++;
}
int dfn[N],bel[N],bcnt,Stack[N],tp,_clock,n,deg[N],size[N];
int tarjan(int u) {
    int low=dfn[u]=++_clock,v;
    Stack[++tp]=u;
    for(edge*it=h2[u];it;it=it->nt)
        if(!dfn[v=it->to]) cmin(low,tarjan(v));
        else if(!bel[v]) cmin(low,dfn[v]);
    if(low==dfn[u]) {
        ++bcnt;
        do {
            v=Stack[tp--];
            bel[v]=bcnt;
            ++size[bcnt];
        } while(u^v);
    }
    return low;
}
int val[N];
long long tpsort() {
    long long ret=0;
    int i,u,v,cnt=0; e*it;
    for(i=1;i<=bcnt;++i)
        if(!deg[i])Stack[++tp]=i,val[i]=1;
    while(tp) {
        u=Stack[tp--]; ++cnt;
        ret+=(long long)val[u]*size[u];
        for(it=he[u];it;it=it->nt) {
            v=it->to;
            cmax(val[v],val[u]+it->v);
            if(!(--deg[v])) Stack[++tp]=v;
        }
    }
    if(cnt^bcnt) return -1LL;
    else return ret;
}
//1:a<b 2:a<=b;
int main() {
    int a,b,x,k;
    edge*it;
    n=gi(),k=gi();
    while(k--) {
        x=gi(),a=gi(),b=gi();
        if(x==1) add2(a,b),add2(b,a);
        else if(x==2) {if(a^b)add1(a,b);else return puts("-1"),0;}
        else if(x==3) add2(b,a);
        else if(x==4) {if(a^b)add1(b,a);else return puts("-1"),0;}
        else add2(a,b);
    }
    for(a=1;a<=n;++a)if(!dfn[a])tarjan(a);
    for(a=1;a<=n;++a) {
        for(it=h1[a];it;it=it->nt)
            if(bel[a]^bel[b=it->to]) adde(bel[a],bel[b],1),++deg[bel[b]];
            else return puts("-1"),0;
        for(it=h2[a];it;it=it->nt)
            if(bel[a]^bel[b=it->to]) adde(bel[a],bel[b],0),++deg[bel[b]];
    }
    printf("%lld\n",tpsort());
    return 0;
}
