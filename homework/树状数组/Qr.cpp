#include <bits/stdc++.h>
#define y1 fjne9w8err
#define pf(x) ( (x) * (x) )
using namespace std;
typedef long long LL;

const int N = 2000 + 10;

int a[5],f[N];
int n;
int tr[2][N];
LL ans = 0,cnt1,cnt2;

void updata(int h0,int k,int num)
{
    while(k <= n)
    {
        tr[h0][k] += num ;
        k += k&-k;
    }
}

int query(int h0 , int k)///1~k¦Ì?????o¨ª
{
    int sum = 0;
    while(k)
    {
        sum += tr[h0][k];
        k -= k&-k;
    }
    return sum;
}

bool cmp(int a,int b){return a > b;}

void myreverse()
{
    swap(a[1],a[4]),swap(a[2],a[3]);
    for(int i = 1;i * 2 <= n;i++)
      swap(f[i] , f[n - i + 1]);
}

void init()
{
    scanf("%d",&n);
    for(int i = 1;i <= 4;i++)
      scanf("%d",&a[i]);
    for(int i = 1;i <= n;i++)
      scanf("%d",&f[i]);
}

bool check(int ai,int aj)
{
    if(ai > aj) swap(ai,aj);
    if(ai == 2 && aj == 3) return true;
    if(ai + aj == 6 || ai + aj == 4) return true;
    return false;
}

int getcnt(int ai,int h0,int fi,int fj)
{
    if(ai == 1) return query(h0,min(fi,fj) - 1);
    if(ai == 2 || ai == 3) return query(h0,max(fi,fj) - 1) - query(h0,min(fi,fj));
    if(ai == 4) return query(h0,n) - query(h0,max(fi,fj));
}

void solve1()
{
    for(int i = 1;i < n - 2;i++)
    {
        memset(tr,0,sizeof(tr));
        for(int j = i + 2;j <= n;j++) updata(1,f[j],1);

        for(int j = i + 2;j < n;j++)
        {
            updata(0,f[j - 1],1);
            updata(1,f[j],-1);
            if(cmp(f[i] , f[j]) == cmp(a[1] , a[3]))
            {
                cnt1 = getcnt(a[2],0,f[i],f[j]);
                cnt2 = getcnt(a[4],1,f[i],f[j]);
                ans += cnt1 * cnt2;
            }
        }
    }
}

void solve2()
{
    for(int i = 2;i < n - 1;i++)
    {
        for(int j = 1;j <= n;j++) tr[1][j] = 0;
        updata(0,f[i - 1],1);
        for(int j = n - 1;j > i;j--)
        {
            updata(1,f[j + 1],1);
            if(cmp(f[i] , f[j]) == cmp(a[2] , a[3]))
            {
                cnt1 = getcnt(a[1],0,f[i],f[j]);
                cnt2 = getcnt(a[4],1,f[i],f[j]);
                ans += cnt1 * cnt2;
            }
        }
    }
}

void solve3()
{
    for(int i = 1;i < n - 2;i++)
    {
        memset(tr,0,sizeof(tr));
        for(int j = i + 2;j <= n;j++) updata(1,f[j],1);
        for(int j = i + 2;j < n;j++)
        {
            updata(0,f[j - 1],1);
            updata(1,f[j],-1);
            if(f[i] > f[j])
            {
                cnt1 = getcnt(4,0,f[i],f[j]);
                cnt2 = getcnt(4,1,f[i],f[j]);
                ans += cnt1 * cnt2;
            }
        }
    }
}

void work()
{
    if( check(a[1],a[3]) ) solve1();
    else if( check(a[2],a[3]) ) solve2();
    else if( check(a[2],a[4]) ) myreverse(),solve1();
    else
    {
        if(a[1] == 3) myreverse();
        swap(a[2],a[4]); solve2(); ans *= -1LL;
        solve3();
    }

    printf("%lld\n",ans);
}

int main()
{
    init();
    work();

    return 0;
}
