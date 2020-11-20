// by cnissnzg
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
const int maxn = 100050;
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
ll a,b,c,d;
ll sumn[maxn];
vector<ll> n0,n1;
bool gao(ll p0,ll p1){
    if(p0==0&&p1==0)return false;
    if(b+c!=p0*p1)return false;
    if(p0==0){
        fo(i,1,p1)putchar('1');
        return true;
    }
    if(p1==0){
        fo(i,1,p0)putchar('0');
        return true;
    }
    ll fst=c/p0;
    ll p = p0-c%p0;
    fo(i,1,fst){
        putchar('1');
        p1--;
    }
    fo(i,1,p0){
        putchar('0');
        if(i==p&&p1){
            putchar('1');
            p1--;
        }
    }
    fo(i,1,p1){
        putchar('1');
    }
    return true;
}
int main()
{
    sumn[1] = 0;
    for(ll i = 2;i <= 100000;i++) sumn[i] = sumn[i-1] + i-1;
    a=read();b=read();c=read();d=read();
    fo(i,0,100000){
        if(a==sumn[i]) n0.push_back(i);
        if(d==sumn[i]) n1.push_back(i);
    }
    for(int i = 0;i < n0.size();i++){
        for(int j = 0;j < n1.size();j++){
            if(gao(n0[i],n1[j]))return 0;
        }
    }
    cout<<"impossible";
    return 0;
}

