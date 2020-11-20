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
void kmp_pre(int x[], int m, int next[])
{
    int i, j;
    j = next[0] = -1;
    i = 0;
    while (i < m)
    {
        while (-1 != j && x[i] != x[j])
            j = next[j];
        next[++i] = ++j;
    }
}
int nxt[maxn];
int n,a[maxn];
int pp=maxn+1,kk=maxn+1;
int main()
{
    n=read();
    fd(i,1,n){
        a[i]=read();
    }
    kmp_pre(a+1,n,nxt);
    int nowp,nowk;
    fo(i,1,n){
        nowp=i-nxt[i];
        nowk=n-i;
        if(nowp+nowk<pp+kk||(nowp+nowk==pp+kk&&nowp<pp)){
            pp=nowp;
            kk=nowk;
        }
    }
    cout<<kk<<" "<<pp<<endl;
    return 0;
}

