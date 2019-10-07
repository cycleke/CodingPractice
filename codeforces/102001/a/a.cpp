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
const int maxn = 100050;
const ll mod = 998244353;
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
char s[2050];
char t[2050];
int cnt0,cnt1,len;
int main()
{
    scanf("%s",s+1);
    len=strlen(s+1);
    fo(i,1,len){
        if(s[i]=='1')cnt1++;
        else cnt0++;
    }
    if(cnt0<cnt1){
        fo(i,1,len)putchar('0');
    }else if(cnt0>cnt1){
        fo(i,1,len)putchar('1');
    }else{
        if(s[1]=='0'){
            t[1]='1';
            fo(i,2,len)t[i]='0';
        }else{
            t[1]='0';
            fo(i,2,len)t[i]='1';
        }
        fo(i,1,len)putchar(t[i]);

    }
    return 0;
}
