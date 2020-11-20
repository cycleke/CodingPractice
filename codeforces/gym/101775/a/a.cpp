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
const int maxn = 100050;
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
ll fac[maxn];
ll inv[maxn];
ll C(ll n,ll m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
ll qpow(ll x,ll y){
    ll ret = 1;
    while(y){
        if(y&1){
            ret = (ret*x)%mod;
        }
        x = (x*x)%mod;
        y >>= 1;
    }
    return ret;
}
ll n,k;
int main(){
    fac[0]=fac[1]=1;
    fo(i,2,maxn-1){
        fac[i] = (fac[i-1]*i)%mod;
    }
    inv[0]=inv[1] = 1;
    fo(i,2,maxn-1){
        inv[i]=(mod-(mod/i))*inv[mod%i]%mod;
    }
    int T=read(),tt=0;
    ll ans1,ans2,nowc;
    while(T--){
        n=read();k=read();
        ans2=0;
        ans1=nowc=1;
        fo(i,1,k-1){
            nowc = nowc*(n-i+1)%mod*inv[i]%mod;
            ans1 += nowc;
            ans1 %= mod;
        }
        ans2 = qpow(2,n) + mod;
        ans2 -= ans1;
        ans2 %= mod;
        printf("Case #%d: %lld\n",++tt,ans2);
    }
    return 0;
}
