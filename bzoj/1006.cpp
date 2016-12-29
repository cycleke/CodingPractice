#include <cstdio>
#include <cstring>
inline int geti() {
    register int a; register char c;
    while(c=getchar(),c<'0');a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return a;
}
#define N 10005
#define M 3000005
struct E{int to;E*nxt;}CD[M],*cd=CD,*head[N],*st[N];
inline void adde(int a,int b) {cd->to=b,cd->nxt=head[a],head[a]=cd++;}
inline void ins(int a,int b) {cd->to=b,cd->nxt=st[a],st[a]=cd++;}
int d[N],col[N],q[N],vis[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("1006.in","r",stdin);
    freopen("1006.out","w",stdout);
#endif
    register int n=geti(),m=geti(),i,j,mx,v; E*it;
    while(m--) adde(i=geti(),j=geti()),adde(j,i);
    mx=m=0;
    for(i=1;i<=n;++i) ins(0,i);
    while(m<n) {
        if(!st[mx]) {--mx; continue;}
        if(vis[st[mx]->to]) {st[mx]=st[mx]->nxt; continue;}
        v=st[mx]->to;
        vis[v]=1; q[m++]=v;
        st[mx]=st[mx]->nxt;
        for(it=head[v];it;it=it->nxt)
            if(!vis[j=it->to]) {
                (++d[j]>mx)?mx=d[j]:1;
                ins(d[j],j);
            }
    }
    memset(vis,0,sizeof vis);
    for(mx=0,i=0;i<n;++i) {
        v=q[i];
        for(it=head[v];it;it=it->nxt)
            vis[col[it->to]]=v;
        for(j=1;;++j)if(vis[j]^v)break;
        if((col[v]=j)>mx) mx=j;
    }
    printf("%d\n",mx);
    return 0;
}
