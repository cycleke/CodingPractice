#include <cstdio>
#include <cstring>
char inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
    register int a; register char c,f=0;
    while(c=getc(),c<'0'||'9'<c)f|=c=='-';a=c-'0';
    while(c=getc(),!(c<'0'||'9'<c))a=(a<<3)+(a<<1)+c-'0';
    return f?-a:a;
}
#define N 1610
#define M 20000
const long long inf=1LL<<50;
int d[N],dt[N],S,T,la[N];
int to[M],nt[M],hd[N],n,m,te;
long long C[M];
int mp[42][42],idx[42][42];
inline void adde(int a,int b,long long c) {
    to[te]=b;nt[te]=hd[a];C[te]=c;hd[a]=te++;
    to[te]=a;nt[te]=hd[b];C[te]=0;hd[b]=te++;
}
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
long long dfs(int u,long long flow) {
    if(u==T||!flow)return flow;
    long long r=0,t;
    for(int&i=la[u];~i;i=nt[i])
        if(d[u]==d[to[i]]+1&&C[i]>0) {
            t=dfs(to[i],flow<C[i]?flow:C[i]);
            r+=t,flow-=t;
            C[i]-=t,C[i^1]+=t;
            if(d[S]>T+1||!flow)return r;
        }
    la[u]=hd[u];
    if(!(--dt[d[u]]))d[S]=T+2;
    ++dt[++d[u]];return r;
}
inline bool check(long long x) {
    memset(hd,-1,sizeof hd);
    int i,j,k,_i,_j; te=0;
    long long t=0,st=0;
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
            if((i+j)&1) {
                adde(S,idx[i][j],x-mp[i][j]);
                st+=x-mp[i][j];
                for(k=0;k^4;++k) {
                    _i=i+dx[k],_j=j+dy[k];
                    if(_i<1||_j<1||_i>n||_j>m)continue;
                    adde(idx[i][j],idx[_i][_j],inf);
                }
            }else adde(idx[i][j],T,x-mp[i][j]);
    i=j=0;dt[j++]=T;
    memset(d,0,sizeof d);
    d[T]=1;
    while(i<j) {
        k=dt[i++];
        for(_i=hd[k];~_i;_i=nt[_i])
            if(!d[to[_i]])d[dt[j++]=to[_i]]=d[k]+1;
    }
    memset(dt,0,sizeof dt);
    for(i=S;i<=T;++i)++dt[d[i]],la[i]=hd[i];
    while(d[S]<T+2)t+=dfs(S,inf);
    return st==t;
}
#define getskip(a) (a*n*m-s0-s1)>>1
int main() {
    int __=geti(),i,j,id;
    long long s0,s1,mv,l,r,mi,an;
    while(__--) {
        n=geti(),m=geti();
        s0=s1=0LL;mv=-inf;
        for(id=0,i=1;i<=n;++i)
            for(j=1;j<=m;++j) {
                if((mp[i][j]=geti())>mv)mv=mp[i][j];
                if((i+j)&1)s1+=mp[i][j];
                else s0+=mp[i][j];
                idx[i][j]=++id;
            }
        S=0,T=++id;
        if(n*m&1) {
            l=s0-s1;
            if(l>=mv&&check(l))printf("%lld\n",getskip(l));
            else puts("-1");
        }else {
            if(s0^s1){puts("-1");continue;}
            for(l=mv,r=inf;l<=r;) {
                mi=l+r>>1;
                if(check(mi))r=(an=mi)-1;
                else l=mi+1;
            }
            printf("%lld\n",getskip(an));
        }
    }
    return 0;
}
