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
const int maxn = 670500;
const ll mod = 70177;
const ll sed = 131;
const ull Sed = 31;
const double eps = 1e-9;
const double pi = acos(-1);
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
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
int n, m;
int Y1[maxn], Y2[maxn];
bool vis1[maxn],vis2[maxn];
int ya, yb, nxta, nxtb;
ll ans1;
ll ans2, tmp;
int main()
{
    n = read();
    m = read();
    ya = read();
    int x;
    fo(i, 1, n)
    {
        x = read();
        Y1[x] = read();
        vis1[x]=true;
    }
    yb = read();
    fo(i, 1, m)
    {
        x = read();
        Y2[x] = read();
        vis2[x]=true;
    }
    bool flag = false;
    fo(i, 0, 60000)
    {
        nxta = ya;
        nxtb = yb;
        if (flag)
        {
            tmp += abs(ya - yb);
        }
        if (vis1[i])
            nxta = Y1[i];
        if (vis2[i])
            nxtb = Y2[i];
        if (ya >= yb && nxta < nxtb)
        {
            flag = true;
            tmp = 0;
        }
        if (ya < yb && nxta >= nxtb)
        {
            if (flag)
            {
                flag = false;
                ans2 += tmp;
                ans1++;
            }
            tmp = 0;
        }
        ya = nxta;
        yb = nxtb;
    }
    cout << ans1 << " " << ans2;
    return 0;
}

