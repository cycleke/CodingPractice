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
int n;
string s[17][1<<17];
char tmp[17][17];
int len[17],lm[17];
int dp[17][1<<17];
int main()
{
    n=read();
    fo(i,1,n){
        scanf("%s",tmp[i]+1);
        len[i]=strlen(tmp[i]+1);
    }
    fo(i,1,n){
        lm[i] = (1<<len[i])-1;
        fo(j,1,lm[i]){
            s[i][j]="";
            for(int k = 1,p=1;k <= j;k <<= 1,p++){
                if(j&k){
                    s[i][j]+=tmp[i][p];
                }
            }
        }
        sort(s[i]+1,s[i]+1+lm[i]);
    }
    memset(dp,-1,sizeof(dp));
    dp[1][0]=0;
    fo(i,1,lm[1]){
        dp[1][i]=max(dp[1][i-1],(int)s[1][i].length());
    }
    dp[1][0]=-1;
    int ans=-1;
    fo(i,2,n){
        int p = 0;
        fo(j,1,lm[i]){
            dp[i][j]=dp[i][j-1];
            while(p<lm[i-1]&&s[i][j]>s[i-1][p+1])p++;
            if(dp[i-1][p]>0)dp[i][j]=max(dp[i][j],dp[i-1][p]+(int)s[i][j].length());
        }
    }
    fo(i,1,lm[n]){
        ans=max(ans,dp[n][i]);
    }
    cout<<ans;

    return 0;
}
