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
ll k;
int n;
char s[105];
bool del[105];
ll getv(){
    ll t = 0;
    fo(i,1,n){
        if(del[i])continue;
        t=t+t+(s[i]-'0');
    }
    return t;
}
int main()
{
    k=read();
    scanf("%s",s+1);
    int ans=0,fst=-1;
    n=strlen(s+1);
    fo(i,1,n-1){
        if(s[i]=='1'){
            fst=i;
            break;
        }
        ans++;
        del[i]=true;
    }
    if(getv()<=k){
        cout<<ans;
        return 0;
    }
    fo(i,1,n){
        if(del[i]||s[i]=='0'||i==fst)continue;
        del[i]=true;ans++;
        if(getv()<=k){
            cout<<ans;
            return 0;
        }
    }
    fo(i,1,n){
        if(del[i]||s[i]=='1')continue;
        del[i]=true;ans++;
        if(getv()<=k){
            cout<<ans;
            return 0;
        }
    }

    return 0;
}
