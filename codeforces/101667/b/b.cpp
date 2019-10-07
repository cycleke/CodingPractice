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
#include <map>
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
struct dat{
    int col[8][8];
    int h[5];
}now,nxt;
int st,xx,yy;
int ans[10][10];
map<ll,bool> tb[5][5];
bool jud(dat st,int p){
    fo(i,1,4){
        fo(j,1,4){
            if(st.col[i][j]==p&&st.col[i][j+1]==p&&st.col[i][j+2]==p)return true;
            if(st.col[i][j]==p&&st.col[i+1][j]==p&&st.col[i+2][j]==p)return true;
            if(st.col[i][j]==p&&st.col[i+1][j+1]==p&&st.col[i+2][j+2]==p)return true;
            if(i>=3)if(st.col[i][j]==p&&st.col[i-1][j+1]==p&&st.col[i-2][j+2]==p)return true;
        }
    }
    return false;
}
ll getv(dat st){
    ll ret = 0;
    fo(i,1,4){
        fo(j,1,4){
            ret=ret*3+st.col[i][j];
        }
    }
    return ret;
}
void dfs(int player,dat st){
    if(jud(st,2)){
        ll hash=getv(st);
        if(tb[xx][yy].count(hash)==0){
            tb[xx][yy][hash]=true;
            ans[xx][yy]++;
        }
        return;
    }
    if(jud(st,1)){
        return;
    }
    fo(i,1,4){
        nxt = st;
        if(nxt.h[i]>=4)continue;
        nxt.h[i]++;
        nxt.col[nxt.h[i]][i] = player;
        xx=nxt.h[i];
        yy=i;
        dfs(3-player,nxt);
    }
}
int main()
{
    st=read();
    now.col[1][st]=1;
    now.h[st]=1;
    dfs(2,now);
    int uu=read(),vv=read();
    cout<<ans[uu][vv];
    return 0;
}

