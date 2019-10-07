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
#define fo(i, l, r) for (long long i = l; i <= r; i++)
#define fd(i, l, r) for (long long i = r; i >= l; i--)
#define mem(x) memset(x, 0, sizeof(x))
#define ll long long
#define ld double
#define ull unsigned long long
using namespace std;
const int maxn = 100050;
const ll mod = 70177;
const ll sed = 131;
const ull Sed=31;
const double eps = 1e-9;
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
int n,m,ind[maxn],dp[maxn],ans;
vector<int> g[maxn];
void dfs(int u){
    dp[u]=1;
    int sz = (int)g[u].size()-1;
    int v;
    fo(i,0,sz){
        v=g[u][i];
        if(ind[v]<=ind[u])continue;
        if(!dp[v])dfs(v);
        dp[u]=max(dp[u],dp[v]+1);
    }
}
int main()
{
    int u,v;
    n=read();m=read();
    fo(i,1,m){
        u=read();v=read();
        g[u].push_back(v);
        g[v].push_back(u);
        ind[u]++;ind[v]++;
    }
    fd(i,0,n-1){
        if(!dp[i])dfs(i);
    }
    fo(i,0,n-1) ans = max(ans,dp[i]);
    cout<<ans;
    return 0;
}

