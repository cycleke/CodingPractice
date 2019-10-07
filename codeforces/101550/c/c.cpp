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
const ll maxn = 250;
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
int n,tran[205],p[10],isinc[10],ans,dp[105],a[105];
char tmp[5];
struct dat{
    int kind;
    int v;
    int pos;
}dats[105];
bool cmp(dat a,dat b){
    if(a.kind != b.kind){
        return p[a.kind] < p[b.kind];
    }else{
        if(isinc[a.kind]==1){
            return a.v < b.v;
        }else{
            return a.v > b.v;
        }
    }
}
void solve(){
    sort(dats+1,dats+1+n,cmp);
    fo(i,1,n){
        a[dats[i].pos] = i;
    }
    int tot = 0;
    fo(i,1,n){
        dp[i]=1;
        fo(j,1,i-1){
            if(a[i]>a[j]) dp[i] = max(dp[i],dp[j]+1);
        }
        if(tot < dp[i]) tot = dp[i];
    }
    ans = min(ans,n-tot);

}
void gao(){
    fo(i,1,2){
        fo(j,1,2){
            fo(k,1,2){
                fo(l,1,2){
                    isinc[1]=i;isinc[2]=j;isinc[3]=k;isinc[4]=l;
                    solve();
                }
            }
        }
    }
}
int main() {
    tran['s']=1;tran['h']=2;tran['d']=3;tran['c']=4;
    fo(i,2,9) tran['0'+i] = i;
    tran['T']=10;tran['J']=11;tran['Q']=12;tran['K']=13;tran['A']=14;
    fo(i,1,4) p[i]=i;
    n=read();ans=n-1;
    fo(i,1,n){
        dats[i].pos=i;
        scanf("%s",tmp+1);
        dats[i].v=tran[tmp[1]];
        dats[i].kind=tran[tmp[2]];
    }
    do{
        gao();
    }while(next_permutation(p+1,p+1+4));
    cout<<ans;
    return 0;
}
