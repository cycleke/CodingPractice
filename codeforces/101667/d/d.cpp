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
ll f(ll x){
    ll res = 0;
    while(x){
        res += (x%10)*(x%10);
        x /= 10;
    }
    return res;
}
ll n;
int main()
{
    n=read();
    while(true){
        n=f(n);
        if(n==1){
            cout<<"HAPPY";
            break;
        }
        if(n==4){
            cout<<"UNHAPPY";
            break;
        }
    }
    return 0;
}

