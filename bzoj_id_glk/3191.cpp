#include <cstdio>
#define geti(x) {\
while(c=getchar(),c<'-');t=c-'0';\
while(c=getchar(),'-'<c)t=(t<<3)+(t<<1)+c-'0';\
x=t;\
}
char a[50]; float dp[51][51];
int main() {
    register char n,m,i,j,k,t,c;
	geti(n);geti(m);
    for(i=0;i<m;++i)geti(a[i]);
    dp[1][1]=1.0;
    for(i=2;i<=n;++i)
	for(j=1;j<=i;++j)
	for(k=0;k<m;++k) {
		if(!(t=a[k]%i)) t=i;
		if(j<t)dp[i][j]+=dp[i-1][i-t+j]/m;
		if(t<j)dp[i][j]+=dp[i-1][j-t]/m;
	}
    for(i=1;i<n;printf("%.2f%% ",dp[n][i++]*100));
    printf("%.2f%%",dp[n][n]*100);
    return 0;
}
