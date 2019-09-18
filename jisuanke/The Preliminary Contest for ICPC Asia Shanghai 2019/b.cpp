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
struct dat{
    int v;
    bool isl;
    friend bool operator < (dat a,dat b){
        return a.v < b.v;
    }
}dats[2050];
int n,m;
int cnt,cnta;
int vv[2050],real[2050];
int main()
{
    int T = read();int tt=0;
    while (T--)
    {
        n=read();
        m=read();
        int u,v;
        memset(vv,0,sizeof(vv));
        memset(real,0,sizeof(real));
        cnt=0;cnta=0;
        fo(i,1,m){
            u=read();v=read();
            dats[++cnt].v = u;
            dats[cnt].isl=true;
            dats[++cnt].v=v+1;
            dats[cnt].isl=false;
        }
        sort(dats+1,dats+1+cnt);
        fo(i,1,cnt){
            if(i==1||dats[i].v!=dats[i-1].v){
                cnta++;
                real[cnta] = dats[i].v;
            }
            if(dats[i].isl) vv[cnta]++;
            else vv[cnta]--;
        }
        vv[++cnta]=n+1;
        int tot=0,ans=0;
        fo(i,1,cnta-1){
            tot += vv[i];
            if(tot&1)ans+=real[i+1]-real[i];
        }
        printf("Case #%d: %d\n",++tt,ans);
    }
    return 0;
}
