#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=507;
double a[MAXN];

int main(){
    //freopen("in.txt","r",stdin);
    int n,k,up,down;
    double coe,res;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;++i)
        scanf("%lf",&a[i]);
    int i=0;
        res=0.0;
        coe=1.0*k/n;
        res=coe*a[i];
        up=n-k;down=n-1;
        for(int j=i-1,jinf=i-n+k;j>=jinf;--j){
            coe*=1.0*up/down;
            --up;--down;
            res+=coe*a[(j+n)%n];
        }
        printf("%.7lf",res);
    ++i;
    for(;i<n;++i){
        res=0.0;
        coe=1.0*k/n;
        res=coe*a[i];
        up=n-k;down=n-1;
        for(int j=i-1,jinf=i-n+k;j>=jinf;--j){
            coe*=1.0*up/down;
            --up;--down;
            res+=coe*a[(j+n)%n];
        }
        printf(" %.7lf",res);
    }
    putchar('\n');
    return 0;
}

