#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int Maxn=50005,INF=0x7f7f7f7f;
int f[20][Maxn],Y[Maxn],R[Maxn],n,m;
char Inb[1<<16],*Ins=Inb,*Ine=Inb,Inc; int Ina; bool InSign;
#define getc() ((Ins==Ine&&(Ine=(Ins=Inb)+fread(Inb,1,1<<16,stdin),Ins==Ine))?0:*Ins++)
inline int geti() {
    InSign = false;
    while(Inc=getc(),Inc<'0')InSign|=Inc=='-';Ina=Inc-'0';
    while(Inc=getc(),'-'<Inc)Ina=(Ina<<3)+(Ina<<1)+Inc-'0';
	return InSign?-Ina:Ina;
}
inline void Make_St() {
    for (register int i=1;i<=n;++i)f[0][i]=R[i];
    for (register int j=1,i;(1<<j)<=n;++j)
		for (i=1;i+(1<<j)-1<=n;++i)
			f[j][i]=max(f[j-1][i],f[j-1][i+(1<<(j-1))]);
}
inline int rmq(const int &l, const int &r) {
    if (l>r)return -INF;
    register int k = 0;
    while ((1<<(k+1)<=r-l+1))++k;
    return max(f[k][l],f[k][r-(1<<k)+1]);
}
int main() {
    register int i,l,r,a,b;
    for (n=geti(),i=1;i<=n;++i)Y[i]=geti(),R[i]=geti();
    m=geti();Make_St();
    while(m--) {
        a=geti(),b=geti();
        l=lower_bound(Y+1,Y+n+1,a)-Y;
        r=lower_bound(Y+1,Y+n+1,b)-Y;
        if((Y[l]^a)&&(Y[r]^b))puts("maybe");
        else if(Y[l]==a&&Y[r]==b){
            if(R[l]<R[r]) puts("false");
            else{
                if(rmq(l+1,r-1)<R[r])(r-l==b-a)?puts("true"):puts("maybe");
                else puts("false");
            }
        }else if(Y[l]^a)(rmq(l,r-1)>=R[r])?puts("false"):puts("maybe");
        else(rmq(l+1,r-1)>=R[l])?puts("false"):puts("maybe");
    }
    return 0;
}
