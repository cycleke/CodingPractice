#include<cstdio>
#include<queue>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
#define maxe 2000000
#define ni (c<'0'|'9'<c)
inline int geti() {
    register int a; register char c,f=0;
    while(c=getchar(),ni)f|=c=='-';a=c-'0';
    while(c=getchar(),!ni)a=(a<<3)+(a<<1)+c-'0';
    return f?-a:a;
}
struct edge{
    int to,weight;
    edge* next;
}*head[maxe],CD[maxe*5],*cd=CD;
  
int S,T,n,m;
bool inq[maxe];
int d[maxe];
int f[maxe];
inline void adde(const int& a,const int& b,const int& c)
{
    cd->to = b,cd->weight = c;
    cd->next = head[a];
    head[a] = cd++;
}
  
inline void input()
{
    int e=1,f=2,i,j,a,b,c;
    for(i=0,a,b,c;i<n;++i)
        for(j=1;j<m;++j){
            c=geti();
            if(!i) a=T,b=f,f+=2;
            else if(i==n-1) a=e,b=0,e+= 2;
            else a=e,b=f,e+=2,f+=2;
            adde(a,b,c);
            adde(b,a,c);
        }
    e = 1,f = 2;
    for(i=1;i<n;++i)
        for(j=0;j<m;++j)
        {
            c=geti();
            if(!j) a=0,b=e,e+=2;
            else if(j==m-1) a=f,b=T,f+=2;
            else a=e,b=f,e+=2,f+=2;
            adde(a,b,c);adde(b,a,c);
        }
    e = 1,f = 2;
    for(i = 1,c;i < n;++i)
        for(j = 1;j < m;++j)
        {
            c=geti();
            adde(e,f,c);
            adde(f,e,c);
            e+=2,f+=2;
        }
}
queue<int>q;
void work()
{
    memset(d,127,sizeof(d));
    d[0] = 0; edge *i;
    int s,v; q.push(0);
    while(!q.empty())
    {
        s=q.front();q.pop();
        inq[s] = false;
        for(i=head[s];i;i=i->next){
            if(d[v=i->to]>d[s]+i->weight){
                d[v]=d[s]+i->weight;
                f[v]=s;
                if(!inq[v]){
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    printf("%d",d[T]);
}
  
int main()
{
    n=geti(),m=geti();
    T = (n - 1)*(m - 1)*2 + 1;
    if(n == 1 || m == 1){
        int ans = 1 << 30;
        int a;
        while(scanf("%d",&a) == 1) ans = min(a,ans);
        printf("%d\n",ans);
        return 0;
    }
    input();
    work();
    return 0;
}
