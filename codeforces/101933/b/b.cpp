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
const int maxn = 10000500;
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
char tmp[15];
int a[maxn];
int main()
{
    n=read();
    fo(i,1,n){
        scanf("%s",tmp+1);
        if(tmp[1]=='m') a[i]=-1;
        else{
            int t = 0,len=strlen(tmp+1);
            fo(j,1,len){
                t=t*10+(tmp[j]-'0');
            }
            a[i] = t;
        }
    }
    bool fst = false,ok = true;
    int cnt=0;
    fo(i,1,n){
        if(!fst){
            if(a[i]==-1)cnt++;
            else{
                fst=true;
                if(a[i]<=cnt)ok=false;
                cnt=a[i];
            }
            
        }else{
            cnt++;
            if(a[i]!=-1&&cnt!=a[i])ok=false;
        }
    }
    if(ok) cout<<"makes sense";
    else cout<<"something is fishy";//cnisssnzg is me
    return 0;
}
