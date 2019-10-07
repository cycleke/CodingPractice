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
const int maxn = 1000500;
const ll mod = 70177;
const ll sed = 131;
const ull Sed = 31;
const double eps = 1e-9;
const double pi = acos(-1);
const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
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
int main()
{
    
    int x1=0,x2=0,y1=0,y2=0;
    int xx=0,yy=0;
    int dir=0,delta,len;
    n=read();
    fo(i,1,n){
        len=read();delta=read();
        if(dir==0){
            len=(y2-yy+1);
            if(len<1)len=1;
            if(len>n)len=n;
            yy+=len;
            y2=max(yy,y2);
        }else if(dir==1){
            len=(xx-x1+1);
            if(len<1)len=1;
            if(len>n)len=n;
            xx-=len;
            x1=min(xx,x1);
        }else if(dir==2){
            len=(yy-y1+1);
            if(len<1)len=1;
            if(len>n)len=n;
            yy-=len;
            y1=min(yy,y1);
        }else if(dir==3){
            len=(x2-xx+1);
            if(len<1)len=1;
            if(len>n)len=n;
            xx+=len;
            x2=max(x2,xx);
        }
        printf("%d ",len);
        dir=(dir+delta+4)%4;
    }
    return 0;
}

