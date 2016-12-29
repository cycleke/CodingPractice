#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
const int Maxn = 50010;
typedef long long ll;
struct data{
    ll i,a,b,c,k;
    bool operator < (const data& x)const{
        if(c==x.c) return i < x.i;
        return c > x.c;
    }
}A[Maxn],B[Maxn];
bool used[Maxn];
int ID[Maxn];

int main(){
    int N,M;
    scanf("%d%d",&N,&M);
    ll k,a,b,c,tot(-1);
    for(int i = 1;i <= M;++i){
        scanf("%lld%lld%lld%lld",&k,&a,&b,&c);
        A[i] = (data){i,a,b,c,k};
        if(k<2) B[++tot] = A[i];
    }
    sort(B,B+tot+1);
    for(int i = 0;i <= tot;++i){
        ID[B[i].i] = i;
    }
    for(int i = 1;i <= M;++i){
        if(A[i].k < 2) used[ID[i]] = true;
        else{
            ll j(0),c(0),len;
            for(;j <= tot;++j)if(used[j]){
                len = min(A[i].b,B[j].b) - max(A[i].a,B[j].a) + 1;
                if(len <= 0) continue;
                if((c += len) >= A[i].c) break;
            }
            printf("%lld\n",B[j].c);
        }
    }
    return 0;
}
