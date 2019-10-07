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
#define double long double
#define ull unsigned long long
using namespace std;
const int maxn = 100500;
const ll mod = 1e9 + 7;
const double eps = 1e-20;
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
struct Point{
    ll x,y;
    Point(){}
    Point(ll _x,ll _y){
        x=_x;
        y=_y;
    }
    ll operator ^(const Point &b)const{
        return x*b.y - y*b.x;
    }
}pts[maxn];
int n;
ll gcd(ll x,ll y){
    if(x<y)swap(x,y);
    return y==0?x:gcd(y,x%y);
}
int main()
{
    n=read();
    fo(i,0,n-1){
        pts[i].x=read();pts[i].y=read();
    } 
    ll S=0,s=0;
    ll dy,dx,gxy;
    fo(i,0,n-1){
        S+=(pts[i]^pts[(i+1)%n]);
        dy=pts[i].y-pts[(i+1)%n].y;
        dx=pts[i].x-pts[(i+1)%n].x;
        dy=abs(dy);dx=abs(dx);
        if(dx==0){
            s+=dy+1;
        }else{
            gxy=gcd(dy,dx);
            s+=gxy+1;
        }
    }
    s-=n;
    S=fabs(S)/2;
    //cout<<s;
    cout<<S+1-s/2;
    return 0;
}

