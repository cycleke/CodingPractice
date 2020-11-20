#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define lson rt<<1,l,m
#define pi acos(-1)
#define rson rt<<1|1,m+1,r
#define fo(i,l,r) for(int i = l;i <= r;i++)
#define fd(i,l,r) for(int i = r;i >= l;i--)
#define mem(x) memset(x,0,sizeof(x))
#define eps 3e-11
using namespace std;
const ll maxn = 650;
const int maxm = 3050;
const ll mod = 998244353;
ll read() {
    ll x=0,f=1;
    char ch=getchar();
    while(!(ch>='0'&&ch<='9')) {
        if(ch=='-')f=-1;
        ch=getchar();
    };
    while(ch>='0'&&ch<='9') {
        x=x*10+(ch-'0');
        ch=getchar();
    };
    return x*f;
}
ll n,a[maxn];
ll tot = 100,cnt = 0;
int main() {
    n=read();
    fo(i,1,n)a[i]=read();
    a[0] = 1314520,a[n+1]=-1;
    fo(i,1,n){
        if(cnt==0 && a[i]<=a[i-1] && a[i] < a[i+1]){
            int buy=min(tot/a[i],100000ll);
            cnt += buy;
            tot -= buy*a[i];
        }
        if(cnt&& a[i]>=a[i-1] && a[i] > a[i+1]){
            tot += cnt*a[i];
            cnt = 0;
        }
    }
    cout<<tot;
    return 0;
}
