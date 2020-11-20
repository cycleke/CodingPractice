// by cnisssnzg
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
using namespace std;
const int maxn = 1500;
const ll mod = 998244353;
const double eps = 1e-9;
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
int n;
int a[maxn],b[maxn];
int ans,t,tot;
int main()
{
    n=read();
    fo(i,1,n){
        a[i]=read();
        b[a[i]]++;
    }
    fo(i,1,365){
        tot += t;
        if(tot >= 20){
            ans++;
            t=tot=0;
        }
        t += b[i];
    }
    if(t)ans++;
    cout<<ans;
    return 0;
}
