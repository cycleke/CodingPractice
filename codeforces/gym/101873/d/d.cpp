// sineMora
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <ctime>
#include <random>
#include <map>
#define fo(i, l, r) for (long long i = l; i <= r; i++)
#define fd(i, l, r) for (long long i = r; i >= l; i--)
#define mem(x) memset(x, 0, sizeof(x))
#define ll long long
#define ld double
#define double long double
#define ull unsigned long long
using namespace std;
const int maxn = 305;
const ll mod = 1e9 + 7;
const double eps = 1e-20;
const double pi = acos(-1);
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (!(ch >= '0' && ch <= '9'))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    };
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    };
    return x * f;
}
int n,m;
map<string,int> mp;
vector<int> g[maxn];
char a[maxn],b[maxn];
string u,v;
int cnt,uu,vv;
bool vis[maxn];
bool dfs(int u,int v){
    if(u==v){
        return true;
    }
    vis[u]=true;
    int sz=(int)g[u].size()-1;
    fo(i,0,sz){
        if(vis[g[u][i]])continue;
        if(dfs(g[u][i],v))return true;
    }
    return false;

}
int main()
{
    n=read();m=read();
    fo(i,1,n){
        scanf("%s",a);
        fo(j,1,4)scanf("%s",b);
        u=a;
        v=b;
        if(mp.count(u)==0){
            mp[u]=++cnt;
        }
        if(mp.count(v)==0){
            mp[v]=++cnt;
        }
        uu=mp[u];
        vv=mp[v];
        g[uu].push_back(vv);
    }
    fo(i,1,m){
        scanf("%s",a);
        fo(j,1,4)scanf("%s",b);
        u=a;
        v=b;
        uu=mp[u];vv=mp[v];
        if(!uu||!vv){
            printf("Pants on Fire\n");
            continue;
        }
        mem(vis);
        if(dfs(uu,vv)){
            printf("Fact\n");
            continue;
        }
        mem(vis);
        if(dfs(vv,uu)){
            printf("Alternative Fact\n");
            continue;
        }
        printf("Pants on Fire\n");
        
    }
    return 0;
}

