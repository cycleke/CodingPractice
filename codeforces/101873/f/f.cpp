// by sineMora
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
const int maxn = 100500;
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
const int MAXN = 1610;  //点数的最大值
const int MAXM = 155000; //边数的最大值
vector<int> g[MAXN];
int linker[MAXN];
bool used[MAXN];
int uN;
int a[MAXN];
bool b[MAXN];
void sve(){
    memcpy(a,linker,sizeof(a));
    memcpy(b,used,sizeof(b));
}
void lod(){
    memcpy(linker,a,sizeof(a));
    memcpy(used,b,sizeof(b));
}
bool dfs(int u)
{
    int sz = g[u].size();
    for (int i = 0;i<sz;i++)
    {
        int v = g[u][i];
        if (!used[v])
        {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v]))
            {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int res = 0;
    memset(linker,-1, sizeof(linker));
    for (int u = 0; u < uN; u++)
    {
        memset(used, false, sizeof(used));
        if (dfs(u))
            res++;
    }
    return res;
}
int vN,m;
int main()
{
    int u,v;
    uN=read();vN=read();m=read();
    fo(i,1,m){
        u=read();v=read();
        u--;v--;
        g[u].push_back(v);
    }
    int ans = hungary(),tmp=0,tot=0;
    uN+=2;
    fo(i,0,uN-3){
        g[uN-2]=g[uN-1] = g[i];
        sve();
        tot=0;
        fo(j,uN-2,uN-1){
            memset(used, false, sizeof(used));
            if (dfs(j))
            tot++;
        }
        tmp=max(tmp,ans+tot);
        lod();
    }
    cout<<tmp;
    return 0;
}

