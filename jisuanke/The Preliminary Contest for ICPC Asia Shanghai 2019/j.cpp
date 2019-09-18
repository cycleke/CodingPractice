// by sineMora
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define ll long long
using namespace std;
const int maxn = 1000050;
const ll mod = 1e9 + 7;
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
int a[305];
ll dp[305*505];
int cmp(int a,int b){
    return a>b;
}
int main()
{
    int T = read();int tt=0;
    while (T--)
    {
        n=read();
        m=0;
        fo(i,1,n){
            a[i]=read();
            m+=a[i];
        }
        sort(a+1,a+1+n,cmp);
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        ll ans = 0;
        fo(i,1,n){
            fd(j,1,m){
                if(j<a[i])break;
                dp[j] = (dp[j]+dp[j-a[i]])%mod;
                if(j>=m-j&&j-a[i]<=m-j){
                    ans = (ans + dp[j-a[i]]) % mod;
                }

            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
